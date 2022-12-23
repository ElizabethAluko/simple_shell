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

/**
 * read_cmd - read the cml input.
 * Return: a pointer.
 */
mParticle & HackerNoon adWrite on Growth Marketing, Win $12K!
 by
@MIMA

13,479 reads
Let's Build a Linux Shell [Part I]
June 8th 2020
12 min
by @MIMA



Open TLDR
tldt arrow


EN

Read on Terminal Reader
Mention Thumbnail
Mention Thumbnail


featured image - Let's Build a Linux Shell [Part I]

#programming
#linux
#shell
#terminal

1x
voice-avatar
Audio Presented by
T3rn-icon
Mohammed Isam HackerNoon profile picture
@MIMA
Mohammed Isam
GNU/Linux system administrator and programmer

About @MIMA

react to story with heartreaction animationreaction animationreaction animation
Since the early days of Unix, the shell has been part of the user's interface with the operating system. The first Unix shell (the Thompson shell) had very limited features, mainly I/O redirection and command pipelines. Later shells expanded on that early shell and added more and more capabilities, which gave us powerful features that include word expansion, history substitution, loops and conditional expressions, among many others.

Why This Tutorial
Over the past 20 years, I've been using GNU/Linux as my main operating system. I've used many GNU/Linux shells, including but not limited to bash, ksh, and zsh. However, I've always been bugged by this question: what makes the shell tick? Like, for example:

How does the shell parse my commands, convert them to executable instructions, and then perform these commands?
How does the shell perform the different word expansion procedures, such as parameter expansion, command substitution, and arithmetic expansion?
How does the shell implement I/O redirection?
... and so on.
As most GNU/Linux shells are open-sourced, if you want to learn the inner workings of the shell, you can search online for the source code and start digging in (that's what I actually did). But this advice is actually easier said than done. For example, where exactly should you start reading the code from? Which source files contain the code that implements I/O redirection? Where can I find the code that parses user commands? I guess you got the point.

This is why I’ve decided to write this tutorial, to help Linux users and programmers gain a better understanding of their shells. Together, we are going to implement a fully functional Linux shell, from scratch. Along the way, we'll see how a Linux shell manages to parse and execute commands, loops, and conditional expressions by actually writing the C code that does the above tasks. We’ll talk about word expansions and I/O redirection, and we’ll see the code that performs features.

By the end of this tutorial, we’ll have a basic Linux shell, that will not do much for now, but which we’ll expand and improve in the next parts. At the end of this series, we’ll have a fully functional Linux shell that can parse and execute a fairly complex set of commands, loops, and expressions.

What You Will Need
In order to follow this tutorial, you will need the following:

A working GNU/Linux system (I personally use Ubuntu and Fedora, but feel free to use your favorite Linux distribution).
GCC (the GNU Compiler Collection) to compile the code.
A text editor to write the code (I personally use GEdit, but you can use Vim, Emacs, or any other editor as well).
How to program in C.
I'm not going to dive into the details of installing the required software here. If you are not sure how to get your system running any of the above software packages, please refer to your Linux distribution's documentation and make sure you have everything set up before going further.

Now let's get down to business. We’ll start by having a bird’s eye view of what constitutes a Linux shell.

Components of a Linux Shell
The shell is a complex piece of software that contains many different parts.

The core part of any Linux shell is the Command Line Interpreter, or CLI. This part serves two purposes: it reads and parses user commands, then it executes the parsed commands. You can think of the CLI itself as having two parts: a parser (or front-end), and an executor (or back-end).

The parser scans input and breaks it down to tokens. A token consists of one or more characters (letters, digits, symbols), and represents a single unit of input. For example, a token can be a variable name, a keyword, a number, or an arithmetic operator.

The parser takes these tokens, groups them together, and creates a special structure we call the Abstract Syntax Tree, or AST. You can think of the AST as a high level representation of the command line you gave to the shell. The parser takes the AST and passes it to the executor, which reads the AST and executes the parsed command.

Another part of the shell is the user interface, which usually operates when the shell is in the interactive mode, for example, when you are entering commands at the shell prompt. Here the shell runs in a loop, which we know as the Read-Eval-Print-Loop, or REPL.

As the loop's name indicates, the shell reads input, parses and executes it, then loops to read the next command, and so on until you enter a command such as exit , shutdown, or reboot.

Most shells implement a structure known as the symbol table, which the shell uses to store information about variables, along with their values and attributes. We'll implement the symbol table in part II of this tutorial.

Linux shells also have a history facility, which allows the user to access the most recently entered commands, then edit and re-execute commands without much typing. A shell can also contain builtin utilities, which are a special set of commands that are implemented as part of the shell program itself.

Builtin utilities include commonly used commands, such as cd, fg, and bg. We'll implement many of the builtin utilities as we move along with this tutorial.

Now that we know the basic components of a typical Linux shell, let's start building our own shell.

Our First Shell
Our first version of the shell won't do anything fancy; it will just print a prompt string, read a line of input, then echo the input back to the screen. In subsequent parts of this tutorial, we’ll add the capability to parse and execute commands, loops, conditional expressions, and much more.

Let's start by creating a directory for this project. I usually use ~/projects/ for my new projects, but feel free to use whatever path you're comfortable with.

The first thing we'll do is to write our basic REPL loop. Create a file named main.c (using touch main.c), then open it using your favorite text editor. Enter the following code in your main.c file:

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

int main(int argc, char **argv)
{
    char *cmd;

    do
    {
        print_prompt1();

        cmd = read_cmd();

        if(!cmd)
        {
            exit(EXIT_SUCCESS);
        }

        if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
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

    } while(1);

    exit(EXIT_SUCCESS);
}
Our main() function is quite simple, as it only needs to implement the REPL loop. We first prints the shell's prompt, then we read a command (for now, let's define a command as an input line ending with \n). If there's an error reading the command, we exit the shell. If the command is empty (i.e. the user pressed ENTER without writing anything), we skip this input and continue with the loop.

