#include "ft_header.h"

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

