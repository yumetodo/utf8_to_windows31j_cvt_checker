FROM ubuntu:20.04
RUN apt-get update && \
    apt-get install -y --no-install-recommends language-pack-ja && \
    rm -rf /var/lib/apt/lists/* && \
    update-locale LANG=ja_JP.UTF-8
COPY utf8_to_windows31j_cvt_checker /usr/bin
