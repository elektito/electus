all: kernel

kernel:
	cp config ../_src_/.config
	$(MAKE) -C ../_src_

install:
	mkdir -p ${INSTDIR}/boot
	cp ../_src_/arch/x86/boot/bzImage ${INSTDIR}/boot/bzImage
	$(MAKE) modules_install INSTALL_MOD_PATH=${INSTDIR} -C ../_src_

.PHONY: all install
