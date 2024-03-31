#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define REQUIRED_ARG_CNT (3)

int
main(int argc, char ** argv)
{
	openlog(NULL, 0, LOG_USER);

	if (REQUIRED_ARG_CNT != argc)
	{
		syslog(LOG_ERR, "Invalid number of arguments: %d", 
				argc);
		return (1);
	}

	char const * const write_file = argv[1];
	char const * const write_str  = argv[2];

	int fd_write_file = open(write_file, O_RDWR | O_CREAT, 0644);

	if (-1 == fd_write_file)
	{
		perror("open file failed");
		syslog(LOG_ERR, "Unable to create %s: %s", 
				write_file, strerror(errno));
		return (1);
	}

	syslog(LOG_DEBUG, "Writing %s to %s", write_str, write_file);

	write(fd_write_file, write_str, strlen(write_str));

	int close_status = close(fd_write_file);

	if (-1 == close_status)
	{
		perror("close file failed");
		syslog(LOG_ERR, "Unable to close file %s: %s",
				write_file, strerror(errno));
	}

	closelog();

	return (0);
}
