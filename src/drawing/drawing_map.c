/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:49:44 by aboudoun          #+#    #+#             */
/*   Updated: 2022/09/30 15:39:59 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   void draw_line(t_data *data, int count)
   {
   (void)count;
   double	beginX = data->player->x / BOX_SIZE * 6;
   double	beginY = data->player->y / BOX_SIZE * 6;
   double endX = data->player->x / BOX_SIZE * 6 + cos(data->player->angle) * 6;
   double endY = data->player->y / BOX_SIZE * 6 - sin(data->player->angle) * 6;
   double deltaX = endX - beginX; // 10
   double deltaY = endY - beginY; // 0
   int pixels = data->rays_dist[count];
   deltaX /= pixels; // 1
   deltaY /= pixels; // 0
   while (pixels)
   {
   my_mlx_pixel_put(data->img, beginX, beginY, 0xFF1818);
   beginX += deltaX;
   beginY += deltaY;
   --pixels;
   }
   }*/
#include"cub.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = (char *)data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	drw_box(t_data *data, int x_b, int y_b, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->minimap->box)
	{
		x = 0;
		while (x < data->minimap->box)
		{
			my_mlx_pixel_put(data->img, x + x_b, y + y_b, color);
			x++;
		}
		y++;
	}
}

void	drw_player(t_data *data, double x_b, double y_b, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->minimap->p_box)
	{
		x = 0;
		while (x < data->minimap->p_box)
		{
			my_mlx_pixel_put(data->img, x + x_b, y + y_b, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_data *data, double mini_p_x, double mini_p_y)
{
	int		x;
	int		y;

	y = 0;
	while (data->game->map[y])
	{
		x = 0;
		while (data->game->map[y][x])
		{
			if (data->game->map[y][x] == WALL)
				drw_box(data, x * data->minimap->box,
					y * data->minimap->box, 0x8758FF);
			else if (data->game->map[y][x] == EMPTY || \
					ft_strchr("NSWE", data->game->map[y][x]))
				drw_box(data, x * data->minimap->box,
					y * data->minimap->box, 0xD2DAFF);
			else
				drw_box(data, x * data->minimap->box,
					y * data->minimap->box, 0xFF000000);
			x++;
		}
		y++;
	}
	drw_player(data, mini_p_x, mini_p_y, 0x000ED5);
	get_distance(data);
}
