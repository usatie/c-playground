IMAGE_NAME=rootme
NAME=rootme

minishell: rl.c
	gcc -o minishell rl.c -L$(brew --prefix readline)/lib -lreadline

pipex: pipe.c
	gcc -o pipex pipe.c

run:
	docker run --rm -it --cap-add=SYS_PTRACE --security-opt="seccomp=unconfined" -v `pwd`:/playground -w /playground $(IMAGE_NAME) /bin/bash

.PHONY: run
