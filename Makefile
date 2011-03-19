B = bin
T = addp addpc addpd
E = install

all: configure $(T)

configure:
	(mkdir -p ${B} && cd ${B} && cmake ..)

$(T) $(E):
	(cd ${B} && make $@)
