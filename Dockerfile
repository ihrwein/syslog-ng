FROM ubuntu:trusty

RUN mkdir -p /home/syslog-ng/source
RUN mkdir -p /home/syslog-ng/install
RUN mkdir -p /home/syslog-ng/build
VOLUME /home/syslog-ng/source
RUN apt-get -qq update
RUN apt-get -qq install xsltproc bison libbison-dev make gcc
RUN apt-get -qq install libglib2.0-dev
RUN apt-get -qq install libevtlog-dev
RUN apt-get -qq install libssl-dev
RUN apt-get -qq install docbook-xsl
RUN apt-get -qq install flex
RUN apt-get -qq install autoconf libtool automake
WORKDIR cd /home/syslog-ng/build
CMD /bin/bash
# After you've built the image, run the following commands to bootstrap your dev environment:
# cd /home/syslog-ng/source/
# ./autogen.sh
# cd /home/syslog-ng/build
# ../source/configure --prefix=/home/syslog-ng/install --disable-mongodb --enable-debug
# and now you can run make from the build dir
