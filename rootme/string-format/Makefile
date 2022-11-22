IMAGE_NAME=rootme
NAME=rootme
CFLAGS=-no-pie

all: format.c
	$(CC) $(CFLAGS) -o a.out format.c

run:
	docker run --rm -it --cap-add=SYS_PTRACE --security-opt="seccomp=unconfined" -v `pwd`:/playground -w /playground $(IMAGE_NAME) /bin/bash

.PHONY: run
