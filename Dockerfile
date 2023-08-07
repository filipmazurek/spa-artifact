FROM ubuntu:18.04

RUN apt update
RUN apt install -y build-essential git m4 scons zlib1g zlib1g-dev libprotobuf-dev protobuf-compiler libprotoc-dev libgoogle-perftools-dev python3-dev python libboost-all-dev pkg-config wget

CMD ["/bin/bash"]
