#include <unistd.h>
#include <stdio.h>
struct s_biggest
{
	int	x_pos;
	int	y_pos;
	int	size;
} t_biggest;

struct s_square
{
	int	l_bound;
	int	r_bound;
	int	t_bound;
	int	d_bound;
	int	size;
} t_square;

struct setup{
	char *raw;
	char *map;
	char legend[4]; //0 = 'empty', 1 = 'obstacle'
	char *file_path;
	int width;
	int	height;
	int	key;
} test;

//returns the biggest value between two ints
//cmp == b will return biggest 
//cmp == s will return smallest
int	int_cmp(int a, int b, char cmp)
{
	if (a >= b && cmp == 'b')
		return (a);
	if (a <= b && cmp == 's')
		return (a);
	return (b);
}

int	square_height(int x_pos, int y_pos, int sq_width, int width, int height, char *map)
{
	char	cursor;
	int		x;
	int		y;

	x = x_pos;
	y = y_pos;
	printf("in the square_height fct, the sq_width passed is %d\n", sq_width);
	while (map[x + (width + 1) * y] != 'o' && y < height)
	{
		x++;
		if (x == x_pos + sq_width - 1)
		{
			x = x_pos;
			y++;
		}
		printf("sq_height pos_x = %d, pos_y = %d, cursor = %c\n", x, y, map[x + (width + 1) * y]);
	}
	return (y - y_pos);
}

int	square_size(int *x_pos, int *y_pos, char *map, int width, int height)
{
	int	x;
	int	y;
	int sq_width;
	int	sq_height;

	x = *x_pos;
	y = *y_pos;
	sq_width = width - *x_pos;
	while (map[x + (width + 1) * y] != 'o' && y < height && y - *y_pos < sq_width)
	{
		x++;
		if (x == width)
		{
			x = *x_pos;
			y++;
		}
		printf("sq_size pos_x = %d, pos_y = %d, cursor = %c\n", x, y, map[x + (width + 1) * y]);
	}
	sq_width = int_cmp(sq_width, x - *x_pos, 's');
	printf("sq_width = %d and height = %d\n", sq_width, y - *y_pos);
	if (sq_width > y - *y_pos)
	{
		y += square_height(*x_pos, y, (x - *x_pos), width, height, map);
		return (int_cmp(y - *y_pos, sq_width, 's'));
	}
	return (int_cmp(y - *y_pos, sq_width, 'b'));
}






//NOTE: if  is smaller than , sq_size = y,
//but the new x_pos needs to be x_pos + x, because there might be a bigger square 1 further

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


	int size = square_size(&x_pos, &y_pos, map, width, height);
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

	printf("For this map :\n%s\npos_x = %d, pos_y = %d, possible square size = %d\n", map, x_pos, y_pos, size);
	print_full_square(x_pos_biggest, y_pos_biggest, size, width, height, map);

}

void	print_full_square(int x_pos, int y_pos, int size, int width, int height, char *map)
{
	int xndex;
	int yndex;

	yndex = 0;
	while (yndex < height)
	{
		xndex = 0;
		while (xndex <= width)
		{
			if (xndex >= x_pos && xndex < (x_pos + size) && yndex >= y_pos && yndex < (y_pos + size))
				write (1, "x", sizeof(char));
			else
				write (1, &map[xndex + (width + 1) * yndex], sizeof(char));
			xndex++;
		}
		yndex++;
	}
}















