FROM ubuntu:22.04
LABEL discription="Dockerize vos"

# copy all the files from the current directory to the container

COPY . /app/

WORKDIR /app

RUN ["apt-get", "update"]
RUN ["apt-get", "install","-y","libgl1"]
RUN ["apt-get", "install", "-y", "python3"]
RUN ["apt-get", "install", "-y", "python3-pip"]
RUN ["apt-get","install","-y","make"]
RUN ["make", "wholeP"]

ENTRYPOINT ["tail"]
CMD ["-f","/dev/null"]