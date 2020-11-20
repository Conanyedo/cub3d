/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:55:37 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/20 12:16:21 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fc_render(t_cub3d *cub)
{
	if (cub->img.h < cub->drawstart)
	{
		if (!cub->fc.exist)
		{
			cub->img.img_data[cub->img.h * cub->res.w + cub->ray] =
				create_rgb(&cub->c);
			bmp_filling(cub, &cub->f);
		}
	}
	if (cub->img.h > cub->drawend)
	{
		if (!cub->fc.exist)
		{
			cub->img.img_data[cub->img.h * cub->res.w + cub->ray] =
				create_rgb(&cub->f);
			bmp_filling(cub, &cub->c);
		}
	}
}

void	bmp_fc(t_cub3d *cub, int y, int x)
{
	cub->abrv = x + (cub->res.h - y) * cub->res.w;
	if (cub->save == 1)
	{
		cub->image[(cub->abrv) * 3 + 2] = cub->fc.color >> 16;
		cub->image[(cub->abrv) * 3 + 1] = cub->fc.color >> 8;
		cub->image[(cub->abrv) * 3 + 0] = cub->fc.color;
	}
}

void	fc_calc(t_cub3d *cub, int y)
{
	cub->fc.raydirx0 = cub->dirx - cub->planex;
	cub->fc.raydiry0 = cub->diry - cub->planey;
	cub->fc.raydirx1 = cub->dirx + cub->planex;
	cub->fc.raydiry1 = cub->diry + cub->planey;
	cub->fc.p = y - cub->res.h / 2;
	cub->fc.posz = 0.5 * cub->res.h;
	cub->fc.rowdistance = cub->fc.posz / cub->fc.p;
	cub->fc.floorStepx = cub->fc.rowdistance *
		(cub->fc.raydirx1 - cub->fc.raydirx0) / cub->res.h;
	cub->fc.floorStepy = cub->fc.rowdistance *
		(cub->fc.raydiry1 - cub->fc.raydiry0) / cub->res.h;
	cub->fc.floorx = cub->posx + cub->fc.rowdistance *
		cub->fc.raydirx0;
	cub->fc.floory = cub->posy + cub->fc.rowdistance *
		cub->fc.raydiry0;
}

void	fc_txt(t_cub3d *cub, int y)
{
	if (y < cub->res.h / 2)
		cub->fc.color = cub->txt[5].img_data[cub->texwidth *
			cub->fc.ty + cub->fc.tx];
	else
		cub->fc.color = cub->txt[6].img_data[cub->texwidth *
			cub->fc.ty + cub->fc.tx];
	cub->fc.color = (cub->fc.color >> 1) & 8355711;
}

void	floor_ceiling(t_cub3d *cub)
{
	int		y;
	int		x;

	y = -1;
	while (++y < cub->res.h)
	{
		fc_calc(cub, y);
		x = -1;
		while (++x < cub->res.w)
		{
			cub->fc.cellx = (int)(cub->fc.floorx);
			cub->fc.celly = (int)(cub->fc.floory);
			cub->fc.tx = (int)(cub->texwidth * (cub->fc.floorx - cub->fc.cellx)) & (cub->texwidth - 1);
			cub->fc.ty = (int)(cub->texheight * (cub->fc.floory - cub->fc.celly)) & (cub->texheight - 1);
			cub->fc.floorx += cub->fc.floorStepx;
			cub->fc.floory += cub->fc.floorStepy;
			fc_txt(cub, y);
			cub->img.img_data[y * cub->res.w + x] = cub->fc.color;
			bmp_fc(cub, y, x);
		}
	}
}
