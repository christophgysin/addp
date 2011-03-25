B = bin
T = all help \
	clean \
	depend edit_cache \
	install install/local install/strip \
	list_install_components \
	package package_source \
	rebuild_cache \
	test \
	addp addpc addpd

default: config all

config:
	(mkdir -p ${B} && cd ${B} && cmake ..)

$(T):
	(cd ${B} && make $@)
