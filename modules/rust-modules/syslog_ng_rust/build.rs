use std::env;

fn main() {
    let abs_top_builddir = env::var("abs_top_builddir").unwrap();
    
    println!("cargo:rustc-flags= -L native={}/lib/.libs -l dylib=syslog-ng", abs_top_builddir);
}
