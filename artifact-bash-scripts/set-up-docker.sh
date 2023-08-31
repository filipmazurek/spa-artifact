#!/bin/bash

docker build -t spa-builder .
docker run --privileged --name spa-container --mount type=bind,source=./docker-share,destination=/shared -it spa-builder bash
