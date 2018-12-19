all: hello

hello:
	gcc hello.c -static -o hello
	strip hello

clean:
	rm -f hello

install:
	cp hello ${INSTDIR}/init

.PHONY: all clean install
