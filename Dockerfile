FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get -y update && apt-get install -y build-essential cmake python git

COPY . /usr/src/app
WORKDIR /usr/src/app

RUN mkdir -p build && cd build && cmake .. && make
CMD build/FractalCreator