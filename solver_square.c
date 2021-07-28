#include <unistd.h>
#include <stdio.h>

int sq_calc_sq(int x_pos, int y_pos, char *map, int width, int height)
{
	int	x;
	int	y;
	int	size;

	size = 0;
	x = x_pos;
	y = y_pos;
	while (map[x + (width + 1) * y] != 'o' && y < height && x < width)
	{
		size++;
		x = x_pos;
		y = y_pos + size - 1;
			while (++x < x_pos + size - 1 && x < width)
			{
				if (map[x + (width + 1) * y] == 'o')
						return (size - 1);
				while (x == x_pos + size - 1 && y > y_pos)
				{
					y--;
					if (map[x + (width + 1) * y] == 'o')
						return (size - 1);
				}
			}
	}
	return (size - 1);
}

#include <time.h>
void	print_full_square(int x_pos, int y_pos, int size, int width, int height, char *map);

int	main(void)
{
	char *map = "...........................\n...........................\n....o.......o..............\n...........................\n....o......................\n...............o...........\n...........................\n......o..............o.....\n..o.......o................\n";
	int height = 9;
	int width = 27;
	int x_pos = 0;
	int y_pos = 0;
	int	x_pos_biggest = 0;
	int y_pos_biggest = 0;

	time_t begin, end;
    time(&begin);
	int size = sq_calc_sq(x_pos, y_pos, map, width, height);
	printf("For this map :\n%s\npos_x = %d, pos_y = %d, possible square size = %d\n", map, x_pos, y_pos, size);
	print_full_square(x_pos, y_pos, size, width, height, map);
/*	
	while (y_pos < height)
	{
		x_pos = 0;
		while (x_pos < width)
		{
			if (square_size(&x_pos, &y_pos, map, width, height) > size)
			{
				size = square_size(&x_pos, &y_pos, map, width, height);
				x_pos_biggest = x_pos;
				y_pos_biggest = y_pos;
			}
			x_pos++;
		}
		y_pos++;
	}

	printf("coords of biggest : [%d, %d]\n", x_pos_biggest, y_pos_biggest);
	time(&end);
    time_t elapsed = end - begin;

	printf("For this map :\n%s\npos_x = %d, pos_y = %d, possible square size = %d\n", map, x_pos, y_pos, size);
	print_full_square(x_pos_biggest, y_pos_biggest, size, width, height, map);
	printf("Time measured: %ld seconds.\n", elapsed);
*/
}

void	print_full_square(int x_pos, int y_pos, int size, int width, int height, char *map)
{
	int x;
	int y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x <= width)
		{
			if (x >= x_pos && x < (x_pos + size) && y >= y_pos && y < (y_pos + size))
				write (1, "x", sizeof(char));
			else
				write (1, &map[x + (width + 1) * y], sizeof(char));
			x++;
		}
		y++;
	}
}