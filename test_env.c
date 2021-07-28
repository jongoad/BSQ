#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
	char *raw_str;
	int size;
	char *map;
	char *file_path;
	char legend[4];
	int width;
	int	height;
	int	error_status;
} s_data;

/**********************************************************************************************/
/*                                  Status: COMPLETE                                          */
/**********************************************************************************************/
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

/**********************************************************************************************/
/*                                  Status: COMPLETE                                          */
/**********************************************************************************************/


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

//Function to check that legend contains valid chars and no duplicates//WORKING
s_data check_legend(s_data maps)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (maps.legend[i] != '\0')
	{
		if (maps.legend[i] < 32)
			maps.error_status = 1;
		j = 1;
		while (maps.legend[i + j] != '\0')
		{
			if (maps.legend[i] == maps.legend[i + j])
				maps.error_status = 1;
			j++; 
		}
		i++;
	}
	return (maps);
}
//Function to ensure char is part of the legend
//DOUBLE CHECK THIS
int	is_legend(char c, s_data maps)
{
	int i;
	int	is_valid;
	int	is_obst;

	is_valid = 0;
	is_obst = 0;
	i = 0;
	while (maps.legend[i] != '\0')
	{
		if (c == maps.legend[i])
			is_valid = 1;
		if (c == maps.legend[1])
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

//Function to check that map only contains valid chars//WORKING
s_data	check_map_chars(s_data maps)
{
	int i;
	int	found_obst;
	
	found_obst = 0;
	i = 0;
	while (maps.raw_str[i] != '\n') //Skip first line
		i++;
	i++;
	while (i < maps.size)
	{
		if (is_legend(maps.raw_str[i], maps) == 0 && maps.raw_str[i] != '\n')
			maps.error_status = 1;
		else if (is_legend(maps.raw_str[i], maps) == 2)
			found_obst = 1;
		i++;
	}
	if (found_obst == 0)
		maps.error_status = 1;
	return (maps);
}

//Function to make sure line lengths are correct//WORKING
s_data	check_map_lines(s_data maps)
{
	int i;
	int	line_len;

	i = 0;
	while (maps.raw_str[i] != '\n' && maps.raw_str[i] != '\0') // Iterate to end of first line to avoid legend.
		i++;
	i++;
	while (maps.raw_str[i] != '\n' && maps.raw_str[i] != '\0') //Get length of first map line
	{
		maps.width++;
		i++;
	}
	while (++i < maps.size && maps.raw_str[i] != '\0') //Check length of the rest of the lines and get total height
	{
		line_len = 0;
		while (maps.raw_str[i] != '\n' && maps.raw_str[i] != '\0')
		{
			line_len++;
			i++;
		}
		if (line_len != maps.width) //If line_len is not same as first map line, return map error
			maps.error_status = 1;
	}
	return (maps);
}

//Function to check that maps has correct number of lines//WORKING
s_data	check_map_height(s_data maps)
{
	int i;
	int	line_count;

	i = 0;
	line_count = 0;
	while (maps.raw_str[i] != '\n' && maps.raw_str[i] != '\0') // Iterate to end of first line to avoid legend.
		i++;
	i++;
	while (i < maps.size)
	{
		while(maps.raw_str[i] != '\n' && maps.raw_str[i] != '\0' && (is_legend(maps.raw_str[i], maps) > 0))
		{
			i++;
		}
		line_count++;
		i++;
	}
	if (line_count != maps.height)
		maps.error_status = 1;
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


//Function to write final array for output to solver
char* write_map(s_data maps)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	maps.map = (char *)malloc(sizeof(char) * (maps.size + 10));
	while (maps.raw_str[i] != '\n') // Iterate to end of first line to avoid legend.
		i++;
	i++;
	while (i < maps.size)
	{
		maps.map[j] = maps.raw_str[i];
		i++;
		j++;
	}
	maps.map[i] = '\0';
	return (maps.map);
}


/**********************************************************************************************/
/*                                  Status: COMPLETE                                          */
/**********************************************************************************************/

char	*no_args(void)
{
	char	buf;
	int		fd;

	fd = open("stdin_map", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (read(STDIN_FILENO, &buf, 1))
	{
		write(fd, &buf, 1);
	}
	close(fd);
	return ("stdin_map");
}

//If no files are passed as args, read from standard input
s_data* init_structs_stdin(s_data* maps)
{	
	maps[0].error_status = 0;
	maps[0].width = 0;
	maps[0].file_path = no_args();
	maps[0] = file_to_string(maps[0]);
	maps[0] = get_legend(maps[0]);
	maps[0] = check_all(maps[0]);
	if (maps[0].error_status == 0)
		maps[0].map = write_map(maps[0]);

	return (maps);
}

//Function to initialize struct array members and make calls to other init functions
s_data* init_structs(int	argc, char	**argv, s_data* maps)
{
	int i;

	i = 0;
	while (i < argc - 1)
	{
		//maps[i].size = get_file_size(maps[i]);
		maps[i].error_status = 0;
		maps[i].width = 0;
		maps[i].file_path = *(argv + i + 1);
		maps[i] = file_to_string(maps[i]);
		maps[i] = get_legend(maps[i]);
		maps[i] = check_all(maps[i]);
		if (maps[i].error_status == 0)
			maps[i].map = write_map(maps[i]);
		i++;
	}
	return (maps);
}


//Main function to drive the entire program
//Move into its own file after testing
int	main(int	argc, char	**argv)
{
	int i;

	i = 0;
	//First thing we must do is declare our structs and assign memory
	s_data *maps = NULL;
	maps = malloc(sizeof(*maps) * (argc - 1));


	if (argc == 1)
		maps = init_structs_stdin(maps);
	else
		maps = init_structs(argc, argv, maps);

	//Test print
	if (argc == 1)
	{
		printf("path is %s.\nwidth is %d.\nheight is %d.\n", maps[i].file_path, maps[i].width, maps[i].height);
		printf("error status is %d\n", maps[i].error_status);
		printf("legend is %s\n", maps[i].legend);
		printf("map %d contains:\n%s\n", i, maps[i].raw_str);
		printf("\n");
		printf("final map output is:\n%s", maps[i].map);
		printf("\n");
	}
	
	//Test print
	while (i < argc - 1)
	{
		printf("path is %s.\nwidth is %d.\nheight is %d.\n", maps[i].file_path, maps[i].width, maps[i].height);
		printf("error status is %d\n", maps[i].error_status);
		printf("legend is %s\n", maps[i].legend);
		printf("map %d contains:\n%s\n", i, maps[i].raw_str);
		printf("\n");
		printf("final map output is:\n%s", maps[i].map);
		printf("\n\n");
		i++;
	}
	//Right before program return free memory
	free(maps);
	return (0);
}

//To do

//Output error to stderr
//Makefile
//Header file
//Test

