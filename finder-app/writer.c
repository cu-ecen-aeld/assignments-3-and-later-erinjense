

#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRED_ARG_CNT (3)

int
main(int argc, char ** argv)
{
	openlog(NULL, 0, LOG_USER);

	if (REQUIRED_ARG_CNT != argc)
	{
		syslog(LOG_ERR, "Invalid number of arguments: %d", argc);
		return (1);
	}

	char const * const write_file = argv[1];
	char const * const write_str  = argv[2];

	FILE * fp_write_file = fopen(write_file, "w+");

	if (NULL == fp_write_file)
	{
		syslog(LOG_ERR, "Unable to create %s", write_file);
		return (1);
	}

	syslog(LOG_DEBUG, "Writing %s to %s", write_str, write_file);

	fwrite(write_str, sizeof(write_str[0]),
		strlen(write_str), fp_write_file);

	fclose(fp_write_file);

	closelog();

	return (0);
}
