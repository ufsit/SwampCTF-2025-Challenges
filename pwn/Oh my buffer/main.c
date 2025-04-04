#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define WRITE(x) write(STDOUT_FILENO, x, sizeof(x) - 1)

void reg(void)
{
	char buffer[16];

	WRITE("Username: ");
	read(STDIN_FILENO, buffer, 42);

	WRITE("Password: ");
	read(STDIN_FILENO, buffer, 42);

	WRITE("Sorry, registration isn't open right now!\n");
}

void login(void)
{
	int len;
	char buffer[16];

	WRITE("How long is your username: ");
	fscanf(stdin, "%d", &len);

	WRITE("Username: ");
	read(STDIN_FILENO, buffer, sizeof(buffer));

	WRITE("Sorry, we couldn't find the user: ");
	write(STDOUT_FILENO, buffer, len);
}

int main()
{
	FILE* pFile = fopen("flag.txt", "r");
	char flag[64];
	fgets(flag, sizeof(flag), pFile);
	fclose(pFile);

	FILE* pNull = fopen("/dev/null", "w");
	int fd      = dup(STDOUT_FILENO);
	dup2(fileno(pNull), STDOUT_FILENO);

	puts("Here's the flag, too bad we don't let you see this:");
	fflush(stdout);
	fputs(flag, stdout);
	memset(flag, 0, sizeof(flag));

	dup2(fd, STDOUT_FILENO);
	close(fd);
	fclose(pNull);

	if (fork() != 0)
	{
		wait(NULL);
		_exit(0);
	}

	while (1)
	{
		WRITE("===================\n");
		WRITE("Welcome to the box!\n");
		WRITE("1) Register\n");
		WRITE("2) Login\n");
		WRITE("3) Exit\n");
		WRITE("> ");

		char c;
		while ((c = getchar()) == '\n');
		int choice = atoi(&c) % 3;
		while (getchar() != '\n');

		WRITE("-------------------\n");

		switch (choice % 3)
		{
			case 0: _exit(0); break;
			case 1: reg(); break;
			case 2: login(); break;
		}
	}
}
