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
		x = x_pos;
		y = y_pos + size;
		if (x_pos == 10 && y_pos == 2)
					printf("size loop x = %d and y = %d, size = %d\n", x, y, size);
			while (maps.map[x + (maps.width + 1) * y] != maps.legend[1] && x < x_pos + size && x < maps.width && y < maps.height && y > 0)
			{
				x++;
				if (x_pos == 10 && y_pos == 2)
					printf(" x loop x = %d and y = %d, size = %d\n", x, y, size);
				if (maps.map[x + (maps.width + 1) * y] == maps.legend[1])
						return (size);
				while (x == x_pos + size && y > y_pos)
				{
						y--;
					if (x_pos == 10 && y_pos == 2)
						printf("  y loop x = %d and y = %d, size = %d\n", x, y, size);
					if (maps.map[x + (maps.width + 1) * y] == maps.legend[1])
						return (size);
				
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













