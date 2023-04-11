FROM ubuntu:20.04

WORKDIR /home/

COPY s21_vector.h /home
COPY s21_vector_realiz.cc /home
COPY test_vector.cc /home
COPY Makefile /home

RUN apt update &&\
    apt install -y gcc make libfcgi-dev\
    libgtest-dev build-essential vim google-mock\
    libgmock-dev