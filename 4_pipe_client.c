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
	char buffer[40] = {};
	char result[40] = {};
	int number = 0;

	printf("Введите число:\n");

	if ( (fd = open(input, O_WRONLY)) < 0)
        {
         /* Если открыть FIFO не удалось, печатаем об этом сообщение и прекращаем работу */
                 printf("Can\'t open FIFO for writting\n");
                 exit(-1);
        }
	
	if(scanf("%d", &number) != 1)
	{
		strcpy(buffer, "error");
		write(fd, buffer, strlen(buffer) + 1);
		printf("Нужно было ввести число.\n");
		close(fd);
		exit(-1);
	}
	else
	{
		sprintf(buffer, "%d", number);
	}

	size = write(fd, buffer, strlen(buffer) + 1);
        if(size != (strlen(buffer) + 1))
        {
                /* Если записалось меньшее количество байт, сообщаем об ошибке и завершаем работу */
                printf("Can\'t write all string to FIFO\n");
                exit(-1);
        }

        close(fd);

	if ( (fd = open(output, O_RDONLY)) < 0)
        {
                 /* Если открыть FIFO не удалось, печатаем об этом сообщение и прекращаем работу */
                 printf("Can\'t open FIFO for reading\n");
                 exit(-1);
        }

        size = read(fd, result, sizeof(result));

        if(size != (strlen(result) + 1))
        {
                /* Если считалось меньшее количество байт, сообщаем об ошибке и завершаем работу */
                printf("Can\'t read all string to FIFO\n");
                exit(-1);
        }

	close(fd);

	printf("Result: %s\n", result);

	return 0;
}
