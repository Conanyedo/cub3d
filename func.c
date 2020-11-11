/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 01:49:26 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/11 10:18:49 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			init(t_cub3d *cub)
{
	cub->rotateSpeed = 0.03;
	cub->moveSpeed = 0.15;
	cub->path.NO = NULL;
	cub->path.SO = NULL;
	cub->path.WE = NULL;
	cub->path.EA = NULL;
	cub->path.S = NULL;
	cub->map = NULL;
	cub->parse.mapline = 0;
	cub->parse.X = 0;
	cub->parse.spawn = 0;
	cub->parse.r = 1;
	cub->parse.line = NULL;
	cub->parse.colors = NULL;
	cub->parse.splitted = NULL;
	cub->rep.res = 0;
	cub->rep.NO = 0;
	cub->rep.SO = 0;
	cub->rep.WE = 0;
	cub->rep.EA = 0;
	cub->rep.S = 0;
	cub->rep.F = 0;
	cub->rep.C = 0;
	cub->texHeight = 64;
	cub->texWidth = 64;
	cub->spriteNum = 0;
	cub->spriteN = 0;
}

void			checker(char **s, t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
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

void			range(t_rgb *rgb, t_cub3d *cub)
{
	if (rgb->r > 255 || rgb->r < 0 || rgb->g > 255 || rgb->g < 0 ||
		rgb->b > 255 || rgb->b < 0)
		error_msg_free("Error\nRange is false\n", cub);
}

void			fc_checker(t_parse *parse, t_cub3d *cub)
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

unsigned long	create_rgb(t_rgb *rgb)
{
	return ((rgb->r & 0xff) << 16) + ((rgb->g & 0xff) << 8) + (rgb->b & 0xff);
}
