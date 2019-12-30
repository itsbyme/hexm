#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <hexm.h>

#define NAME "hexm"
#define VERSION "0-0-0"
#define AUTHOR "itsbyme"

void usage(void)
{
	puts("Usage " NAME "." VERSION ":");
	puts("hexm [option]|[file]");
	puts("Options:");
	puts("\t-v    show version info");
	puts("\t-h    show this help info");
	puts("That's all, kids!");
	exit(EXIT_SUCCESS);
}

void version_info(void)
{
	puts(NAME);
	puts("\tversion: " VERSION);
	puts("\tauthor:" AUTHOR);
	exit(EXIT_SUCCESS);
}

void die(char *msg)
{
	puts(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if (argc == 1) 
		usage();
	int c;
	while ((c = getopt(argc, argv, "vh")) != -1) {
		switch (c) {
			case 'v':
				version_info();
				break;
			case 'h':
				usage();
				break;
			case '?':
				usage();
				break;
			default:
				abort();
		}
	}
	FILE *file = fopen(argv[optind], "r");
	Program *program = parse_stream(file);
	return core(program);
}
