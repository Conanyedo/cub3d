/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:11:23 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/16 12:57:34 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	moves_up_down(t_cub3d *cub)
{
	if (cub->keyboard[13])
	{
		if (cub->map[(int)(cub->posX + cub->dirX * cub->moveSpeed)]
			[(int)(cub->posY)] == '0')
			cub->posX += cub->dirX * cub->moveSpeed;
		if (cub->map[(int)(cub->posX)][(int)(cub->posY + cub->dirY *
			cub->moveSpeed)] == '0')
			cub->posY += cub->dirY * cub->moveSpeed;
	}
	if (cub->keyboard[1])
	{
		if (cub->map[(int)(cub->posX - cub->dirX * cub->moveSpeed)]
			[(int)(cub->posY)] == '0')
			cub->posX -= cub->dirX * cub->moveSpeed;
		if (cub->map[(int)(cub->posX)][(int)(cub->posY - cub->dirY *
			cub->moveSpeed)] == '0')
			cub->posY -= cub->dirY * cub->moveSpeed;
	}
}

void	movesides(t_cub3d *cub)
{
	if (cub->keyboard[0])
	{
		if (cub->map[(int)(cub->posX - cub->planeX * cub->moveSpeed)]
			[(int)(cub->posY)] == '0')
			cub->posX -= cub->planeX * cub->moveSpeed;
		if (cub->map[(int)(cub->posX)][(int)(cub->posY - cub->planeY *
			cub->moveSpeed)] == '0')
			cub->posY -= cub->planeY * cub->moveSpeed;
	}
	if (cub->keyboard[2])
	{
		if (cub->map[(int)(cub->posX + cub->planeX * cub->moveSpeed)]
			[(int)(cub->posY)] == '0')
			cub->posX += cub->planeX * cub->moveSpeed;
		if (cub->map[(int)(cub->posX)][(int)(cub->posY + cub->planeY *
			cub->moveSpeed)] == '0')
			cub->posY += cub->planeY * cub->moveSpeed;
	}
}

void	look(t_cub3d *cub)
{
	cub->oldDirX = cub->dirX;
	if (cub->keyboard[123])
	{
		cub->dirX = cub->dirX * cos(cub->rotateSpeed) - cub->dirY *
			sin(cub->rotateSpeed);
		cub->dirY = cub->oldDirX * sin(cub->rotateSpeed) + cub->dirY *
			cos(cub->rotateSpeed);
		cub->oldPlaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(cub->rotateSpeed) - cub->planeY *
			sin(cub->rotateSpeed);
		cub->planeY = cub->oldPlaneX * sin(cub->rotateSpeed) + cub->planeY *
			cos(cub->rotateSpeed);
	}
	if (cub->keyboard[124])
	{
		cub->dirX = cub->dirX * cos(-cub->rotateSpeed) - cub->dirY *
			sin(-cub->rotateSpeed);
		cub->dirY = cub->oldDirX * sin(-cub->rotateSpeed) + cub->dirY *
			cos(-cub->rotateSpeed);
		cub->oldPlaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(-cub->rotateSpeed) - cub->planeY *
			sin(-cub->rotateSpeed);
		cub->planeY = cub->oldPlaneX * sin(-cub->rotateSpeed) + cub->planeY *
			cos(-cub->rotateSpeed);
	}
}
