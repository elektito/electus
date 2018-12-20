all:
	cd ../_src_ && ./configure --prefix=/usr --exec-prefix= --enable-static-link && $(MAKE)

install:
	$(MAKE) -C ../_src_ install DESTDIR=${INSTDIR}

.PHONY: all install
