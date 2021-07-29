/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:10:19 by jgoad             #+#    #+#             */
/*   Updated: 2021/07/28 21:10:23 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_header.h"

t_data	get_legend(t_data maps)
{
	int	i;
	int	leg_len;

	maps.height = 0;
	i = 0;
	while (maps.raw_str[i] != '\n')
		i++;
	leg_len = i;
	i = 0;
	while (i < leg_len - 3)
	{
		maps.height = (maps.height * 10) + maps.raw_str[i] - '0';
		i++;
	}
	maps.legend[0] = maps.raw_str[i];
	maps.legend[1] = maps.raw_str[i + 1];
	maps.legend[2] = maps.raw_str[i + 2];
	maps.legend[3] = '\0';
	return (maps);
}

t_data	check_all(t_data maps)
{
	maps = check_legend(maps);
	maps = check_map_chars(maps);
	maps = check_map_lines(maps);
	maps = check_map_height(maps);
	return (maps);
}

int	get_file_size(t_data maps)
{
	int		count;
	int		fd;
	int		status;
	char	*c;

	count = 0;
	status = 1;
	c = (char *)malloc(sizeof(char));
	fd = open(maps.file_path, O_RDONLY);
	while (status > 0 && fd != -1)
	{
		status = read(fd, c, 1);
		if (status > 0)
			count++;
	}
	free(c);
	status = close(fd);
	if (status == -1 || fd == -1)
		maps.error_status = 1;
	return (count);
}

t_data	file_to_string(t_data maps)
{
	int	fd;
	int	status;

	status = 1;
	maps.size = get_file_size(maps);
	maps.raw_str = (char *)malloc(sizeof(char) * (maps.size));
	fd = open(maps.file_path, O_RDONLY);
	status = read(fd, maps.raw_str, maps.size);
	maps.raw_str[maps.size] = '\0';
	status = close(fd);
	if (status == -1 || fd == -1)
		maps.error_status = 1;
	return (maps);
}
