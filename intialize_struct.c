#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
	char *raw_str;
	char *map;
	char *file_path;
	char legend[4];
	int width;
	int	height;
	int	error_status;
} s_data;

//Function to get the total size of the map file to malloc an array
int get_file_size(s_data maps)
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
	fd = open(maps.file_path, O_RDONLY);
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
	printf("size is %d\n", count);
	//Return error or size of file
	if (status == -1 || fd == -1)
		maps.error_status = 1;
	return (count);
}

//Function to convert entire map into a char array
char* file_to_string(s_data maps)
{
   //Create an int that will hold the file descriptor
	int fd;
	int status;
	int size;

	status = 1;

	//Allocate a memory block large enough to hold read output, including an extra byte for null terminator.
	size = get_file_size(maps);
	maps.raw_str = (char *)malloc(sizeof(char) * (size));

	//Open the file
	fd = open(maps.file_path, O_RDONLY);

	//Read size bytes from the file to our string.
	//Returns above 0 are the number of bytes read
	status = read(fd, maps.raw_str, size);
   
	//Null terminate the string at last byte
	maps.raw_str[size] = '\0';

	//Close the file
	status = close(fd);
	printf("%s\n", maps.raw_str);
	//Need to handle error reporting. We can return a null string on error. Might need to split open and close into seperate functions that return fd
	if (status == -1 || fd == -1)
		maps.error_status = 1;
	return (maps.raw_str);
}




//Function to initialize struct array members and make calls to other init functions
s_data* init_structs(int	argc, char	**argv, s_data* maps)
{
	int i;

	i = 0;
	while (i < argc)
	{
		maps[i].file_path = *(argv + i + 1);
		maps[i].raw_str = file_to_string(maps[i]);
		printf("%s\n", maps[i].raw_str);
		i++;
	}
	return (maps);
}



//Main function to drive the entire program
//Move into its own file after testing
int	main(int	argc, char	**argv)
{
	//First thing we must do is declare our structs and assign memory
	s_data *maps = NULL;
	maps = malloc(sizeof(*maps) * (argc - 1));

	//Now we run out struct initialization function
	maps = init_structs(argc, argv, maps);

	//Test print
	int i;

	i = 0;
	while (i < argc - 1)
	{
		printf("path is %s.\nwidth is %d.\nheight is %d.\n", maps[i].file_path, maps[i].width, maps[i].height);
		printf("map %d contains:\n%s\n", i, maps[i].raw_str);
		printf("\n");
		i++;
	}
	//Right before program return free memory
	free(maps);
}