B = bin
T = addp addpc addpd
E = package install

all: config $(T)

config:
	(mkdir -p ${B} && cd ${B} && cmake ..)

$(T) $(E):
	(cd ${B} && make $@)
