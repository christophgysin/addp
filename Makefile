B := bin
T := all help clean depend edit_cache install install/local install/strip \
	list_install_components package package_source rebuild_cache test \
	addp addpc addpd

default: config all test

config:
	@(mkdir -p ${B} && cd ${B} && cmake ${CMAKE_OPTS} ..)

$(T):
	@(cd ${B} && \
		if [ -f Makefile ]; then \
			make $@; \
		elif [ -f rules.ninja ]; then \
			ninja $@; \
		fi \
	)

clang:
	make CC=/usr/bin/clang CXX=/usr/bin/clang++ default

iwyu: B := bin-iwyu
iwyu:
	(mkdir -p ${B} && cd ${B} && cmake -D IWYU=true .. && make iwyu)

ninja:
	make CMAKE_OPTS=-GNinja default

ninja-clang:
	make CMAKE_OPTS=-GNinja CC=/usr/bin/clang CXX=/usr/bin/clang++ default
