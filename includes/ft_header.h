/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:08:53 by jgoad             #+#    #+#             */
/*   Updated: 2021/07/28 21:14:07 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_HEADER_H
# define FT_HEADER_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct t_data{
	char	*raw_str;
	int		size;
	char	*map;
	char	*file_path;
	char	legend[4];
	int		width;
	int		height;
	int		error_status;
}	t_data;

void	ft_putchar(char c, int stream);
void	ft_putstr(char *str, int stream);
int		get_file_size(t_data maps);
t_data	file_to_string(t_data maps);
t_data	get_legend(t_data maps);
t_data	check_legend(t_data maps);
int		is_legend(char c, t_data maps);
t_data	check_map_chars(t_data maps);
t_data	check_map_lines(t_data maps);
t_data	check_map_height(t_data maps);
t_data	check_all(t_data maps);
char	*write_map(t_data maps);
char	*no_args(void);
t_data	*init_structs_stdin(t_data	*maps);
t_data	*init_structs(int	argc, char	**argv, t_data	*maps);
void	solver(t_data maps);
void	print_full_square(int x_pos, int y_pos, int size, t_data maps);
void	solver(t_data maps);
int		sq_calc(int x_pos, int y_pos, t_data maps);
int		find_big_sq(int *x_pos_biggest, int *y_pos_biggest, t_data maps);

#endif
