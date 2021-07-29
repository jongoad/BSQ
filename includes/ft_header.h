#ifndef FT_HEADER_H
# define FT_HEADER_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef struct {
	char	*raw_str;
	int		size;
	char	*map;
	char	*file_path;
	char	legend[4];
	int		width;
	int		height;
	int		error_status;
} s_data;

void	ft_putchar(char c, int stream);
void	ft_putstr(char *str, int stream);
int get_file_size(s_data maps);
s_data file_to_string(s_data maps);
s_data	get_legend(s_data maps);
s_data check_legend(s_data maps);
int	is_legend(char c, s_data maps);
s_data	check_map_chars(s_data maps);
s_data	check_map_lines(s_data maps);
s_data	check_map_height(s_data maps);
s_data	check_all(s_data maps);
char* write_map(s_data maps);
char	*no_args(void);
s_data* init_structs_stdin(s_data* maps);
s_data* init_structs(int	argc, char	**argv, s_data* maps);
void	solver(s_data maps);

void	print_full_square(int x_pos, int y_pos, int size, s_data maps);
void	solver(s_data maps);
int sq_calc(int x_pos, int y_pos, s_data maps);


#endif