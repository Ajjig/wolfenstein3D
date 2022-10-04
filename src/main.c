/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:45:00 by aboudoun          #+#    #+#             */
/*   Updated: 2022/10/04 19:05:26 by majjig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_clear(t_game *game)
{
	int	i;

	i = 0;
	free(game -> west);
	free(game -> north);
	free(game -> south);
	free(game -> east);
	while (game -> map[i])
		free(game -> map[i++]);
	free(game -> map);
	free(game -> sprite);
}

int	open_map(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		error_handler("argument error");
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || !ft_strcmp(".cub", &av[1][ft_strlen(av[1]) - 4]))
		error_handler("invalid file");
	return (fd);
}

unsigned int	*map_img_fix(t_data*data, t_img *img)
{
	int ix;
	int iy = data->player->y / BOX_SIZE * data->minimap->box - 40;
	static t_img	*new = NULL;
	int x;
	int y = 0;

	if (!new)
	{
		new = malloc(sizeof(t_img));
		new->img = mlx_new_image(data->mlx, 80, 80);
		new->addr = (int *) mlx_get_data_addr(new->img, &new->bits_per_pixel, &new->line_length, &new->endian);
	}
	while (y < 80 * (new->line_length / 4))
	{
		x = 0;
		ix = data->player->x / BOX_SIZE * data->minimap->box - 40;
		while (x < 80)
		{
			new->addr[y + x] = img->addr[iy + ix];
			x++;
			ix++;
		}
		y += new->line_length / 4;
		iy += img->line_length / 4;
	}
	return (new->img);
}

int	next_frame(t_data *data)
{
	static double	mini_p_x;
	static double	mini_p_y;

	mini_p_x = data->player->x / BOX_SIZE * data->minimap->box;
	mini_p_y = data->player->y / BOX_SIZE * data->minimap->box;
	change_position(data);
	draw_map(data, mini_p_x, mini_p_y);
	draw_game(data);
	mlx_put_image_to_window(data->mlx, data->win, map_img_fix(data, data->img), 10, 10);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == W || key == S)
		data->player->walk_direction = 0;
	if (key == A || key == D)
		data->player->turn_direction = 0;
	if (key == LEFT || key == RIGHT)
		data->player->rotation_direction = 0;
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	t_data	data;

	fd = open_map(ac, av);
	init_data(&data);
	get_map(fd, data.game, NULL);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	check_elements_path(&data);
	get_player_pos(&data);
	init_images(&data);
	mlx_loop_hook(data.mlx, next_frame, &data);
	mlx_hook(data.win, 2, 0, &key_handler, &data);
	mlx_hook(data.win, 3, 0, &key_release, &data);
	mlx_loop(data.mlx);
	ft_clear(data.game);
	return (0);
}
