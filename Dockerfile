FROM ubuntu:16.04
MAINTAINER Eric Martindale <eric@blockstream.com>
RUN apt-get update -q && \
    apt-get install -y software-properties-common && \
    add-apt-repository -y ppa:bitcoin/bitcoin && \
    apt-get update -q && \
    apt-get install -y \
            git \
            autoconf \
            libtool \
            libprotobuf-c-dev \
            libsodium-dev \
            libsqlite3-dev \
            libgmp-dev \
            bsdmainutils \
            build-essential \
            libevent-dev \
            libsqlite3-dev \
            libdb4.8-dev \
            libdb4.8++-dev \
            libboost-all-dev \
            libssl-dev \
            g++ \
            curl \
            gcc \
            libc6-dev \
            make \
            pkg-config

RUN git clone https://github.com/ElementsProject/elements.git /opt/elements && \
    cd /opt/elements && \
    git checkout alpha && \
    ./autogen.sh && \
    ./configure --disable-wallet && \
    make && \
    make install
RUN useradd elements; mkdir /elements /bitcoin; chown elements:users /elements /bitcoin

RUN alphad -daemon

VOLUME ['/bitcoin', '/elements']
EXPOSE 22
EXPOSE 8333
