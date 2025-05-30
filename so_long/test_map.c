#include <stdio.h>

void fill(char **arr, int x, int y)
{
	if (arr[y][x] == '1' || arr[y][x] == 'X' || arr[y][x] == 'E')
		return ;
	else if (arr[y][x] != 'P')
		arr[y][x] = 'X';
	fill(arr, x, y + 1);
	fill(arr, x, y - 1);
	fill(arr, x - 1, y);
	fill(arr, x + 1, y);
	printf("x: %i y: %i\n", x, y);
}

int main(int argc, char **argv)
{
	fill(argv + 1, 1, 3);
	printf("%c\n", argv[4][1]);
	//printf("HERE WE GO!\n");
	for (int i = 1; i < argc; i++)
		printf("%s\n", argv[i]);
	
}