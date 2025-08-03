############################################################################################
############################################################################################

FROM debian:bullseye-20250721-slim AS build

WORKDIR /build

# apt packages
#   git                 - install dependences
#   gcc g++ cmake       - compile dependences
#   gdb                 - debug main program
#   python3 libasio-dev - Crow dependences*

# * -> required in the final image

# uncomment the 2nd line when the debian bullseye
# is archived (it is necessary to use `apt`)
RUN echo "Installing APT packages..." \
	#&& sed -i 's/deb\(\.debian\.org\)/archive\1/g' /etc/apt/sources.list \
	&& apt update 1> /dev/null        \
	&& apt install -y git gcc g++ cmake gdb python3 libasio-dev 1> /dev/null

############################################################################################

RUN echo "Downloading SH scripts..."                                    \
	&& mkdir /build/scripts                                             \
	&& git clone --depth 1 https://github.com/vishnubob/wait-for-it.git \
	&& mv ./wait-for-it/wait-for-it.sh ./scripts

############################################################################################

RUN echo "Cloning dependences from GitHub..."                                                      \
	&& git clone --depth 1 --branch v1.1.0 https://github.com/CrowCpp/Crow.git        1> /dev/null \
	&& git clone --depth 1 --branch  0.1.0 https://github.com/valkey-io/libvalkey.git 1> /dev/null \
	&& mkdir ./libvalkey/build ./Crow/build

RUN cd ./Crow/build                \
	&& cmake ..                    \
		-D CROW_BUILD_EXAMPLES=OFF \
		-D CROW_BUILD_TESTS=OFF    \
		-D CROW_AMALGAMATE=ON      \
		-D CROW_INSTALL=OFF        \
	&& make                        \
	&& mv crow_all.h /usr/local/include/crow.h

RUN cd ./libvalkey/build                       \
	&& cmake ..                                \
	&& make                                    \
	&& mv ../include/valkey /usr/local/include \
	&& mv ./libvalkey.so.0.1.0 /usr/local/lib/libvalkey.so

############################################################################################

COPY ./src ./src/
COPY Makefile .
RUN echo "Compiling the main application" \
	&& make

# for manual tests
CMD ["/bin/bash"]

############################################################################################
############################################################################################

FROM debian:bullseye-20250721-slim

WORKDIR /app

# uncomment the 2nd line when the debian bullseye
# is archived (it is necessary to use `apt`)
RUN echo "Installing dependences..."                   \
	#sed -i 's/deb\(\.debian\.org\)/archive\1/g' /etc/apt/sources.list \
	&& apt update 1> /dev/null                         \
	&& apt install -y python3 libasio-dev 1> /dev/null \
	&& apt clean

############################################################################################

COPY --from=build /usr/local/lib/libvalkey.so   /usr/local/lib
COPY --from=build /usr/local/include/crow.h     /usr/local/include
COPY --from=build /build/bin/rb-2025            .
COPY --from=build /build/scripts/wait-for-it.sh .
COPY ./start-server .

CMD ["./start-server"]

############################################################################################
############################################################################################
