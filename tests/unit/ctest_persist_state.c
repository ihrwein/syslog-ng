#include <criterion/criterion.h>

#include "persist-state.h"
#include "apphook.h"
#include "libtest/cpersist_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct _TestState
{
  guint32 value;
} TestState;

void
_write_test_file_for_test_in_use_handle(gboolean in_use_handle, const gchar *filename)
{
  PersistState *state = clean_and_create_persist_state_for_test(filename);
  PersistEntryHandle handle = persist_state_alloc_entry(state, "alma", sizeof(TestState));
  TestState *test_state = (TestState*) persist_state_map_entry(state, handle);
  test_state->value = 0xDEADBEEF;
  persist_state_unmap_entry(state, handle);

  if (!in_use_handle)
    persist_state_remove_entry(state, "alma");

  commit_and_free_persist_state(state);
}

void
_foreach_callback_assertions(gchar* name, gint size, gpointer entry, gpointer userdata)
{
  cr_assert_str_eq((gchar *) userdata, "test_userdata", "Userdata is not passed correctly to foreach func!");
  cr_assert_str_eq(name, "test", "Name of persist entry does not match!");

  TestState *state = (TestState *) entry;
  cr_assert_eq(state->value, 3, "Content of state does not match!");
  cr_assert_eq(size, sizeof(TestState), "Size of state does not match!");
}


/*
 * Tests
 */

TestSuite(persist_state, .init = app_startup, .fini = app_shutdown);

#ifndef __hpux
Test(persist_state, test_persist_state_open_success_on_invalid_file)
{
  const gchar *persist_file = "test_invalid_magic.persist";
  PersistState *state;
  int fd;
  unlink(persist_file);

  fd = open(persist_file, O_CREAT | O_RDWR, 0777);
  write(fd, "aaa", 3);
  close(fd);

  state = persist_state_new(persist_file);
  cr_assert(persist_state_start(state), "persist_state_start returned with false!");

  cancel_and_destroy_persist_state(state);
}

Test(persist_state, test_persist_state_open_fails_on_invalid_file_with_dump)
{
  const gchar *persist_file = "test_invalid_magic_d.persist";
  PersistState *state;
  int fd;
  unlink(persist_file);

  fd = open(persist_file, O_CREAT | O_RDWR, 0777);
  write(fd, "aaa", 3);
  close(fd);

  state = persist_state_new(persist_file);
  cr_assert_not(persist_state_start_dump(state),
    "persist_state_start_dump returned with success when persist file was invalid!");

  cancel_and_destroy_persist_state(state);
}

Test(persist_state, test_persist_state_open_failes_when_file_open_fails)
{
  const gchar *persist_file = "test_invalid_magic_of.persist";
  PersistState *state;
  unlink(persist_file);

  state = persist_state_new(persist_file);

  cr_assert_not(persist_state_start_dump(state),
    "persist_state_start_dump returned with success when persist file open failed!");

  cancel_and_destroy_persist_state(state);
}

Test(persist_state, test_persist_state_in_use_handle_is_loaded)
{
  const gchar *persist_file = "test_in_use.persist";
  PersistState *state;
  guint8 version;
  gsize size;
  PersistEntryHandle handle;

  unlink(persist_file);
  _write_test_file_for_test_in_use_handle(TRUE, persist_file);

  state = create_persist_state_for_test(persist_file);

  handle = persist_state_lookup_entry(state, "alma", &size, &version);

  cr_assert_neq(handle, 0, "lookup failed when looking for simple entry with in_use = TRUE!");

  cancel_and_destroy_persist_state(state);
}

Test(persist_state, test_persist_state_not_in_use_handle_is_not_loaded)
{
  const gchar *persist_file = "test_in_use_hn.persist";
  PersistState *state;
  guint8 version;
  gsize size;
  PersistEntryHandle handle;

  unlink(persist_file);
  _write_test_file_for_test_in_use_handle(FALSE, persist_file);

  state = create_persist_state_for_test(persist_file);

  handle = persist_state_lookup_entry(state, "alma", &size, &version);

  cr_assert_eq(handle, 0, "lookup succeeded when looking for simple entry with in_use = FALSE!");

  cancel_and_destroy_persist_state(state);
}

Test(persist_state, test_persist_state_not_in_use_handle_is_loaded_in_dump_mode)
{
  const gchar *persist_file = "test_in_use_dm.persist";
  PersistState *state;
  guint8 version;
  gsize size;
  PersistEntryHandle handle;

  unlink(persist_file);
  _write_test_file_for_test_in_use_handle(FALSE, persist_file);

  state = persist_state_new(persist_file);
  persist_state_start_dump(state);

  handle = persist_state_lookup_entry(state, "alma", &size, &version);

  cr_assert_neq(handle, 0, "lookup failed in dump mode when looking for simple entry with in_use = FALSE!");

  cancel_and_destroy_persist_state(state);
}

