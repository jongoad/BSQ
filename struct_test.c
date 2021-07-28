//Test to see if we can make an array of structs in main to be passed around the program
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char *raw;
	char *map;
	char legend[4];
	char *file_path;
	int width;
	int	height;
	int	key;
} map;


int	main(int argc, char **argv)
{
	int	map_count;
	int	i;

	//Number of required struct members is the number of arguments passed minus program name
	map_count = argc - 1;
	i = 0;
	// Initialize a NULL array of struct map members
	map *maps = NULL;

	//Malloc memory for the array of struct members
	maps = malloc(sizeof(*maps) * map_count);

	if (!maps) 
	{ /* validate all memory allocations */
    	fprintf (stderr, "error: virtual memory exhausted.\n");
        return 1;
	}
	//Assign values to struct members
	while (i < map_count)
	{
		maps[i].file_path = *(argv + i + 1);
		maps[i].width = 1 + i;
		maps[i].height = 10 + i;
		maps[i].key = i;
		i++;
	}
	i = 0;
	while (i < map_count)
	{
		printf("path is %s.\nwidth is %d.\nheight is %d.\nkey value is %d.\n", maps[i].file_path, maps[i].width, maps[i].height, maps[i].key);
		printf("\n");
		i++;
	}

	free (maps);

	return (0);
}

//IF NO ARGS PASSED, SWITCH TO READING ON STANDARD INPUT