// work in progress general string parsing program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

#include "sentinel.h"

#define SCRIPT_MAX 2048

int main(int argc, char **argv) {

	int opt;

	// flags
	bool has_infile = false;
	bool has_outfile = false;
	bool has_script = false;
	bool has_precompile = false;
	bool write_compilation = false;
	bool wrap_newlines = false;

	// arguments
	char infile_name[NAME_MAX];
	char outfile_name[NAME_MAX];
	char script_name[NAME_MAX];
	char precompile_name[NAME_MAX];
	char outcompile_name[NAME_MAX];
	char script_content[SCRIPT_MAX];

	int in_fd;
	int out_fd;

	// parse arguments
	while ((opt = getopt(argc, argv, "f:o:i:c:Cwh")) != -1) {
		switch (opt) {
		case 'f': strncpy(infile_name, optarg, sizeof(infile_name)); has_infile = true; break;
		case 'o': strncpy(outfile_name, optarg, sizeof(outfile_name)); has_outfile = true; break;
		case 'i': strncpy(script_content, optarg, sizeof(script_content)); has_script = true; break;
		case 'c': strncpy(precompile_name, optarg, sizeof(precompile_name)); has_precompile = true; break;
		case 'C': strncpy(outcompile_name, optarg, sizeof(outcompile_name)); write_compilation = true; break;
		case 'w': wrap_newlines = true; break;
		case 'h': show_help(); return 0;

		// unknown option
		case '?':
			if (optopt == 'f' || optopt == 'o') {
				fprintf(stderr, "Option '-%c' requres an argument.\n", optopt);

			} else if (isprint(optopt)) {
				fprintf(stderr, "Unknown option '-%c'.\n", optopt);

			} else {
				fprintf(stderr, "Unknown option character '\\x%x'\n", optopt);
			}
		}			
	}

	// sentinel script must be provided to operate
	if (optind >= argc && !has_script) {
		fprintf(stderr, "No sentinel script provided\n");
		return 0;
	// script passed as non-opt argument
	} else if (!has_script) {
		strncpy(script_content, argv[optind], sizeof(script_content));
	}

	// if we have an infile, read from it, else stdin
	if (has_infile) {
		infile_name[NAME_MAX - 1] = '\0';
		in_fd = open(infile_name, O_RDONLY);
	} else {
		in_fd = dup(STDIN_FILENO);
	}

	// if we have an outfile, write to it, else stdout
	if (has_outfile) {
		outfile_name[NAME_MAX - 1] = '\0';
		out_fd = open(outfile_name, O_WRONLY|O_CREAT, 0666);
	} else {
		out_fd = dup(STDOUT_FILENO);
	}

	// compile script
	// TODO: if write_compilation, write out compilation to current dir

	// start string parsing

	// free any resources
	close(in_fd);
	close(out_fd);
	return 0;
}

void show_help() {
	char *help_text =
	"Usage: sentinel [OPTIONS...] <sentinel_script>\n"
	"\n"
    "-f <filename>  --  Specify the name of a text file as input. If none are\n"
    "                   selected, will instead read from stdin.\n"
    "\n"
    "-o <filename>  --  Specify the name of an output file. Will create a new\n"
    "                   file if none exists and overwrite any which do. If none\n"
    "                   specified, will instead write to stdout.\n"
    "\n"
    "-i <script>    --  Provide script through opts rather than as an arg.\n"
    "\n"
    "-c <sntl_file> --  Provide a .sntl file as a precompiled script.\n"
    "\n"
    "-C <filename>  --  Output a compiled .sntl file from the provided script\n"
    "                   for use later.\n"
    "\n"
    "-w             --  Wrap newlines. Sentinel marching by default ends at \n"
    "                   newlines. Marching may optionally wrap around newlines \n"
    "                   with -w. If wrapping is enabled, things will only stop \n"
    "                   after the last code has finished executing.\n"
    "\n"
    "-h             --  Display help message.\n";

	fprintf(stdout, help_text);
	return;
}

void compile_script(uint8_t **dest, size_t *length, char *script) {
	// TODO: compilation stuff. Just follow outline in header
	return;
	
}