Test(persist_state, test_persist_state_remove_entry)
{
  guint8 version;
  gsize size;

  PersistState *state = clean_and_create_persist_state_for_test("test_persist_state_remove_entry.persist");

  PersistEntryHandle handle = persist_state_alloc_entry(state, "test", sizeof(TestState));

  handle = persist_state_lookup_entry(state, "test", &size, &version);
  cr_assert_neq(handle, 0, "lookup failed before removing entry");

  persist_state_remove_entry(state, "test");

  state = restart_persist_state(state);

  handle = persist_state_lookup_entry(state, "test", &size, &version);
  cr_assert_eq(handle, 0, "lookup succeeded after removing entry");

  cancel_and_destroy_persist_state(state);
}

Test(persist_state, test_persist_state_foreach_entry)
{
  PersistState *state = clean_and_create_persist_state_for_test("test_persist_foreach.persist");

  PersistEntryHandle handle = persist_state_alloc_entry(state, "test", sizeof(TestState));
  TestState *test_state = persist_state_map_entry(state, handle);
  test_state->value = 3;
  persist_state_unmap_entry(state, handle);

  persist_state_foreach_entry(state, _foreach_callback_assertions, "test_userdata");

  cancel_and_destroy_persist_state(state);
}

Test(persist_state, test_values)
{
  PersistState *state;
  gint i, j;
  gchar *data;

  state = clean_and_create_persist_state_for_test("test_values.persist");

  for (i = 0; i < 1000; i++)
    {
      gchar buf[16];
      PersistEntryHandle handle;

      g_snprintf(buf, sizeof(buf), "testkey%d", i);
      handle = persist_state_alloc_entry(state, buf, 128);
      cr_assert(handle, "Error allocating value in the persist file: %s", buf);

      data = persist_state_map_entry(state, handle);
      for (j = 0; j < 128; j++)
        {
          data[j] = (i % 26) + 'A';
        }
      persist_state_unmap_entry(state, handle);
    }
  for (i = 0; i < 1000; i++)
    {
      gchar buf[16];
      PersistEntryHandle handle;
      gsize size;
      guint8 version;

      g_snprintf(buf, sizeof(buf), "testkey%d", i);
      handle = persist_state_lookup_entry(state, buf, &size, &version);
      cr_assert(handle, "Error retrieving value from the persist file: %s", buf);

      data = persist_state_map_entry(state, handle);
      for (j = 0; j < 128; j++)
        cr_assert_eq(data[j], (i % 26) + 'A', "Invalid data in persistent entry");

      persist_state_unmap_entry(state, handle);
    }

  state = restart_persist_state(state);

  for (i = 0; i < 1000; i++)
    {
      gchar buf[16];
      PersistEntryHandle handle;
      gsize size;
      guint8 version;

      g_snprintf(buf, sizeof(buf), "testkey%d", i);
      handle = persist_state_lookup_entry(state, buf, &size, &version);
      cr_assert(handle, "Error retrieving value from the persist file: %s", buf);

      cr_assert(size == 128 && version == 4,
        "Error retrieving value from the persist file: %s, invalid size (%d) or version (%d)",
        buf, (gint) size, version);

      data = persist_state_map_entry(state, handle);
      for (j = 0; j < 128; j++)
          cr_assert_eq(data[j], (i % 26) + 'A', "Invalid data in persistent entry");

      persist_state_unmap_entry(state, handle);
    }
  cancel_and_destroy_persist_state(state);
}

Test(persist_state, test_persist_state_temp_file_cleanup_on_cancel)
{
  PersistState *state = clean_and_create_persist_state_for_test("test_persist_state_temp_file_cleanup_on_cancel.persist");

  cancel_and_destroy_persist_state(state);

  cr_assert(access("test_persist_state_temp_file_cleanup_on_cancel.persist", F_OK) != 0,
    "persist file is removed on destroy()");
  cr_assert(access("test_persist_state_temp_file_cleanup_on_cancel.persist-", F_OK) != 0,
    "backup persist file is removed on destroy()");
}

Test(persist_state, test_persist_state_temp_file_cleanup_on_commit_destroy)
{
  PersistState *state = clean_and_create_persist_state_for_test("test_persist_state_temp_file_cleanup_on_commit_destroy.persist");

  commit_and_destroy_persist_state(state);

  cr_assert(access("test_persist_state_temp_file_cleanup_on_commit_destroy.persist", F_OK) != 0,
    "persist file is removed on destroy(), even after commit");
  cr_assert(access("test_persist_state_temp_file_cleanup_on_commit_destroy.persist-", F_OK) != 0,
    "backup persist file is removed on destroy(), even after commit");
}
#endif
