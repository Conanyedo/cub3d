/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:16:51 by ybouddou          #+#    #+#             */
/*   Updated: 2020/10/19 20:17:08 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc(t_cub3d *cub)
{
	cub->hit = 0;
	cub->img.h = 0;
	cub->cameraX = 2 * cub->ray / (double)cub->res.w - 1;
	cub->rayDirX = cub->dirX + cub->planeX * cub->cameraX;
	cub->rayDirY = cub->dirY + cub->planeY * cub->cameraX;
	cub->mapX = (int)cub->posX;
	cub->mapY = (int)cub->posY;
	cub->deltaDistX = sqrt(1 + (cub->rayDirY * cub->rayDirY) / (cub->rayDirX * cub->rayDirX));
	cub->deltaDistY = sqrt(1 + (cub->rayDirX * cub->rayDirX) / (cub->rayDirY * cub->rayDirY));
	cub->deltaDistX = (cub->rayDirY == 0) ? 0 : ((cub->rayDirX == 0) ? 1 : cub->deltaDistX);
	cub->deltaDistY = (cub->rayDirX == 0) ? 0 : ((cub->rayDirY == 0) ? 1 : cub->deltaDistY);
}

void	sideDist(t_cub3d *cub)
{
	if (cub->rayDirX < 0)
	{
		cub->stepX = -1;
		cub->sideDistX = (cub->posX - cub->mapX) * cub->deltaDistX;
	}
	else
	{
		cub->stepX = 1;
		cub->sideDistX = (cub->mapX + 1.0 - cub->posX) * cub->deltaDistX;
	}
	if (cub->rayDirY < 0)
	{
		cub->stepY = -1;
		cub->sideDistY = (cub->posY - cub->mapY) * cub->deltaDistY;
	}
	else
	{
		cub->stepY = 1;
		cub->sideDistY = (cub->mapY + 1.0 - cub->posY) * cub->deltaDistY;
	}
}

void	hit(t_cub3d *cub)
{
	while (cub->hit == 0)
	{
		if (cub->sideDistX < cub->sideDistY)
		{
			cub->sideDistX += cub->deltaDistX;
			cub->mapX += cub->stepX;
			cub->side= 0;//NO
		}
		else
		{
			cub->sideDistY += cub->deltaDistY;
			cub->mapY += cub->stepY;
			cub->side = 1;//WE
		}
		if(cub->side == 0 && cub->rayDirX > 0)
			cub->side = 2;//SO
		else if(cub->side == 1 && cub->rayDirY < 0)
			cub->side = 3;//EA
		if (cub->map[cub->mapX][cub->mapY] > '0')
			cub->hit = 1;
	}
}

void	wall(t_cub3d *cub)
{
	if (cub->side == 0 || cub->side == 2)
		cub->perpWallDist = (cub->mapX - cub->posX + (1 - cub->stepX) / 2) / cub->rayDirX;//2.5
	else
		cub->perpWallDist = (cub->mapY - cub->posY + (1 - cub->stepY) / 2) / cub->rayDirY;
	cub->lineHeight = (int)(cub->res.h / cub->perpWallDist);//144
	cub->drawStart = (-cub->lineHeight / 2) + (cub->res.h / 2);//108
	if(cub->drawStart < 0)
		cub->drawStart = 0;
	cub->drawEnd = cub->lineHeight / 2 + cub->res.h / 2;//252
	if(cub->drawEnd >= cub->res.h)
		cub->drawEnd = cub->res.h - 1;
	if (cub->side == 0 || cub->side == 2)
		cub->wallX = cub->posY + cub->perpWallDist * cub->rayDirY;//3.5
	else
		cub->wallX = cub->posX + cub->perpWallDist * cub->rayDirX;
	cub->wallX -= floor((cub->wallX));//0.5
	cub->texX = (int)(cub->wallX * (double)(cub->texWidth));//32
	if(cub->side == 0 && cub->rayDirX > 0)
		cub->texX = cub->texWidth - cub->texX - 1;
	if(cub->side == 1 && cub->rayDirY < 0)
		cub->texX = cub->texWidth - cub->texX - 1;
	// How much to increase the texture coordinate per screen pixel
	cub->step = 1.0 * cub->texHeight / cub->lineHeight;//0.444
	// Starting texture coordinate
	cub->texPos = (cub->drawStart - cub->res.h / 2 + cub->lineHeight / 2) * cub->step;//~32
}

void	render(t_cub3d *cub)
{
	while (cub->img.h < cub->res.h)
	{
		if (cub->img.h < cub->drawStart)
			cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = createRGB(&cub->C);
		if (cub->img.h >= cub->drawStart && cub->img.h <= cub->drawEnd)
		{
			cub->texY = (int)cub->texPos & (cub->texHeight - 1);	
			cub->texPos += cub->step;
			if (cub->side == 0)//NO
			{
				//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = color;
				cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[0].img_data[cub->texX + cub->texY * cub->txt[0].w];
			}
			else if (cub->side == 1)//WE
			{
				//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = color;
				cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[1].img_data[cub->texX + cub->texY * cub->txt[1].w];
			}
			else if (cub->side == 2)//SO
			{
				//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = color;
				cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[2].img_data[cub->texX + cub->texY * cub->txt[2].w];
			}
			else if (cub->side == 3)//EA
			{
				//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = color;
				cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[3].img_data[cub->texX + cub->texY * cub->txt[3].w];
			}
		}
		if (cub->img.h > cub->drawEnd)
			cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = createRGB(&cub->F);
		cub->img.h++;
	}
	cub->ray++;
}