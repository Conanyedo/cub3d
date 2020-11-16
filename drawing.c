/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:16:51 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/16 12:57:53 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc(t_cub3d *cub)
{
	cub->hit = 0;
	cub->img.h = 0;
	cub->bmp_pos = 0;
	cub->cameraX = 2 * cub->ray / (double)cub->res.w - 1;
	cub->rayDirX = cub->dirX + cub->planeX * cub->cameraX;
	cub->rayDirY = cub->dirY + cub->planeY * cub->cameraX;
	cub->mapX = (int)cub->posX;
	cub->mapY = (int)cub->posY;
	cub->deltaDistX = sqrt(1 + pow(cub->rayDirY, 2) / pow(cub->rayDirX, 2));
	cub->deltaDistY = sqrt(1 + pow(cub->rayDirX, 2) / pow(cub->rayDirY, 2));
	if (cub->rayDirY == 0)
		cub->deltaDistX = 0;
	else
		cub->deltaDistX = (cub->rayDirX == 0) ? 1 : cub->deltaDistX;
	if (cub->rayDirX == 0)
		cub->deltaDistY = 0;
	else
		cub->deltaDistY = (cub->rayDirY == 0) ? 1 : cub->deltaDistY;
}

void	sidedist(t_cub3d *cub)
{
	if (cub->rayDirX < 0)
	{
		cub->stepX = -1;
		cub->sidedistX = (cub->posX - cub->mapX) * cub->deltaDistX;
	}
	else
	{
		cub->stepX = 1;
		cub->sidedistX = (cub->mapX + 1.0 - cub->posX) * cub->deltaDistX;
	}
	if (cub->rayDirY < 0)
	{
		cub->stepY = -1;
		cub->sidedistY = (cub->posY - cub->mapY) * cub->deltaDistY;
	}
	else
	{
		cub->stepY = 1;
		cub->sidedistY = (cub->mapY + 1.0 - cub->posY) * cub->deltaDistY;
	}
}

void	hit(t_cub3d *cub)
{
	while (cub->hit == 0)
	{
		if (cub->sidedistX < cub->sidedistY)
		{
			cub->sidedistX += cub->deltaDistX;
			cub->mapX += cub->stepX;
			cub->side = 0;
		}
		else
		{
			cub->sidedistY += cub->deltaDistY;
			cub->mapY += cub->stepY;
			cub->side = 1;
		}
		if (cub->side == 0 && cub->rayDirX > 0)
			cub->side = 2;
		else if (cub->side == 1 && cub->rayDirY < 0)
			cub->side = 3;
		if (cub->map[cub->mapX][cub->mapY] == '1')
			cub->hit = 1;
	}
}

void	wall(t_cub3d *cub)
{
	if (cub->side == 0 || cub->side == 2)
		cub->perpWallDist = (cub->mapX - cub->posX + (1 - cub->stepX) / 2) /
			cub->rayDirX;
	else
		cub->perpWallDist = (cub->mapY - cub->posY + (1 - cub->stepY) / 2) /
			cub->rayDirY;
	cub->lineHeight = (int)(cub->res.h / cub->perpWallDist);
	cub->drawStart = (-cub->lineHeight / 2) + (cub->res.h / 2);
	if (cub->drawStart < 0)
		cub->drawStart = 0;
	cub->drawEnd = cub->lineHeight / 2 + cub->res.h / 2;
	if (cub->drawEnd >= cub->res.h)
		cub->drawEnd = cub->res.h - 1;
	if (cub->side == 0 || cub->side == 2)
		cub->wallX = cub->posY + cub->perpWallDist * cub->rayDirY;
	else
		cub->wallX = cub->posX + cub->perpWallDist * cub->rayDirX;
	cub->wallX -= floor((cub->wallX));
	cub->texX = (int)(cub->wallX * (double)(cub->texWidth));
	if (cub->side == 0 && cub->rayDirX > 0)
		cub->texX = cub->texWidth - cub->texX - 1;
	if (cub->side == 1 && cub->rayDirY < 0)
		cub->texX = cub->texWidth - cub->texX - 1;
	cub->step = 1.0 * cub->texHeight / cub->lineHeight;
}

void	rendering(t_cub3d *cub)
{
	cub->texPos = (cub->drawStart - cub->res.h / 2 + cub->lineHeight / 2) *
		cub->step;
	while (cub->img.h < cub->res.h)
	{
		if (cub->img.h < cub->drawStart)
		{
			cub->img.img_data[cub->img.h * cub->res.w + cub->ray] =
				create_rgb(&cub->C);
			bmp_filling(cub, &cub->F);
		}
		if (cub->img.h >= cub->drawStart && cub->img.h <= cub->drawEnd)
			wallrendering(cub);
		if (cub->img.h > cub->drawEnd)
		{
			cub->img.img_data[cub->img.h * cub->res.w + cub->ray] =
				create_rgb(&cub->F);
			bmp_filling(cub, &cub->C);
		}
		cub->img.h++;
	}
	if (cub->spriteNum)
		cub->sprite_buf[cub->ray] = cub->perpWallDist;
	cub->ray++;
}
