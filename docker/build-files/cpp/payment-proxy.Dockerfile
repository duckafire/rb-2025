############################################################################################
############################################################################################

FROM debian:bullseye-20250721-slim AS build

WORKDIR /build

# add this to RUN when the debian bullseye is archieved
# sed -i 's/deb\(\.debian\.org\)/archive\1/g' /etc/apt/sources.list

RUN apt update 1> /dev/null \
	&& apt install -y git gcc cmake 1> /dev/null

RUN git clone --depth 1 --branch 0.1.0 https://github.com/valkey-io/libvalkey.git 1> /dev/null \
	&& mkdir ./libvalkey/build \
	&& cd ./libvalkey/build \
	&& cmake .. 1> /dev/null \
	&& make 1> /dev/null \
	&& mv ../include/valkey /usr/local/include \
	&& mv ./libvalkey.so.0.1.0 /usr/local/lib/libvalkey.so

RUN cd /build \
	&& git clone --depth 1 https://github.com/vishnubob/wait-for-it.git 1> /dev/null

RUN apt install -y libcurl4-openssl-dev 1> /dev/null

COPY ./docker/Makefile .
COPY ./src/cpp/include ./include

############################################################################################

RUN apt install -y g++ python3 libasio-dev 1> /dev/null

RUN git clone --depth 1 --branch 0.1.0 https://github.com/CrowCpp/Crow.git 1> /dev/null \
	&& mkdir ./Crow/build \
	&& cd ./Crow/build \
	&& cmake .. \
		-D CROW_BUILD_EXAMPLES=OFF \
		-D CROW_BUILD_TESTS=OFF \
		-D CROW_AMALGAMATE=ON \
		-D CROW_INSTALL=OFF \
	&& make \
	&& mv crow_all.h /usr/local/include/crow.h

COPY ./src/cpp/payment-proxy ./src

RUN make \
	LIBS_DEP="valkey asio" \
	SRC_FILES="main" \
	COMPILER=g++ \
	FILES_EXT=.cpp

############################################################################################
############################################################################################

FROM debian:bullseye-20250721-slim

WORKDIR /app
CMD ["/app/boot"]

# add this to RUN when the debian bullseye is archieved
# sed -i 's/deb\(\.debian\.org\)/archive\1/g' /etc/apt/sources.list

RUN apt update 1> /dev/null \
	&& apt install -y libcurl4 1> /dev/null

COPY --from=build /usr/local/lib/libvalkey.so /usr/local/lib
COPY --from=build /build/wait-for-it/wait-for-it.sh /build/bin/run ./
COPY ./docker/boot-app ./boot

############################################################################################

RUN apt install -y python3 libasio-dev 1> /dev/null

############################################################################################
############################################################################################
