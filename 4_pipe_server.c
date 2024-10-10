#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
        int fd;
        size_t size;
        char input[] = "inputFifo";
	char output[] = "outputFifo";
	char result[40];
	int number = 0;
	
	/* Открываем FIFO на чтение.*/
        if ( (fd = open(input, O_RDONLY)) < 0)
        {
        	 /* Если открыть FIFO не удалось, печатаем об этом сообщение и прекращаем работу */
                 printf("Can\'t open FIFO for reading\n");
                 exit(-1);
        }

        size = read(fd, result, sizeof(result));

	if(!strcmp("error", result)) 
        {
                exit(-1);
        }

        if(size != (strlen(result) + 1))
        {
                /* Если считалось меньшее количество байт, сообщаем об ошибке и завершаем работу */
                printf("Can\'t read all string to FIFO\n");
                exit(-1);
        }

	close(fd);
        
	number = atoi(result);
	number *= number;
	sprintf(result, "%d", number);

	if ( (fd = open(output, O_WRONLY)) < 0)
        {
         /* Если открыть FIFO не удалось, печатаем об этом сообщение и прекращаем работу */
                 printf("Can\'t open FIFO for writting\n");
                 exit(-1);
        }
        
        size = write(fd, result, strlen(result) + 1);
        if(size != (strlen(result) + 1))
        {
                printf("Can\'t write all string to FIFO\n");
                exit(-1);
        }

        close(fd);

        return 0;
}
