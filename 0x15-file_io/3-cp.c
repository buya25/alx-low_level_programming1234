#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *create_buffer(char *file);
void close_file(int fd);

/**
 * create_buffer - 1024 bytes for a buffer.
 * @file: file buffer is storing chars for.
 *
 * Return: A pointer - newly-allocated buffer.
 */
char *create_buffer(char *file)
{
	char *bf;

	bf = malloc(sizeof(char) * 1024);

	if (bf == NULL)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", file);
		exit(99);
	}

	return (bf);
}

/**
 * close_file - Closes file descriptors.
 * @fd: descriptor to be closed.
 */
void close_file(int fd)
{
	int cot;

	cot = close(fd);

	if (cot == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - Copies the contents of a file to another file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the argument count is incorrect - exit code 97.
 * If file from does not exist or cannot be read - exit code 98.
 * If file to cannot be created or written to - exit code 99.
 * If file to or from cannot be closed - exit code 100.
 */
int main(int argc, char *argv[])
{
	int frm, t, r, w;
	char *br;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	br = create_buffer(argv[2]);
	frm = open(argv[1], O_RDONLY);
	r = read(frm, br, 1024);
	t = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	do {
		if (frm == -1 || r == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't read from file %s\n", argv[1]);
			free(br);
			exit(98);
		}

		w = write(t, br, r);
		if (t == -1 || w == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", argv[2]);
			free(br);
			exit(99);
		}

		r = read(frm, br, 1024);
		t = open(argv[2], O_WRONLY | O_APPEND);

	} while (r > 0);

	free(br);
	close_file(frm);
	close_file(t);

	return (0);
}
