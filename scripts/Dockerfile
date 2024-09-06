FROM ubuntu:latest

RUN apt-get update && apt-get install -y grub2-common xorriso grub-pc-bin

VOLUME /shared

WORKDIR /shared

ENTRYPOINT [ "/bin/sh", "-c", "./create_iso.sh" ]