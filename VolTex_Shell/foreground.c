#include "headers.h"

void foreground(char **tokens, int nb_par)
{
	char *com[nb_par + 1];
	int i = 0;
	for (; i < nb_par; i++)
		com[i] = tokens[i];
	com[i] = NULL;

	int pid = fork();
	// printf(tokens[0]);
	if (pid < 0)
	{
		printf("Error: Fork Failed\n");
		return;
	}
	else if (pid == 0)
	{
		setpgid(0, 0);
		if (execvp(com[0], com) == -1)
		{
			printf("no such command\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		childpid = pid;
		char name[100];
		strcpy(name, com[0]);
		for (int i = 0; i < (nb_par - 1); i++)
		{
			strcat(name, " ");
			strcat(name, tokens[i]);
		}

		fore.pid = pid;
		strcpy(fore.name, name);
		fore.is_back = 0;
		waitpid(-1, NULL, WUNTRACED);
	}
}