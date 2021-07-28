#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
/*
struct setup{
	char *raw;
	char *map;
	char legend[4];
	char *file_path;
	int dimension[2];
	int width;
	int	height;
	int	key;
}test; */

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

//Function to convert entire map into a char array
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
		return (size);
}






//Function to read the legend and convert to a char array
//May need to split into check and convert as seperate functions
int	get_legend(char *raw_str, char *legend, int *dimension)
{
	int i;
	int	status; //0 is starting, 1 is found lines, 2 is found empty, 3 is found obstacle, 4 is found fill

	status = 0;
	i = 0;
	while (raw_str[i] != '\n')
	{
		if (raw_str[i] >= '0' && raw_str[i] <= '9' && status == 0) //Amount of lines (CAN BE DOUBLE DIGIT< FIX THIS)
		{

			dimension[1] = raw_str[i] - '0';
			status = 1;
		}

		if (raw_str[i] >= 32 && status == 1) //Empty char
		{
			legend[0] = raw_str[i];
			status = 2;
		}
		else if (raw_str[i] >= 32 && status == 2) //Obstacle char
		{
			legend[1] = raw_str[i];
			status = 3;
		}
		else if (raw_str[i] >= 32 && status == 3) //Fill char
		{
			legend[2] = raw_str[i];
			status = 4;
		}
		i++;
	}
	if (raw_str[i] == '\n' && status == 4)
		return (1);
	else
		return (0);
}

//Function to ensure char is part of the legend
int	check_legend(char c, char *legend)
{
	int i;
	int	is_valid;
	int	is_obst;

	is_valid = 0;
	is_obst = 0;
	i = 0;
	while (legend[i] != '\0')
	{
		if (c == legend[i])
			is_valid = 1;
		if (c == legend[1])
			is_obst = 1;
		i++;
	}
	if (is_valid == 1 && is_obst == 1)
		return (2);
	else if (is_valid  == 1)
		return (1);
	else
		return (0);
}

//Function to check that map only contains valid chars
int	check_map_chars(char *raw_str, char *legend, int size)
{
	int i;
	int found_lines;
	int	found_obst;
	
	found_lines = 0;
	found_obst = 0;
	i = 0;
	while (i < size)
	{
		if (raw_str[i] >= '0' && raw_str[i] <= '9' && found_lines == 0)
		{
			found_lines = 1;
			i++;
		}
		if (check_legend(raw_str[i], legend) == 0 && raw_str[i] != '\n')
			return (0);
		else if (check_legend(raw_str[i], legend) == 2)
			found_obst = 1;
		i++;
	}
	if (found_obst == 0)
		return (0);
	else
		return (1);
}



//Function to make sure number of map lines is correct
//int	check_map_height(char *raw_str,int *dimension, int size)



//Function to make sure line lengths are correct
//MAP HEIGHT AND WIDTH ARE THE SAME!!!!
int	check_map_lines(char *raw_str, int *dimension, int size)
{
	int i;
	int	line_len_first;
	int	line_len;
	int	line_c;

	i = 0;
	line_len_first = 0;
	line_len = 0;
	line_c = 0;

	while (raw_str[i] != '\n' && line_c == 0) // Iterate to end of first line to avoid legend.
		i++;
	if (raw_str[i] == '\n')
	{
			line_c = 1;
			i++;
	}
	while (raw_str[i] != '\n' && line_c == 1) //Get length of first map line
	{
		line_len_first++;
		i++;
	}
	if (raw_str[i] == '\n')
	{
			line_c++;
			i++;
	}
	printf("first width is %d\n", line_len_first);
	while (i < size) //Check length of the rest of the lines and get total height
	{
		line_len = 0;
		while (raw_str[i] != '\n')
		{
			line_len++;
			i++;
		}
		if (raw_str[i] == '\n')
		{
				line_c++;
		}
		printf("current width is %d\n", line_len);
		if (line_len != line_len_first) //If line_len is not same as first map line, return map error
			return (0);
		i++;
	}
	dimension[0] = line_len_first;
	if (line_c - 1 != dimension[1]) //If total lines is not equal to height, map error
		return (0);
	else
		return (1);
}

//REDO THIS- STILL NEEDS TO CHECK FOR LINE LENGTH< TOTAL LINE < AT LEAST ONE OBST
int	check_map(char *raw_str, char *legend, int *dimension, int size)
{
	int status;

	status = check_map_chars(raw_str, legend, size);
	if (status == 0)
		return (0);
	status = check_map_lines(raw_str, dimension, size);
		printf("status is %d\n", status);
	if (status == 0)
		return (0);
	else
		return (1);		
}

//Function to parse map and ensure validity of map(line length, symbol legend), and fill legend and board
int	check_get_map(char *raw_str, char *legend, int *dimension, int size)
{
	int	status;

	//Need to pass the current map in each time, so change this after test
	status = get_legend(raw_str, legend, dimension);
	if (status == 0)
		return (0);
	status = check_map(raw_str, legend, dimension, size);
	if (status == 0)
		return (0);
	else
		return (1);
}




//RULES:
//Every line must have a line break
//There must be at least one obstacle? Or maybe just needs to be minimum two lines for a box to be found?
//All map lines must be the same length
//Must be 3 legend chars on first line
//Legend chars must be unique (no duplicate)
//Chars on map can only be those from legend


//TEST MAIN
int	main(void)
{	
	int size;
	int	status;

	test.file_path = "map3.txt";
	size = file_to_string();
	if (size < 0)
		printf("malloc error\n");
		//return (0);
	status = check_get_map(test.raw, test.legend, test.dimension, size);
	printf("status is %d\n", status);
	printf("legend is %s\n", test.legend);
	printf("test.height is %d\n", test.dimension[1]);
	//printf("size is %d\n", size);
	//printf("%s\n", test.raw);
	return (0);
}