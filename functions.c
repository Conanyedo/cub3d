/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:52:06 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/26 10:00:29 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_close(t_cub3d *cub)
{
	mlx_clear_window(cub->mlx.p, cub->mlx.w);
	error_msg("END OF GAME!\n");
	return (0);
}

void	if_sprite(t_cub3d *cub)
{
	if (cub->sprite_num)
	{
		cub->sprite_buf = (double *)malloc((cub->res.w + 1) * sizeof(double));
		cub->sprite = malloc((cub->sprite_num + 1) * sizeof(t_sprite));
	}
}

void	free_path(t_cub3d *cub)
{
	free(cub->path.no);
	free(cub->path.so);
	free(cub->path.ea);
	free(cub->path.we);
	free(cub->path.s);
}

void	wallrendering(t_cub3d *cub)
{
	cub->tex_y = (int)cub->texpos;
	cub->texpos += cub->step;
	if (cub->side == 0)
		cub->color = cub->txt[2].img_data[cub->tex_x + cub->tex_y *
			cub->txt[2].w];
	else if (cub->side == 1)
		cub->color = cub->txt[3].img_data[cub->tex_x + cub->tex_y *
			cub->txt[3].w];
	else if (cub->side == 2)
		cub->color = cub->txt[0].img_data[cub->tex_x + cub->tex_y *
			cub->txt[0].w];
	else if (cub->side == 3)
		cub->color = cub->txt[1].img_data[cub->tex_x + cub->tex_y *
			cub->txt[1].w];
	cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->color;
	if (cub->ac == 3)
	{
		cub->image[(cub->ray + (cub->drawend - cub->bmp_pos) * cub->res.w)
			* 3 + 2] = cub->color >> 16;
		cub->image[(cub->ray + (cub->drawend - cub->bmp_pos) * cub->res.w)
			* 3 + 1] = cub->color >> 8;
		cub->image[(cub->ray + (cub->drawend - cub->bmp_pos) * cub->res.w)
			* 3 + 0] = cub->color;
		cub->bmp_pos++;
	}
}

void	spritesort(t_cub3d *cub)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < cub->sprite_num - 1)
	{
		j = 0;
		while (j < cub->sprite_num - i - 1)
		{
			if (cub->sprite[j].dist < cub->sprite[j + 1].dist)
			{
				tmp = cub->sprite[j];
				cub->sprite[j] = cub->sprite[j + 1];
				cub->sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
