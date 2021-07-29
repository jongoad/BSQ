/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:12:06 by jgoad             #+#    #+#             */
/*   Updated: 2021/07/28 21:12:12 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_header.h"

int	sq_calc(int x_pos, int y_pos, t_data maps)
{
	int	x;
	int	y;
	int	size;

	size = 0;
	x = x_pos;
	y = y_pos;
	while ((maps.map[x + (maps.width + 1) * y] != maps.legend[1])
		&& y < maps.height && x < maps.width)
	{
		size++;
		x = x_pos;
		y = y_pos + size;
		while ((maps.map[x + (maps.width + 1) * y] != maps.legend[1])
			&& x < x_pos + size && x < maps.width && y < maps.height && y > 0)
		{
			x++;
			if (maps.map[x + (maps.width + 1) * y] == maps.legend[1])
				return (size);
			while (x == x_pos + size && y-- > y_pos)
				if (maps.map[x + (maps.width + 1) * y] == maps.legend[1])
					return (size);
		}
	}
	return (size - 1);
}

void	solver(t_data maps)
{
	int	x_pos_biggest;
	int	y_pos_biggest;
	int	size;

	if (maps.error_status == 1)
	{
		ft_putstr("map error", 2);
		ft_putchar(10, 2);
		return ;
	}
	size = find_biggest_square(&x_pos, &y_pos, maps);
	if (maps.error_status == 0)
	{
		print_full_square(x_pos_biggest, y_pos_biggest, size, maps);
		ft_putchar(10, 2);
	}
}

int	find_big_sq(int *x_pos_biggest, int *y_pos_biggest, t_data maps)
{
	int	x_pos;
	int	y_pos;
	int	size;

	y_pos = 0;
	x_pos = 0;
	size = sq_calc(x_pos, y_pos, maps);
	*x_pos_biggest = x_pos;
	*y_pos_biggest = y_pos;
	while (y_pos < maps.height)
	{
		x_pos = 0;
		while (x_pos < maps.width)
		{
			if (sq_calc(x_pos, y_pos, maps) > size)
			{
				size = sq_calc(x_pos, y_pos, maps);
				*x_pos_biggest = x_pos;
				*y_pos_biggest = y_pos;
			}
			x_pos++;
		}
		y_pos++;
	}
	return (size);
}

void	print_full_square(int x_pos, int y_pos, int size, t_data maps)
{
	int	x;
	int	y;

	y = 0;
	while (y < maps.height)
	{
		x = 0;
		while (x <= maps.width)
		{
			if ((x >= x_pos && x < (x_pos + size))
				&& y >= y_pos && y < (y_pos + size))
				write (1, &maps.legend[2], sizeof(char));
			else
				write (1, &maps.map[x + (maps.width + 1) * y], sizeof(char));
			x++;
		}
		y++;
	}
}
