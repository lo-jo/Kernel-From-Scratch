FROM ubuntu:latest

RUN sudo apt-get update && apt-get install -y grub2-common xorriso 

RUN mkdir -p /shared

COPY ./create_iso.sh /shared/
COPY ../kernel /shared/

VOLUME /shared

WORKDIR /shared

RUN chmod +x ./create_iso.sh
RUN ./create_iso.sh

CMD [ "/bin/sh" ]