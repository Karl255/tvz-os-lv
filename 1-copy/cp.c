#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(LIB_SYS)
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>

	#define FILE_T int
	#define file_open_read(path) open(path, O_RDONLY)
	#define FILE_OPEN_ERROR -1
	#define file_open_write(path) open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
	#define file_read(buffer, element_size, element_count, file) read(file, buffer, element_count * element_size)
	#define file_write(buffer, element_size, element_count, file) write(file, buffer, element_count * element_size)
	#define file_close(file) close(file)
#else
	#define FILE_T FILE*
	#define file_open_read(path) fopen(path, "rb")
	#define FILE_OPEN_ERROR NULL
	#define file_open_write(path) fopen(path, "wb")
	#define file_read(buffer, element_size, element_count, file) fread(buffer, element_size, element_count, file)
	#define file_write(buffer, element_size, element_count, file) fwrite(buffer, element_size, element_count, file)
	#define file_close(file) fclose(file)
#endif

typedef struct {
	long bufferSize;
} Options;

typedef enum {
	OPTION_HANDLED,
	OPTION_NOT_AN_OPTION,
	OPTION_ERROR_OR_QUIT
} OptionResult;

void print_help();
OptionResult handle_option(const char*, Options*);
void copy_file(Options, const char*, const char*);

int main(const int argc, const char** argv) {
	Options options;
	options.bufferSize = 1024;

	if (argc == 1) {
		print_help();
	} else {
		OptionResult res = handle_option(argv[1], &options);

		if (res != OPTION_ERROR_OR_QUIT) {
			size_t start = 1;

			if (res == OPTION_HANDLED) {
				start++;
			}

			if (start + 1 < argc) {
				copy_file(options, argv[start], argv[start + 1]);
			} else {
				printf("Not enough arguments: got %d", argc - 1);
			}
		}
	}

	return 0;
}

const char* HELP_TEXT =
#if defined(LIB_SYS)
	"Usage: cp_sys [OPTION] SOURCE DEST\n"
#else
	"Usage: cp_std [OPTION] SOURCE DEST\n"
#endif
	"\n"
	"Options:\n"
	"  -h            Show this help text\n"
	"  -b=BUFFER     Specify buffer size to use during copy (in bytes)\n"
	"  --            Options end\n";

void print_help() {
	fputs(HELP_TEXT, stdout);
}

OptionResult handle_option(const char* opt, Options* options) {
	if (strcmp(opt, "-h") == 0) {
		print_help();
		return OPTION_ERROR_OR_QUIT;
	} else if (strcmp(opt, "--") == 0) {
		return OPTION_HANDLED;
	} else if (strstr(opt, "-b=") == opt) {
		char* end;
		long result = strtol(opt + 3, &end, 10);
		
		if (end - opt == strlen(opt)) {
			options->bufferSize = result;
			return OPTION_HANDLED;
		} else {
			printf("Invalid value for -b option: %s\n", opt + 3);
			return OPTION_ERROR_OR_QUIT;
		}
	}

	return OPTION_NOT_AN_OPTION;
}

void copy_file(Options options, const char* sourcePath, const char* destionationPath) {
	FILE_T fSource = file_open_read(sourcePath);

	if (fSource == FILE_OPEN_ERROR) {
		perror(sourcePath);
		exit(-1);
	}

	FILE_T fDestionation = file_open_write(destionationPath);

	if (fDestionation == FILE_OPEN_ERROR) {
		perror(destionationPath);
		exit(-2);
	}

	int8_t* buffer = malloc(options.bufferSize * sizeof(int8_t));
	int bytesRead;

	do {
		bytesRead = file_read(buffer, sizeof(int8_t), options.bufferSize, fSource);
		file_write(buffer, sizeof(int8_t), bytesRead, fDestionation);
	} while(bytesRead == options.bufferSize);

	free(buffer);
	file_close(fSource);
	file_close(fDestionation);
}
