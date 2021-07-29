#include "ft_header.h"


//Function to read the legend and convert to a char array, and get number of lines (height)
s_data	get_legend(s_data maps)
{
	int i;
	int	leg_len;

	maps.height = 0;
	i = 0;
	//Get number of lines, then number of lines is everything before last 3 chars.
	while (maps.raw_str[i] != '\n')
		i++;
	leg_len = i;
	i = 0;
	while (i < leg_len - 3)
	{
		maps.height = (maps.height * 10) + maps.raw_str[i] - '0';
		i++;
	}
	//Now get rest of chars
	maps.legend[0] = maps.raw_str[i];
	maps.legend[1] = maps.raw_str[i + 1];
	maps.legend[2] = maps.raw_str[i + 2];
	maps.legend[3] = '\0';
	return (maps);
}

//Function to drive all of the parsing functions
s_data	check_all(s_data maps)
{
	maps = check_legend(maps);
	maps = check_map_chars(maps);
	maps = check_map_lines(maps);
	maps = check_map_height(maps);
	return (maps);
}

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
	//Return error or size of file
	if (status == -1 || fd == -1)
		maps.error_status = 1;
	return (count);
}

//Function to convert entire map into a char array
s_data file_to_string(s_data maps)
{
   //Create an int that will hold the file descriptor
	int fd;
	int status;

	status = 1;
	//Allocate a memory block large enough to hold read output, including an extra byte for null terminator.
	maps.size = get_file_size(maps);
	maps.raw_str = (char *)malloc(sizeof(char) * (maps.size));

	//Open the file
	fd = open(maps.file_path, O_RDONLY);

	//Read size bytes from the file to our string.
	//Returns above 0 are the number of bytes read
	status = read(fd, maps.raw_str, maps.size);
   
	//Null terminate the string at last byte
	maps.raw_str[maps.size] = '\0';

	//Close the file
	status = close(fd);
	//Need to handle error reporting. We can return a null string on error. Might need to split open and close into seperate functions that return fd
	if (status == -1 || fd == -1)
		maps.error_status = 1;
	return (maps);
}

