#include <stdio.h>
#include "shell.h"

/**
 * print_prompt1 - print first prompt string.
 */

void print_prompt1(void)
{
	fprintf(stderr, "$ ");
}

/**
 * print_prompt2 - print second prompt.
 */
void print_prompt2(void)
{
	fprintf(stderr, "> ");
}
