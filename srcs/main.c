/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:46 by jgoad             #+#    #+#             */
/*   Updated: 2021/07/28 21:09:52 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_header.h"

void	ft_putchar(char c, int stream)
{
	write(stream, &c, 1);
}

void	ft_putstr(char *str, int stream)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], stream);
		i++;
	}
}

int	main(int	argc, char	**argv)
{
	int		i;
	t_data	*maps;

	i = 0;
	maps = NULL;
	maps = malloc(sizeof(*maps) * (argc - 1));
	if (argc == 1)
		maps = init_structs_stdin(maps);
	else
		maps = init_structs(argc, argv, maps);
	if (argc == 1)
		solver(maps[0]);
	else
	{
		while (i < argc - 1)
		{
			solver(maps[i]);
			i++;
		}
	}
	free(maps);
	return (0);
}
