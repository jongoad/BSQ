#include "ft_header.h"

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

s_data	check_map_chars(s_data maps)
{
	int i;
	int	found_obst;
	
	found_obst = 0;
	i = 0;
	while (maps.raw_str[i] != '\n')
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

s_data	check_map_lines(s_data maps)
{
	int i;
	int	line_len;

	i = 0;
	while (maps.raw_str[i] != '\n' && maps.raw_str[i] != '\0')
		i++;
	i++;
	while (maps.raw_str[i] != '\n' && maps.raw_str[i] != '\0')
	{
		maps.width++;
		i++;
	}
	while (++i < maps.size && maps.raw_str[i] != '\0')
	{
		line_len = 0;
		while (maps.raw_str[i] != '\n' && maps.raw_str[i] != '\0')
		{
			line_len++;
			i++;
		}
		if (line_len != maps.width)
			maps.error_status = 1;
	}
	return (maps);
}

s_data	check_map_height(s_data maps)
{
	int i;
	int	line_count;

	i = 0;
	line_count = 0;
	while (maps.raw_str[i] != '\n' && maps.raw_str[i] != '\0')
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
