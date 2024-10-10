#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd;
        size_t size;
        char input[] = "inputFifo";
	char output[] = "outputFifo";

        (void)umask(0);

	if((argc > 1) && !strcmp(argv[1], "remove"))
	{	
		unlink(input);
		unlink(output);
		exit(0);
	}

        if(mknod(input, S_IFIFO | 0666, 0) < 0)
        {
                printf("Can\'t create FIFO\n");
                exit(-1);
        }

	if(mknod(output, S_IFIFO | 0666, 0) < 0)
        {
                printf("Can\'t create FIFO\n");
                exit(-1);
        }

	return 0;
}
