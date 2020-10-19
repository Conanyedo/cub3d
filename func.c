/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 01:49:26 by ybouddou          #+#    #+#             */
/*   Updated: 2020/10/19 20:17:56 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_cub3d *cub)//////////over 25////////////
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
	cub->parse.nline = 0;
	cub->parse.line = NULL;
	cub->parse.colors = NULL;
	cub->parse.splitted = NULL;
	cub->img.w = -1;
	cub->img.h = -1;
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
}

void	checker(char **s)
{
	int i;
	int	j;

	i = 0;	
	while (s[i])
	{
		j = 0;
        if (s[i][0] == '-')
			error_msg_free("Error\nNegative number\n", s);
		while (s[i][j])
		{
			if (s[i][j] < 48 || s[i][j] > 57)
				error_msg_free("Error\nAnother char found\n", s);
			j++;
		}
		i++;
	}
}

void	range(t_rgb *rgb)
{
	if (rgb->r > 255 || rgb->r < 0 || rgb->g > 255 || rgb->g < 0 || rgb->b > 255 || rgb->b < 0)
	{
		ft_putstr_fd("Error\nRange is false\n", 2);
		exit (1);
	}
}

unsigned long createRGB(t_rgb *rgb)
{
	return ((rgb->r & 0xff) << 16) + ((rgb->g & 0xff) << 8) + (rgb->b & 0xff);
}