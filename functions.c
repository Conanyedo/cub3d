/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:52:06 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/16 12:58:23 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_close(t_cub3d *cub)
{
	mlx_clear_window(cub->mlx.p, cub->mlx.w);
	system("rm -rf a.out >/dev/null 2>&1");
	exit(0);
	return (0);
}

void	if_sprite(t_cub3d *cub)
{
	if (cub->spriteNum)
	{
		cub->sprite_buf = (double *)malloc((cub->res.w + 1) * sizeof(double));
		cub->sprite = malloc((cub->spriteNum + 1) * sizeof(t_sprite));
	}
}

void	free_path(t_cub3d *cub)
{
	free(cub->path.NO);
	free(cub->path.SO);
	free(cub->path.EA);
	free(cub->path.WE);
	free(cub->path.S);
}

void	wallrendering(t_cub3d *cub)
{
	cub->texY = (int)cub->texPos;
	cub->texPos += cub->step;
	if (cub->side == 0)
		cub->color = cub->txt[2].img_data[cub->texX + cub->texY
			* cub->txt[2].w];
	else if (cub->side == 1)
		cub->color = cub->txt[3].img_data[cub->texX + cub->texY *
			cub->txt[3].w];
	else if (cub->side == 2)
		cub->color = cub->txt[0].img_data[cub->texX + cub->texY *
			cub->txt[0].w];
	else if (cub->side == 3)
		cub->color = cub->txt[1].img_data[cub->texX + cub->texY *
			cub->txt[1].w];
	cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->color;
	if (cub->save == 1)
	{
		cub->image[(cub->ray + (cub->drawEnd - cub->bmp_pos) * cub->res.w)
			* 3 + 2] = cub->color >> 16;
		cub->image[(cub->ray + (cub->drawEnd - cub->bmp_pos) * cub->res.w)
			* 3 + 1] = cub->color >> 8;
		cub->image[(cub->ray + (cub->drawEnd - cub->bmp_pos) * cub->res.w)
			* 3 + 0] = cub->color;
		cub->bmp_pos++;
	}
}

void	sprite_image(t_cub3d *cub)
{
	cub->d = (cub->spriteLine) * 256 - cub->res.h * 128 +
		cub->spriteHeight * 128;
	cub->texY = ((cub->d * cub->texHeight) / cub->spriteHeight) / 256;
	if (cub->txt[4].img_data[cub->texX + cub->texY * cub->txt[4].w])
	{
		cub->img.img_data[cub->spriteLine * cub->res.w + cub->drawStartX] =
			cub->txt[4].img_data[cub->texX + cub->texY * cub->txt[4].w];
		if (cub->save == 1)
		{
			cub->abrv = ((cub->drawEndY - cub->bmp_pos) * cub->res.w +
				cub->drawStartX);
			cub->image[cub->abrv * 3 + 2] = cub->txt[4].img_data[cub->texX +
				cub->texY * cub->txt[4].w] >> 16;
			cub->image[cub->abrv * 3 + 1] = cub->txt[4].img_data[cub->texX +
				cub->texY * cub->txt[4].w] >> 8;
			cub->image[cub->abrv * 3 + 0] = cub->txt[4].img_data[cub->texX +
				cub->texY * cub->txt[4].w];
		}
	}
	cub->bmp_pos++;
}
