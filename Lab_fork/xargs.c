#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#ifndef NARGS
#define NARGS 4
#endif

#define READ 0
#define WRITE 1


void
clean_array(char *args[], int counter)
{
	for (int i = 1; i < counter; i++) {
		free(args[i]);
	}
}

int
main(int argc, char *argv[])
{
	char *command = NULL;

	if (argc == 2) {
		command = argv[1];
	} else {
		printf("bad program call\n");
		return 1;
	}

	char *args[] = { NULL, NULL, NULL, NULL, NULL, NULL };  // -> array de arrays
	args[0] = command;
	char *line = NULL;
	size_t len = 0;
	int counter = 1;

	while (getline(&line, &len, stdin) != -1) {  // leo stdin hasta terminar
		if (counter == NARGS + 1) {
			pid_t child_id = fork();  // hago un proceso

			if (child_id < 0) {
				printf("error in fork\n");
				clean_array(args, counter);
				free(line);
				exit(-1);
			}

			if (child_id == 0) {  // si soy hijo me convierto
				execvp(command, args);
			} else {  // si soy padre renuevo el contador y sigo
				clean_array(args, counter);
				counter = 1;
				wait(NULL);
			}
		}
		strtok(line, "\n");  // le saco el barra n
		char *string = malloc(strlen(line) + 1);
		strcpy(string, line);
		args[counter] = string;
		counter++;
	}
	free(line);

	// pueden quedarme argumentos sin procesar si quedan fuera del paquete
	// entonces para no perder memoria reorganizo el vector y libero lo necesario

	for (int i = counter; i < 5; i++) {
		args[i] = NULL;
	}
	pid_t child_id = fork();
	if (child_id < 0) {
		printf("error in fork\n");
		clean_array(args, counter);
		exit(-1);
	}

	if (child_id == 0) {
		execvp(command, args);
	} else {
		clean_array(args, counter);
		wait(NULL);
	}
	return 0;
}
