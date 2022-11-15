IMAGE_NAME=rootme
NAME=rootme

run:
	docker run --rm -it --cap-add=SYS_PTRACE --security-opt="seccomp=unconfined" -v `pwd`:/playground -w /playground $(IMAGE_NAME) /bin/bash

.PHONY: run
