#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

/**
 * main - shell entry point.
 * @argc: number of arguments in the function.
 * @argv: arrays of arguments.
 * Return: 0 if successful.
 */
int main(int argc, char **argv)
{
	char *cmd;

	do
	{
		print_prompt1();
		cmd read_cmd();

		if(!cmd)
			exit(EXIT_SUCCESS);
		if(cmd[0] == '\0'|| strcmp(cmd, "\n") == 0)
		{
			free(cmd);
			continue;
		}

		if(strcmp(cmd, "exit\n") == 0)
		{
			free(cmd);
			break;
		}

		printf("%s\n", cmd);
		free(cmd);
	}
	while(1);
	exit(EXIT_SUCCESS);
}
