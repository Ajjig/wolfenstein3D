#include "cub.h"

void	move_up(t_data *data)
{
	if (data->game->map[(int)(data->player->y - data->player->dy * PLAYER_SPEED)][(int)(data->player->x + data->player->dx * PLAYER_SPEED)] != WALL)
	{
		data->player->y -= data->player->dy * PLAYER_SPEED;
		data->player->x += data->player->dx * PLAYER_SPEED;
	}
}

void	move_down(t_data *data)
{
	if (data->game->map[(int)(data->player->y + data->player->dy * PLAYER_SPEED)][(int)(data->player->x - data->player->dx * PLAYER_SPEED)] != WALL)
	{
		data->player->y += data->player->dy * PLAYER_SPEED;
		data->player->x -= data->player->dx * PLAYER_SPEED;
	}
}

void	move_left(t_data *data)
{
	if (data->game->map[(int)(data->player->y - data->player->dy * PLAYER_SPEED)][(int)(data->player->x - data->player->dx * PLAYER_SPEED)] != WALL)
	{
		data->player->y -= data->player->dx * PLAYER_SPEED;
		data->player->x -= data->player->dy * PLAYER_SPEED;
	}
}

void	move_right(t_data *data)
{
	if (data->game->map[(int)(data->player->y + data->player->dy * PLAYER_SPEED)][(int)(data->player->x + data->player->dx * PLAYER_SPEED)] != WALL)
	{
		data->player->x += data->player->dy * PLAYER_SPEED;
		data->player->y += data->player->dx * PLAYER_SPEED;
	}

}

void	rotate_left(t_data *data)
{
	data->player->angle += ROTATE_SPEED;
	if (data->player->angle < 0)
		data->player->angle = 2 * PI + data->player->angle;
	data->player->dx = cos(data->player->angle);
	data->player->dy = sin(data->player->angle);
	printf("angle:%f\n", data->player->angle);
	printf("angle degre:%f\n", data->player->angle * 180 / PI);
}

void	rotate_right(t_data *data)
{
	data->player->angle -= ROTATE_SPEED;
	if (data->player->angle > 2 * PI)
		data->player->angle -= 2 * PI;
	data->player->dx = cos(data->player->angle);
	data->player->dy = sin(data->player->angle);
	printf("angle:%f\n", data->player->angle);
	printf("angle degre:%f\n", data->player->angle * 180 / PI);
}

void	key_handler(int key, t_data *data)
{
	printf("player_b x:%f\n", data->player->x);
	printf("player_b y:%f\n", data->player->y);
	if (key == W)
		move_up(data);
	else if (key == S)
		move_down(data);
	else if (key == A)
		move_left(data);
	else if (key == D)
		move_right(data);
	else if (key == RIGHT)
		rotate_right(data);
	else if (key == LEFT)
		rotate_left(data);
	printf("player x:%f\n", data->player->x);
	printf("player y:%f\n", data->player->y);
}
