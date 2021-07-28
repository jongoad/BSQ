#include <unistd.h>
#include <stdio.h>
typedef struct {
	char *raw_str;
	int size;
	char *map;
	char *file_path;
	char legend[4];
	int width;
	int	height;
	int	error_status;
} s_data;

void	print_full_square(int x_pos, int y_pos, int size, s_data maps);
int sq_calc(int x_pos, int y_pos, s_data maps);

void	printmap(s_data maps);

int sq_calc(int x_pos, int y_pos, s_data maps)
{
	int	x;
	int	y;
	int	size;

	size = 0;
	x = x_pos;
	y = y_pos;
	while (maps.map[x + (maps.width + 1) * y] != maps.legend[1] && y < maps.height && x < maps.width)
	{
		size++;
		x = x_pos - 1;
		y = y_pos + size;
			while (++x <= x_pos + size && x < maps.width && y < maps.height)
			{
				if (maps.map[x + (maps.width + 1) * y] == maps.legend[1])
						return (size - 1);
				while (x == x_pos + size && y >= y_pos)
				{
					y--;
					if (maps.map[x + (maps.width + 1) * y] == maps.legend[1])
						return (size - 1);
				}
			}
	}
	return (size - 1);
}

//NOTE: if  is smaller than , sq_size = y,
//but the new x_pos needs to be x_pos + x, because there might be a bigger square 1 further
#include <time.h>


void	solver(s_data maps)
{
	int	x_pos;
	int	y_pos;
	int	x_pos_biggest;
	int	y_pos_biggest;
	int size;

	//printmap(maps);
	printf("map height = %d; map width = %d\n", maps.height, maps.width);

	time_t begin, end;
    time(&begin);
	y_pos = 0;
	x_pos = 0;
	size = sq_calc(x_pos, y_pos, maps);
	x_pos_biggest = x_pos;
	y_pos_biggest = y_pos;
	printf("Biggest is [%d, %d], size = %d\n", x_pos_biggest, y_pos_biggest, size);
	while (y_pos < maps.height)
	{
		x_pos = 0;
		while (x_pos < maps.width)
		{
			if (sq_calc(x_pos, y_pos, maps) > size)
			{
				size = sq_calc(x_pos, y_pos, maps);
				x_pos_biggest = x_pos;
				y_pos_biggest = y_pos;
				printf("Biggest is [%d, %d], size = %d\n", x_pos_biggest, y_pos_biggest, size);
			}
			x_pos++;
		}
		y_pos++;
	}
	printf("coords of biggest : [%d, %d]\n", x_pos_biggest, y_pos_biggest);
	printf("map height at the end = %d; map width = %d\n", maps.height, maps.width);

	printmap(maps);
	printf("pos_x = %d, pos_y = %d, possible square size = %d\n", x_pos_biggest, y_pos_biggest, size);
	print_full_square(x_pos_biggest, y_pos_biggest, size, maps);
	printf("Time measured: %ld seconds.\n", elapsed);

}

void	print_full_square(int x_pos, int y_pos, int size, s_data maps)
{
	int x;
	int y;

	y = 0;
	while (y < maps.height)
	{
		x = 0;
		while (x <= maps.width)
		{
			if (x >= x_pos && x < (x_pos + size) && y >= y_pos && y < (y_pos + size))
				write (1, &maps.legend[2], sizeof(char));
			else
				write (1, &maps.map[x + (maps.width + 1) * y], sizeof(char));
			x++;
		}
		y++;
	}
}

void	printmap(s_data maps)
{
	int x = 0;
	int y = 0;
	
	while (y < maps.height)
	{
		x = 0;
		while (x <= maps.width)
		{
			write (1, &maps.map[x + (maps.width + 1) * y], sizeof(char));
			x++;
		}
		y++;
	}
	return ;
}













