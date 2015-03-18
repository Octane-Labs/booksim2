# GenXYZ
#
# VERSION         0.0.1
# Pull base image
FROM ontouchstart/libzmq

# Install modified booksim2 from repository

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y flex bison libzmq3-dev libtool autoconf automake uuid-dev uuid e2fsprogs libtool
# RUN cd /tmp && git clone https://github.com/Octane-Labs/booksim2.git && cd booksim2 && make -j 8
RUN cd /tmp && git clone https://github.com/zeromq/czmq && cd czmq && ./autogen && ./configure && make -j 4 && make install && ldconfig
ADD https://github.com/Octane-Labs/booksim2/archive/GenXYZ.zip /tmp/
RUN unzip /tmp/GenXYZ.zip -d /tmp
RUN cd /tmp/booksim2-GenXYZ/src/ && make -j 8
RUN cp /tmp/booksim2-GenXYZ/src/booksim /usr/bin/
