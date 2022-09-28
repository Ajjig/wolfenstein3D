/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_horizontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:15:07 by aboudoun          #+#    #+#             */
/*   Updated: 2022/09/28 16:55:02 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

static void	init_horizontal(t_distance *dist, t_data *data, double angle)
{
	int	px;
	int	py;

	py = data->player->y;
	px = data->player->x;
	if (sin(angle) > 0)
	{
		dist->ry = ((py / BOX_SIZE) * BOX_SIZE) - 0.0001;
		dist->rx = (py - dist->ry) * (1 / tan(angle)) + px;
		dist->y_move = BOX_SIZE * (-1);
		dist->x_move = - (dist->y_move) * (1 / tan(angle));
	}
	else if (sin(angle) < 0)
	{
		dist->ry = ((py / BOX_SIZE) * BOX_SIZE) + BOX_SIZE;
		dist->rx = (py - dist->ry) * (1 / tan(angle)) + px;
		dist->y_move = BOX_SIZE;
		dist->x_move = - (dist->y_move) * (1 / tan(angle));
	}
	else
		dist->dof = data->game->map_height;
}

static void	check_map(t_data *data, t_distance *dist)
{
	int	mx;
	int	my;

	while (dist->dof < data->game->map_height)
	{
		mx = (int)(dist->rx) / BOX_SIZE;
		my = (int)(dist->ry) / BOX_SIZE;
		if (mx >= 0 && mx < data->game->map_width && my < \
data->game->map_height && my >= 0 && data->game->map[my][mx] == '1')
			dist->dof = data->game->map_height;
		else
		{
			dist->rx += dist->x_move;
			dist->ry += dist->y_move;
			dist->dof++;
		}
	}
}

double	get_horizontal(t_data *data, double angle, int count)
{
	t_distance	*dist;
	int			px;
	int			py;

	dist = malloc(sizeof(t_distance));
	ft_bzero(dist, sizeof(t_distance));
	px = data->player->x;
	py = data->player->y;
	dist->dof = 0;
	init_horizontal(dist, data, angle);
	check_map(data, dist);
	if (count == -1)
		return (hypot((dist->rx - px), (dist->ry - py)));
	if (data->rays_dist[count] > hypot((dist->rx - px), (dist->ry - py)) * \
fabs(cos(data->player->angle - angle)))
	{
		data->rays_x[count] = dist->rx;
		data->rays_y[count] = dist->ry;
		data->is_horizontal[count] = true;
		data->rays_dist[count] = hypot((dist->rx - px), (dist->ry - py)) * \
fabs(cos(data->player->angle - angle));
	}
	return (hypot((dist->rx - px), (dist->ry - py)) * \
fabs(cos(data->player->angle - angle)));
}
