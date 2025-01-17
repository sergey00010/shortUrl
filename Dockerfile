FROM alpine:latest
EXPOSE 9999

WORKDIR /app

RUN apk add --no-cache \
    gcc \
    g++ \
    make \
    wget \
    cmake \
    boost-dev

COPY CMakeLists.txt /app/
COPY server_config.json /app/
COPY ./libs /app/libs/
COPY ./src /app/src/

ENV BOOST_ROOT=/app/libs/boost
RUN mkdir /app/build && cd /app/build && cmake .. && make

WORKDIR /app/build
CMD ["./shortUrl"]
