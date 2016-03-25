#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef EXIT_STATUS
# define EXIT_STATUS EXIT_SUCCESS
#endif

#if EXIT_STATUS == EXIT_SUCCESS
# define PROGRAM_NAME "true"
#else
# define PROGRAM_NAME "false"
#endif

void
usage(int status)
{
	printf("Usage: %s [ignored command line arguments]\n\
   or: %s OPTION\n", PROGRAM_NAME, PROGRAM_NAME);
	printf("%s\n\n",
			EXIT_STATUS == EXIT_SUCCESS
      ? "Exit with a success status code"
			: "Exit with a failure status code");
			     
	exit(status);
}

int
main(int argc, char **argv)
{
	if (argc == 2) {
    if (argv[1][0] && ! strcmp(argv[1], "--help"))
       usage(EXIT_STATUS);
    if (*argv[1] && ! strcmp(argv[1], "--version"))
       printf("version 1.0");
	}
			 
  return EXIT_STATUS;
}

