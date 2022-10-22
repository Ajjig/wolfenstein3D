/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:35:09 by aboudoun          #+#    #+#             */
/*   Updated: 2022/10/22 04:47:15 by majjig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_data(t_data *data)
{
	data->game = calloc(1, sizeof(t_game));
	data->player = calloc(1, sizeof(t_player));
	data->rays_dist = calloc(1, sizeof(double) * WIN_WIDTH);
	data->img = calloc(1, sizeof(t_img));
	data->img_game = calloc(1, sizeof(t_img));
	data->rays_x = calloc(1, sizeof(double) * WIN_WIDTH);
	data->rays_y = calloc(1, sizeof(double) * WIN_WIDTH);
	data->ray_angle = calloc(1, sizeof(double) * WIN_WIDTH);
	data->is_horizontal = calloc(1, sizeof(int) * WIN_WIDTH);
}

void	init_images(t_data *data)
{
	data->img_game->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img_game->addr = (int *)mlx_get_data_addr(data->img_game->\
img, &data->img_game->bits_per_pixel, &data->img_game->\
line_length, &data->img_game->endian);
	data->img->img = mlx_new_image(data->mlx, 6 * MINI, MINI * 6);
	data->img->addr = (int *)mlx_get_data_addr(data->img->img, &data->img->\
bits_per_pixel, &data->img->line_length, &data->img->endian);
}
