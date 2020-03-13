/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:49:26 by ybouddou          #+#    #+#             */
/*   Updated: 2020/03/13 13:45:59 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <math.h>
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "cub3d.h"

void	init(t_cub3d *cub)
{
	cub->posX = 22;
	cub->posY = 12;
	cub->dirX = -1;
	cub->dirY = 0;
	cub->planeX = 0;
	cub->planeY = 0.66;
	cub->rotateSpeed = 0.03;
	cub->moveSpeed = 0.3;
	cub->path.NO = NULL;
	cub->path.SO = NULL;
	cub->path.WE = NULL;
	cub->path.EA = NULL;
	cub->path.S = NULL;
	cub->parse.r = 1;
	cub->parse.line = NULL;
	cub->parse.colors = NULL;
	cub->parse.splitted = NULL;
	cub->img.w = -1;
	cub->img.h = -1;
	cub->change = 0;
	cub->look = 0;

}

void ft_free(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
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
                j++;
		while (s[i][j])
		{
			if (s[i][j] < 48 || s[i][j] > 57)
				printf("error character found\n");
			j++;
		}
		i++;
	}
}

void	range(t_rgb *rgb)
{
	if (rgb->r > 255 || rgb->r < 0 || rgb->g > 255 || rgb->g < 0 || rgb->b > 255 || rgb->b < 0)
		printf("error range\n");
}

int		key_pressed(int key, t_cub3d *cub)
{
	cub->keyboard[key] = 1;
	return (0);
}

int		key_released(int key, t_cub3d *cub)
{
	cub->keyboard[key] = 0;
	return (0);
}

unsigned long createRGB(t_rgb *rgb)
{
	return ((rgb->r & 0xff) << 16) + ((rgb->g & 0xff) << 8) + (rgb->b & 0xff);
}