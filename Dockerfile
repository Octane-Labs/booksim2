# GenXYZ
#
# VERSION         0.0.1
# Pull base image
FROM ontouchstart/libzmq

# Install modified booksim2 from repository

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y flex bison
# RUN cd /tmp && git clone https://github.com/Octane-Labs/booksim2.git && cd booksim2 && make -j 8
ADD https://github.com/Octane-Labs/booksim2/archive/GenXYZ.zip /tmp/
RUN unzip /tmp/GenXYZ.zip -d /tmp
RUN cd /tmp/booksim2-GenXYZ/src/ && make -j 8
RUN cp /tmp/booksim2-GenXYZ/src/booksim /usr/bin/
