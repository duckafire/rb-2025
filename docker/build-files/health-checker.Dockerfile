############################################################################################
############################################################################################

FROM debian:bullseye-20250721-slim AS build

WORKDIR /build

############################################################################################

# add this to RUN when the debian bullseye is archieved
# sed -i 's/deb\(\.debian\.org\)/archive\1/g' /etc/apt/sources.list

RUN apt update 1> /dev/null \
	&& apt install -y git gcc gdb cmake libcurl4-openssl-dev 1> /dev/null \
	\
	&& git clone --depth 1 --branch 0.1.0 https://github.com/valkey-io/libvalkey.git 1> /dev/null \
	&& mkdir ./libvalkey/build \
	&& cd ./libvalkey/build \
	&& cmake .. 1> /dev/null \
	&& make 1> /dev/null \
	&& mv ../include/valkey /usr/local/include \
	&& mv ./libvalkey.so.0.1.0 /usr/local/lib/libvalkey.so \
	\
	&& cd /build \
	&& git clone --depth 1 https://github.com/vishnubob/wait-for-it.git 1> /dev/null

############################################################################################

COPY ./docker/Makefile .
COPY ./include ./include
COPY ./src/health-checker-c ./src

RUN make \
	LIBS_DEP="valkey curl" \
	SRC_FILES="main checker cache response"

############################################################################################
############################################################################################

FROM debian:bullseye-20250721-slim

WORKDIR /app
CMD ["/app/boot"]

############################################################################################

# add this to RUN when the debian bullseye is archieved
# sed -i 's/deb\(\.debian\.org\)/archive\1/g' /etc/apt/sources.list

RUN apt update 1> /dev/null \
	&& apt install -y libcurl4 1> /dev/null \
	&& apt clean 1> /dev/null

############################################################################################

COPY --from=build /usr/local/lib/libvalkey.so /usr/local/lib
COPY --from=build /build/wait-for-it/wait-for-it.sh /build/bin/run ./
COPY ./docker/boot-app ./boot

############################################################################################
############################################################################################
