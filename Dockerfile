FROM ubuntu:20.04 AS build-env
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        git \
        g++ \
        ninja-build \
        cmake \
    && rm -rf /var/lib/apt/lists/*
RUN git clone --depth=1 https://github.com/yumetodo/utf8_to_windows31j_cvt_checker.git && \
    cd utf8_to_windows31j_cvt_checker/ && \
    cmake -B build -G "Ninja" . && \
    cmake --build build/ --target utf8_to_windows31j_cvt_checker

FROM ubuntu:20.04
COPY --from=build-env /utf8_to_windows31j_cvt_checker/build/src/utf8_to_windows31j_cvt_checker /usr/bin
RUN apt-get update && \
    apt-get install -y --no-install-recommends language-pack-ja && \
    update-locale LANG=ja_JP.UTF-8
