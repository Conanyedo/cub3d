/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:13:25 by ybouddou          #+#    #+#             */
/*   Updated: 2020/03/13 19:46:16 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_png.h"
#include <math.h>
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "cub3d.h"


#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64

int		worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw(t_cub3d *cub)
{
	
	cub->img.img_ptr = mlx_new_image(cub->mlx.p, cub->res.w, cub->res.h);
	cub->img.img_data = (int *)mlx_get_data_addr(cub->img.img_ptr, &cub->img.bpp, &cub->img.size_line, &cub->img.endian);
	
	cub->ray = 0;
	while (cub->ray < cub->res.w)
	{
		cub->img.h = 0;
		cub->cameraX = 2 * cub->ray / (double)cub->res.w - 1;
		cub->rayDirX = cub->dirX + cub->planeX * cub->cameraX;
		cub->rayDirY = cub->dirY + cub->planeY * cub->cameraX;

		cub->mapX = (int)cub->posX;
		cub->mapY = (int)cub->posY;

		cub->deltaDistX = sqrt(1 + (cub->rayDirY * cub->rayDirY) / (cub->rayDirX * cub->rayDirX));
		cub->deltaDistY = sqrt(1 + (cub->rayDirX * cub->rayDirX) / (cub->rayDirY * cub->rayDirY));
		
		cub->hit = 0;

		cub->deltaDistX = (cub->rayDirY == 0) ? 0 : ((cub->rayDirX == 0) ? 1 : cub->deltaDistX);
		cub->deltaDistY = (cub->rayDirX == 0) ? 0 : ((cub->rayDirY == 0) ? 1 : cub->deltaDistY);

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
		while (cub->hit == 0)
		{
			if (cub->sideDistX < cub->sideDistY)
			{
				cub->sideDistX += cub->deltaDistX;
				cub->mapX += cub->stepX;
				cub->side= 0;
			}
			else
			{
				cub->sideDistY += cub->deltaDistY;
				cub->mapY += cub->stepY;
				cub->side = 1;
			}
			// if(cub->side == 0 && cub->rayDirX < 0)
			// {
			// 	cub->side = 2;
			// }
			// else if(cub->side == 1 && cub->rayDirY < 0)
			// {
			// 	cub->side = 3;
			// }
			if (worldMap[cub->mapX][cub->mapY] > 0)
				cub->hit = 1;
		}
		if (cub->side == 0 /*|| cub->side == 2*/)
			cub->perpWallDist = (cub->mapX - cub->posX + (1 - cub->stepX) / 2) / cub->rayDirX;
		else
			cub->perpWallDist = (cub->mapY - cub->posY + (1 - cub->stepY) / 2) / cub->rayDirY;

		
		cub->lineHeight = (int)(cub->res.h / cub->perpWallDist);
		cub->drawStart = -cub->lineHeight / 2 + cub->res.h / 2;
		if(cub->drawStart < 0)
			cub->drawStart = 0;
		cub->drawEnd = cub->lineHeight / 2 + cub->res.h / 2;
		if(cub->drawEnd >= cub->res.h)
			cub->drawEnd = cub->res.h - 1;
		

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (cub->side == 0)
			wallX = cub->posY + cub->perpWallDist * cub->rayDirY;
		else
			wallX = cub->posX + cub->perpWallDist * cub->rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(texWidth));
		if(cub->side == 0 && cub->rayDirX > 0) texX = texWidth - texX - 1;
		if(cub->side == 1 && cub->rayDirY < 0) texX = texWidth - texX - 1;
		// How much to increase the texture coordinate per screen pixel
      	double step = 1.0 * texHeight / cub->lineHeight;
      	// Starting texture coordinate
      	double texPos = (cub->drawStart - cub->res.h / 2 + cub->lineHeight / 2) * step;

		
		// int color;
		// if(cub->side == 0)
		// 	color = 0xFF2500;
		// else if(cub->side ==1)
		// 	color = 0x0044ed4;
		// else if(cub->side ==2)
		// 	color = 0x4EBDAD;
		// else if(cub->side ==3)
		// 	color = 0xF3CE00;
		// if (cub->change == 1)
		// {
		// 	cub->drawStart += cub->look;
		// 	cub->drawEnd += cub->look;
		// }
		// else if (cub->change == -1)
		// {
		// 	cub->drawStart += cub->look;
		// 	cub->drawEnd += cub->look;
		// }
		while (cub->img.h < cub->res.h)
		{
			if (cub->img.h < cub->drawStart)
				cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = createRGB(&cub->C);
			if (cub->img.h >= cub->drawStart && cub->img.h <= cub->drawEnd)
			{
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[0].img_data[texX + texY * cub->txt[0].w];
			}
			else if (cub->img.h > cub->drawEnd)
				cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = createRGB(&cub->F);
			cub->img.h++;
		}
		cub->ray++;
	}
	mlx_put_image_to_window(cub->mlx.p, cub->mlx.w, cub->img.img_ptr, 0, 0);
}

