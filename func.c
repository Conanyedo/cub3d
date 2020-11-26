/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:26:43 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/26 08:47:51 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_cub3d *cub)
{
	cub->path.no = NULL;
	cub->path.so = NULL;
	cub->path.we = NULL;
	cub->path.ea = NULL;
	cub->path.s = NULL;
	cub->map = NULL;
	cub->parse.x = 0;
	cub->parse.spawn = 0;
	cub->parse.line = NULL;
	cub->parse.colors = NULL;
	cub->parse.splitted = NULL;
	cub->image = NULL;
	cub->rep.res = 0;
	cub->rep.no = 0;
	cub->rep.so = 0;
	cub->rep.we = 0;
	cub->rep.ea = 0;
	cub->rep.s = 0;
	cub->rep.f = 0;
	cub->rep.c = 0;
	cub->sprite_num = 0;
	cub->sprite_n = 0;
}

void	checker(char **s, t_cub3d *cub, int i)
{
	int	j;

	while (s[i])
	{
		j = 0;
		if (s[i][0] == '-')
			error_free("Error\nNegative number\n", cub, s);
		while (s[i][j])
		{
			if (s[i][j] < 48 || s[i][j] > 57)
				error_free("Error\nAnother char found\n", cub, s);
			j++;
		}
		i++;
	}
}

void	range(t_rgb *rgb, t_cub3d *cub)
{
	if (rgb->r > 255 || rgb->r < 0 || rgb->g > 255 || rgb->g < 0 ||
		rgb->b > 255 || rgb->b < 0)
		error_msg_free("Error\nRange is false\n", cub);
}

void	fc_checker(t_parse *parse, t_cub3d *cub)
{
	int	comma;
	int	i;

	i = 0;
	comma = 0;
	if (parse->splitted[2])
		error_free("Error\nAnother char found after F\n", cub, parse->splitted);
	while (parse->splitted[1][i])
	{
		if (parse->splitted[1][i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		error_free("Error\nWrong format of rgb\n", cub, parse->splitted);
}

int		create_rgb(t_rgb *rgb)
{
	int		color;

	color = (rgb->r << 16) | (rgb->g << 8) | rgb->b;
	return (color);
}
