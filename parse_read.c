#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

struct map{
	char *raw;
	char *board;
	char *legend;
	int	key;
	char *file_path;
}test;

//Function to get the total size of the map file to malloc an array
int get_file_size(void)
{
	int count; //File size counter
	int fd; //File descriptor
	int status; //Loop control using return value from read, also failure status of whole function
	char    *c; //Temporary buffer to hold read bytes in local memory

	count = 0;
	status = 1;

	//Create the memory location for buffer
	c = (char *)malloc(sizeof(char));

	//Open the file
	fd = open(test.file_path, O_RDONLY);
	//Read one byte at a time till we hit the EOF char or return an error
	while (status > 0 && fd != -1)
	{
		status = read(fd, c, 1);
		if (status > 0)
			count++;
	}
	
	//Free the allocated memory
	free(c);

	//Close the file
	status = close(fd);
	//Return error or size of file
	if (status == -1 || fd == -1)
		return (-1);
	else
		return (count);
}

int file_to_string(void)
{
   //Create an int that will hold the file descriptor
	int fd;
	int status;
	int size;

	status = 1;

	//Allocate a memory block large enough to hold read output, including an extra byte for null terminator.
	size = get_file_size();
	test.raw = (char *)malloc(sizeof(char) * (size));

	//Open the file
	fd = open(test.file_path, O_RDONLY);

	//Read size bytes from the file to our string.
	//Returns above 0 are the number of bytes read
	status = read(fd, test.raw, size);
   
	//Null terminate the string at last byte
	test.raw[size] = '\0';

	//Close the file
	status = close(fd);
	//Need to handle error reporting. We can return a null string on error. Might need to split open and close into seperate functions that return fd
	if (status == -1 || fd == -1)
	   return (-1);
   else
		return (1);
}


int	main(void)
{
	int	status;
	test.file_path = "map.txt";
	status = file_to_string();

	printf("%s\n", test.raw);
	return (0);
}