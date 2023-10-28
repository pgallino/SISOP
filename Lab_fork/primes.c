#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define READ 0
#define WRITE 1

void
primes(int *left_pipe_fds)
{
	close(left_pipe_fds[WRITE]);

	// p := <leer valor de pipe izquierdo>
	int p;
	if (read(left_pipe_fds[READ], &p, sizeof p) <= 0) {
		exit(0);
	}

	// imprimir p // asumiendo que es primo
	printf("primo %d\n", p);

	// creo el pipe de escritura
	int right_pipe_fds[2];

	if (pipe(right_pipe_fds) < 0) {
		printf("error in primes_pipe\n");
		close(left_pipe_fds[READ]);
		exit(-1);
	}

	// creo el nuevo proceso
	pid_t child_id = fork();

	if (child_id < 0) {
		printf("error in fork in primes\n");
		close(right_pipe_fds[READ]);
		close(right_pipe_fds[WRITE]);
		close(left_pipe_fds[READ]);
		exit(-1);
	}

	if (child_id == 0) {
		close(left_pipe_fds[READ]);
		primes(right_pipe_fds);
	} else {
		close(right_pipe_fds[READ]);
		// mientras <pipe izquierdo no cerrado>:
		// n = <leer siguiente valor de pipe izquierdo>
		int n;
		while (read(left_pipe_fds[READ], &n, sizeof(n)) > 0) {
			// si n % p != 0:
			if ((n % p) != 0) {
				// escribir <n> en el pipe derecho
				if (write(right_pipe_fds[WRITE], &n, sizeof(n)) <
				    0) {
					printf("error in write in primes\n");
					close(right_pipe_fds[WRITE]);
					close(left_pipe_fds[READ]);
					exit(-1);
				};
			}
		}
		close(right_pipe_fds[WRITE]);
		close(left_pipe_fds[READ]);
		wait(NULL);
	}
}

int
main(int argc, char *argv[])
{
	int n;

	if (argc == 2) {
		n = atoi(argv[1]);
	} else {
		printf("bad program call\n");
		return 1;
	}

	int first_pipe_fds[2];

	if (pipe(first_pipe_fds) < 0) {
		printf("error in pipe\n");
		exit(-1);
	}

	pid_t first_child_id = fork();

	if (first_child_id < 0) {
		printf("error in fork\n");
		exit(-1);
	}

	if (first_child_id == 0) {
		primes(first_pipe_fds);

	} else {
		close(first_pipe_fds[READ]);

		int number;
		for (int i = 0; i < n - 1; i++) {
			number = i + 2;
			if (write(first_pipe_fds[WRITE], &number, sizeof number) <
			    0) {
				printf("error in write\n");
				exit(-1);
			};
		}

		close(first_pipe_fds[WRITE]);
		wait(NULL);
	}
	return 0;
}
