FROM ubuntu:latest

RUN apt-get update && apt-get install -y grub2-common xorriso grub-pc-bin

VOLUME /shared

WORKDIR /shared

RUN chmod +x ./create_iso.sh
RUN ./create_iso.sh

CMD [ "/bin/sh" ]