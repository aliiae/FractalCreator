FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
            xz-utils \
            build-essential \
            curl \
            && rm -rf /var/lib/apt/lists/* \
            && curl -SL https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz \
            | tar -xJC . && \
            mv clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04 clang_10.0.0 && \
            echo 'export PATH=/clang_10.0.0/bin:$PATH' >> ~/.bashrc && \
            echo 'export LD_LIBRARY_PATH=/clang_10.0.0/lib:$LD_LIBRARY_PATH' >> ~/.bashrc
RUN apt-get install -y cmake
COPY . /usr/src/app
WORKDIR /usr/src/app

RUN mkdir -p build && cd build && cmake .. && make
CMD build/FractalCreator