int		deal_key(t_cub3d *cub)
{
	mlx_clear_window(cub->mlx.p, cub->mlx.w);
	if (cub->keyboard[13])
	{
		if(worldMap[(int)(cub->posX + cub->dirX * cub->moveSpeed)][(int)(cub->posY)] == 0) 
			cub->posX += cub->dirX * cub->moveSpeed;
		if(worldMap[(int)(cub->posX)][(int)(cub->posY + cub->dirY * cub->moveSpeed)] == 0) 
			cub->posY += cub->dirY * cub->moveSpeed;
	}
	if (cub->keyboard[0])
	{
		if(worldMap[(int)(cub->posX - cub->planeX * cub->moveSpeed)][(int)(cub->posY)] == 0)
			cub->posX -= cub->planeX * cub->moveSpeed;
		if(worldMap[(int)(cub->posX)][(int)(cub->posY - cub->planeY * cub->moveSpeed)] == 0)
			cub->posY -= cub->planeY * cub->moveSpeed;
	}
	if (cub->keyboard[1])
	{
		if(worldMap[(int)(cub->posX - cub->dirX * cub->moveSpeed)][(int)(cub->posY)] == 0)
			cub->posX -= cub->dirX * cub->moveSpeed;
		if(worldMap[(int)(cub->posX)][(int)(cub->posY - cub->dirY * cub->moveSpeed)] == 0)
			cub->posY -= cub->dirY * cub->moveSpeed;
	}
	if (cub->keyboard[2])
	{
		if(worldMap[(int)(cub->posX + cub->planeX * cub->moveSpeed)][(int)(cub->posY)] == 0)
			cub->posX += cub->planeX * cub->moveSpeed;
		if(worldMap[(int)(cub->posX)][(int)(cub->posY + cub->planeY * cub->moveSpeed)] == 0)
			cub->posY += cub->planeY * cub->moveSpeed;
	}
	if(cub->keyboard[123])
	{
		cub->oldDirX = cub->dirX;
		cub->dirX = cub->dirX * cos(cub->rotateSpeed) - cub->dirY * sin(cub->rotateSpeed);
      	cub->dirY = cub->oldDirX * sin(cub->rotateSpeed) + cub->dirY * cos(cub->rotateSpeed);
      	cub->oldPlaneX = cub->planeX;
     	cub->planeX = cub->planeX * cos(cub->rotateSpeed) - cub->planeY * sin(cub->rotateSpeed);
     	cub->planeY = cub->oldPlaneX * sin(cub->rotateSpeed) + cub->planeY * cos(cub->rotateSpeed);
	}
	if (cub->keyboard[124])
	{
		cub->oldDirX = cub->dirX;
		cub->dirX = cub->dirX * cos(-cub->rotateSpeed) - cub->dirY * sin(-cub->rotateSpeed);
      	cub->dirY = cub->oldDirX * sin(-cub->rotateSpeed) + cub->dirY * cos(-cub->rotateSpeed);
      	cub->oldPlaneX = cub->planeX;
     	cub->planeX = cub->planeX * cos(-cub->rotateSpeed) - cub->planeY * sin(-cub->rotateSpeed);
     	cub->planeY = cub->oldPlaneX * sin(-cub->rotateSpeed) + cub->planeY * cos(-cub->rotateSpeed);
	}//lookup
	if(cub->keyboard[126])
	{
		cub->change = 1;
		// // if (cub->drawStart <= 1065)
		// 	cub->look += 5;
	}//lookdown
	if(cub->keyboard[125])
	{
		cub->change = -1;
		// if (cub->drawEnd >= 10)
			cub->look -= 5;
	}
	if(cub->keyboard[53])
		exit(0);
	draw(cub);
	return (0);
}