If the command is exit, we exit the shell. Otherwise, we echo back the command, free the memory we used to store the command, and continue with the loop. Pretty simple, isn't it?

Our main() function calls two custom functions, print_prompt1() and read_cmd(). The first function prints the prompt string, and the second one reads the next line of input. Let’s have a closer look at those two functions.

Printing Prompt Strings
We said that the shell prints a prompt string before reading each command. In fact, there are five different types of prompt string: PS0 , PS1, PS2, PS3, and PS4. The zeroth string, PS0, is only used by bash, so we won’t consider it here. The other four strings are printed at certain times, when the shell wants to convey certain messages to the user.

In this section, we’ll talk about PS1 and PS2. The rest will come later on when we discuss more advanced shell topics.

Now create the source file prompt.c and enter the following code:

#include <stdio.h>
#include "shell.h"

void print_prompt1(void)
{
    fprintf(stderr, "$ ");
}

void print_prompt2(void)
{
    fprintf(stderr, "> ");
}
The first function prints the first prompt string, or PS1, which you usually see when the shell is waiting for you to enter a command. The second function prints the second prompt string, or PS2, which is printed by the shell when you enter a multi-line command (more on this below).

Next, let’s read some user input.

Reading User Input
Open the file main.c and enter the following code at the end, right after the main() function:

char *read_cmd(void)
{
	char buf[1024];
	char *ptr = NULL;
	char ptrlen = 0;

	while(fgets(buf, 1024, stdin))
	{
		int buflen = strlen(buf);
		
		if(!ptr)
		{
			ptr = malloc(buflen+1);
		}
		else
		{
			char *ptr2 = realloc(ptr, ptrlen+buflen+1);
			if(ptr2)
			{
				ptr = ptr2;
			}
			else
			{
				free(ptr);
				ptr = NULL;
			}
		}

		if(!ptr)
		{
			fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
			return NULL;
		}

		strcpy(ptr+ptrlen, buf);

		if(buf[buflen-1] == '\n')
		{
			if(buflen == 1 || buf[buflen-2] != '\\')
			{
				return ptr;
			}

			ptr[ptrlen+buflen-2] = '\0';
			buflen -= 2;
			print_prompt2();
		}

		ptrlen += buflen;
	}
	return ptr;
}
