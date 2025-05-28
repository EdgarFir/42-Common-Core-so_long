#include "so_long.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>

void init_game()
{
	void *mlx_ptr;
	void *win_ptr;
	void *sprite;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1250, 500, "so_long 42");
	int x;
	int y;
	sprite = mlx_xpm_file_to_image(mlx_ptr, "sprites/exit.xpm", &x, &y);
	mlx_put_image_to_window(mlx_ptr, win_ptr, sprite, 750 / 2, 250 / 2);
	mlx_loop(mlx_ptr);
}

int main()
{
	int fd = open("maps/map1.ber", O_RDONLY);
	printf("%i\n", fd);

	void *mlx_ptr;
	void *win_ptr;
	void *player;
	void *collect;
	void *floor;
	int	 height;
	int  width;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 5 * 64, 5 * 64, "so_long 42");
	int x;
	int y;
	player = mlx_xpm_file_to_image(mlx_ptr, "textures/player_bg.xpm", &x, &y);
	printf("%d %d", x, y);
	collect = mlx_xpm_file_to_image(mlx_ptr, "textures/collect.xpm", &x, &y);
	floor = mlx_xpm_file_to_image(mlx_ptr, "textures/floor.xpm", &x, &y);
	 for (int i = 0; i < 5 * 64; i++)
	{
	 	for (int j = 0; j < 5 * 64; j++)
			mlx_put_image_to_window(mlx_ptr, win_ptr, collect, (i * 64), (j * 64));

	}
	//mlx_put_image_to_window(mlx_ptr, win_ptr, player, (5 * 64) / 2, (5 * 64) / 2);
	//mlx_put_image_to_window(mlx_ptr, win_ptr, collect, 750 / 2, 500 / 2);
	//mlx_pixel_put(mlx_ptr, win_ptr, (5 * 64) / 2, (5 * 64) / 2, 0xFFFFFF);
	mlx_loop(mlx_ptr);
}