void	parsing(int fd, t_cub3d *cub)
{
	
	while (cub->parse.r == 1)
	{
		cub->parse.r = get_next_line(fd, &cub->parse.line);
		if (*cub->parse.line == 'R')
		{
			cub->parse.line++;
			cub->parse.splitted = ft_split(cub->parse.line, ' ');
			cub->res.w = (ft_atoi(cub->parse.splitted[0]) > 2560) ? 2560 : ft_atoi(cub->parse.splitted[0]);
			cub->res.w = cub->res.w < 640 ? 640 : cub->res.w;
			cub->res.h = (ft_atoi(cub->parse.splitted[1]) > 1440) ? 1440 : ft_atoi(cub->parse.splitted[1]);
			cub->res.h = cub->res.h < 360 ? 360 : cub->res.h;
			checker(cub->parse.splitted);
			ft_free(cub->parse.splitted);
			printf("R : %d | %d\n", cub->res.w, cub->res.h);
		}
		else if (*cub->parse.line == 'N' && *(cub->parse.line + 1) == 'O')
		{
			cub->parse.splitted = ft_split(cub->parse.line, ' ');
			cub->path.NO = ft_strdup(cub->parse.splitted[1]);
			ft_free(cub->parse.splitted);
			printf("NO : %s\n", cub->path.NO);
		}
		else if (*cub->parse.line == 'S' && *(cub->parse.line + 1) == 'O')
		{
			cub->parse.splitted = ft_split(cub->parse.line, ' ');
			cub->path.SO = ft_strdup(cub->parse.splitted[1]);
			ft_free(cub->parse.splitted);
			printf("SO : %s\n", cub->path.SO);
		}
		else if (*cub->parse.line == 'W' && *(cub->parse.line + 1) == 'E')
		{
			cub->parse.splitted = ft_split(cub->parse.line, ' ');
			cub->path.WE = ft_strdup(cub->parse.splitted[1]);
			ft_free(cub->parse.splitted);
			printf("WE : %s\n", cub->path.WE);
		}
		else if (*cub->parse.line == 'E' && *(cub->parse.line + 1) == 'A')
		{
			cub->parse.splitted = ft_split(cub->parse.line, ' ');
			cub->path.EA = ft_strdup(cub->parse.splitted[1]);
			ft_free(cub->parse.splitted);
			printf("EA : %s\n", cub->path.EA);
		}
		else if (*cub->parse.line == 'S')
		{
			cub->parse.splitted = ft_split(cub->parse.line, ' ');
			cub->path.S = ft_strdup(cub->parse.splitted[1]);
			ft_free(cub->parse.splitted);
			printf("S  : %s\n", cub->path.S);
		}
		else if (*cub->parse.line == 'F')
		{
			cub->parse.splitted = ft_split(cub->parse.line, ' ');
			cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
			cub->F.r = ft_atoi(cub->parse.colors[0]);
			cub->F.g = ft_atoi(cub->parse.colors[1]);
			cub->F.b = ft_atoi(cub->parse.colors[2]);
			checker(cub->parse.colors);
			ft_free(cub->parse.splitted);
			ft_free(cub->parse.colors);
			range(&cub->F);
			printf("F |r : %d | g : %d | g : %d|\n", cub->F.r, cub->F.g, cub->F.b);
		}
		else if (*cub->parse.line == 'C')
		{
			cub->parse.splitted = ft_split(cub->parse.line, ' ');
			cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
			cub->C.r = ft_atoi(cub->parse.colors[0]);
			cub->C.g = ft_atoi(cub->parse.colors[1]);
			cub->C.b = ft_atoi(cub->parse.colors[2]);
			checker(cub->parse.colors);
			ft_free(cub->parse.splitted);
			ft_free(cub->parse.colors);
			range(&cub->C);
			printf("C |r : %d | g : %d | g : %d|\n", cub->C.r, cub->C.g, cub->C.b);
		}
	}
}

int		main(int ac, char **av)
{
	if (ac == 2)
	{
		t_cub3d	cub;
		int		fd = open(av[1], O_RDONLY);

		init(&cub);
		parsing(fd, &cub);
		
		
		cub.mlx.p = mlx_init();
		cub.mlx.w = mlx_new_window(cub.mlx.p, cub.res.w, cub.res.h, "cub3d");
		
		cub.txt[0].img_ptr = mlx_png_file_to_image(cub.mlx.p, "bluestone.png", &cub.txt[0].w, &cub.txt[0].h);
		cub.txt[0].img_data = (int*)mlx_get_data_addr(cub.txt[0].img_ptr, &cub.txt[0].bpp, &cub.txt[0].size_line, &cub.txt[0].endian);
		
		cub.txt[1].img_ptr = mlx_png_file_to_image(cub.mlx.p, "colorstone.png", &cub.txt[1].w, &cub.txt[1].h);
		cub.txt[1].img_data = (int*)mlx_get_data_addr(cub.txt[1].img_ptr, &cub.txt[1].bpp, &cub.txt[1].size_line, &cub.txt[1].endian);
		
		cub.txt[2].img_ptr = mlx_png_file_to_image(cub.mlx.p, "eagle.png", &cub.txt[2].w, &cub.txt[2].h);
		cub.txt[2].img_data = (int*)mlx_get_data_addr(cub.txt[2].img_ptr, &cub.txt[2].bpp, &cub.txt[2].size_line, &cub.txt[2].endian);
		
		cub.txt[3].img_ptr = mlx_png_file_to_image(cub.mlx.p, "greystone.png", &cub.txt[3].w, &cub.txt[3].h);
		cub.txt[3].img_data = (int*)mlx_get_data_addr(cub.txt[3].img_ptr, &cub.txt[3].bpp, &cub.txt[3].size_line, &cub.txt[3].endian);
		
		// cub.txt[4].img_ptr = mlx_png_file_to_image(cub.mlx.p, "bluestone.png", &cub.txt[4].w, &cub.txt[4].h);
		// cub.txt[4].img_data = (int*)mlx_get_data_addr(cub.txt[4].img_ptr, &cub.txt[4].bpp, &cub.txt[4].size_line, &cub.txt[4].endian);
		
		draw(&cub);
		mlx_hook(cub.mlx.w, 2, 0, key_pressed, &cub);
		mlx_hook(cub.mlx.w, 3, 0, key_released, &cub);
		mlx_loop_hook(cub.mlx.p, deal_key, &cub);
		mlx_loop(cub.mlx.p);
	}
	return (0);
}