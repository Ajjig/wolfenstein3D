/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:21:02 by aboudoun          #+#    #+#             */
/*   Updated: 2022/09/09 17:10:06 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static int	is_valid(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0 || !ft_strcmp(".xpm", &path[ft_strlen(path) - 4]))
		error_handler("Invalid texture");
	return (fd);
}

t_texture	*check_elements_path(t_data *data)
{
	int img_width = 40;
	int img_height = 40;
	t_texture	*texture;

	texture = (t_texture *) malloc(sizeof(t_texture));
	ft_bzero(texture, sizeof(t_texture));
	if (is_valid(data->game->north))
		texture->north_tex = mlx_xpm_file_to_image(data->mlx, data->game->north, &img_width, &img_height);
	if (is_valid(data->game->south))
		texture->south_tex = mlx_xpm_file_to_image(data->mlx, data->game->south, &img_width, &img_height);
	if (is_valid(data->game->west))
		texture->west_tex = mlx_xpm_file_to_image(data->mlx, data->game->west, &img_width, &img_height);
	if (is_valid(data->game->east))
		texture->east_tex = mlx_xpm_file_to_image(data->mlx, data->game->east, &img_width, &img_height);
	return (texture);
}

// static char	**split_one(char *to_split, char sp)
// {
// 	char	**splited;
// 	int		count;
// 	int		i;

// 	i = 0;
// 	count = 0;
// 	splited = NULL;
// 	while (to_split[i])
// 	{
// 		if (to_split[i] == sp)
// 		{
// 			count++;
// 			while (to_split[i] == sp)
// 				i++;
// 		}
// 		if (to_split[i] != sp)
// 			count++;
// 		while (to_split[i] != sp)
// 			i++;

// 	}
// 	splited = malloc(sizeof(char) * count);
// 	if (!to_split[i])
// 	{
// 		splited[0] = to_split;
// 		splited[1] = ft_strdup("");
// 	}
// 	else
// 	{
// 		splited[0] = ft_strndup(to_split, i + 1);
// 		splited[1] = ft_strdup(&to_split[i + 1]);
// 	}
// 	return (splited);
// }
