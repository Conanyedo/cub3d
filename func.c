/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 01:49:26 by ybouddou          #+#    #+#             */
/*   Updated: 2020/10/16 13:19:49 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_cub3d *cub)
{
	// cub->dirX = -1;
	// cub->dirY = 0;
	// cub->posX = 14;
	// cub->posY = 12;
	cub->planeX = 0;
	cub->planeY = 0.66;
	cub->rotateSpeed = 0.03;
	cub->moveSpeed = 0.3;
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
	cub->change = 0;
	cub->look = 0;
	cub->rep.res = 0;
	cub->rep.NO = 0;
	cub->rep.SO = 0;
	cub->rep.WE = 0;
	cub->rep.EA = 0;
	cub->rep.S = 0;
	cub->rep.F = 0;
	cub->rep.C = 0;
}

void	exist(t_cub3d *cub)
{
	if (cub->rep.res == 0)
		error_msg("ERROR\nResolution not found");
	else if (cub->rep.NO == 0 || cub->rep.SO == 0 || cub->rep.EA == 0 ||
		cub->rep.WE == 0 || cub->rep.S == 0)
		error_msg("ERROR\nPath not found");
	else if (cub->rep.F == 0)
		error_msg("ERROR\nF not found");
	else if (cub->rep.C == 0)
		error_msg("ERROR\nC not found");
}

void	error_msg_free(char *s, char **tofree)
{
	ft_free(tofree);
	ft_putstr_fd(s, 2);
	exit (1);
}

void	error_msg(char *s)
{
	ft_putstr_fd(s, 2);
	exit (1);
}

void	resolution(t_cub3d *cub)
{
	if (cub->rep.res == 1)
		error_msg("ERROR\nRepetition of res");
	cub->parse.line++;
	if (*cub->parse.line != ' ')
		error_msg("ERROR\nAnother char found after R");
	cub->parse.splitted = ft_split(cub->parse.line, ' ');
	if (cub->parse.splitted[2] || !cub->parse.splitted[1])
		error_msg_free("ERROR\nR has more or less than 2 param", cub->parse.splitted);
	checker(cub->parse.splitted);
	cub->res.w = (ft_atoi(cub->parse.splitted[0]) > 2560) ? 2560 : ft_atoi(cub->parse.splitted[0]);
	cub->res.w = cub->res.w < 640 ? 640 : cub->res.w;
	cub->res.h = (ft_atoi(cub->parse.splitted[1]) > 1440) ? 1440 : ft_atoi(cub->parse.splitted[1]);
	cub->res.h = cub->res.h < 360 ? 360 : cub->res.h;
	ft_free(cub->parse.splitted);
	printf("R : %d | %d\n", cub->res.w, cub->res.h);
	cub->rep.res = 1;
}

void	FC_checker(t_rgb *FC, t_parse *parse, int *rep)
{
	ft_free(parse->splitted);
	parse->rgb = 0;
	while (parse->colors[parse->rgb])
		parse->rgb++;
	if (parse->rgb != 3)
		error_msg_free("Error\nWrong format of rgb\n", parse->colors);
	checker(parse->colors);
	FC->r = ft_atoi(parse->colors[0]);
	FC->g = ft_atoi(parse->colors[1]);
	FC->b = ft_atoi(parse->colors[2]);
	ft_free(parse->colors);
	range(FC);
	*rep = 1;
	printf("F/C |r : %d | g : %d | g : %d|\n", FC->r, FC->g, FC->b);
}

void	FC(t_cub3d *cub)
{
	if (*cub->parse.line == 'F')
	{
		if (cub->rep.F == 1)
			error_msg("Error\nRepetition of F\n");
		if (cub->parse.line[1] != ' ')
			error_msg("Error\nAnother char found after F\n");
		cub->parse.splitted = ft_split(cub->parse.line, ' ');
		if (cub->parse.splitted[2])
			error_msg_free("Error\nAnother char found after F\n", cub->parse.splitted);
		cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
		FC_checker(&cub->F, &cub->parse, &cub->rep.F);
	}
	else if (*cub->parse.line == 'C')
	{
		if (cub->rep.C == 1)
			error_msg("Error\nRepetition of C\n");
		if (cub->parse.line[1] != ' ')
			error_msg("Error\nAnother char found after C\n");
		cub->parse.splitted = ft_split(cub->parse.line, ' ');
		if (cub->parse.splitted[2])
			error_msg_free("Error\nAnother char found after C\n", cub->parse.splitted);
		cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
		FC_checker(&cub->C, &cub->parse, &cub->rep.C);
	}
}

void	path(char **path, t_parse *parse, int *fd, int *rep)
{
	if (*rep == 1)
		error_msg("Error\nAdditional path found\n");
		if (parse->line[0] == 'S' && parse->line[1] != 'O' && parse->line[2] == ' ')
				error_msg("Error\nInvalid indentifier\n");
	if (parse->line[2] != ' ')
	{
		if (parse->line[0] == 'S' && parse->line[1] != 'O')
		{
			if (parse->line[1] != ' ')
				error_msg("Error\nInvalid indentifier\n");	
		}
		else
			error_msg("Error\nInvalid indentifier\n");
	}
	parse->splitted = ft_split(parse->line, ' ');
	if (parse->splitted[2])
		error_msg_free("Error\nIdentifier has more than 2 param\n", parse->splitted);
	*path = ft_strdup(parse->splitted[1]);
	ft_free(parse->splitted);
	*fd = open(*path, O_RDONLY);
	if (*fd == -1)
		error_msg_free("Error\nPath not found\n", path);
	*rep = 1;
}

void	identifier(t_cub3d *cub)
{
	if (*cub->parse.line == 'S' && *(cub->parse.line + 1) != 'O')
	{
		path(&cub->path.S, &cub->parse, &cub->fd.S, &cub->rep.S);
		printf("S : %s\n", cub->path.S);
	}
	else if (*cub->parse.line == 'N' && *(cub->parse.line + 1) == 'O')
	{
		path(&cub->path.NO, &cub->parse, &cub->fd.NO, &cub->rep.NO);
		printf("NO : %s\n", cub->path.NO);
	}
	else if (*cub->parse.line == 'S' && *(cub->parse.line + 1) == 'O')
	{
		path(&cub->path.SO, &cub->parse, &cub->fd.SO, &cub->rep.SO);
		printf("SO : %s\n", cub->path.SO);
	}
	else if (*cub->parse.line == 'W' && *(cub->parse.line + 1) == 'E')
	{
		path(&cub->path.WE, &cub->parse, &cub->fd.WE, &cub->rep.WE);
		printf("WE : %s\n", cub->path.WE);
	}
	else if (*cub->parse.line == 'E' && *(cub->parse.line + 1) == 'A')
	{
		path(&cub->path.EA, &cub->parse, &cub->fd.EA, &cub->rep.EA);
		printf("EA : %s\n", cub->path.EA);
	}
}

void	ft_free(char **arr)
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

void	moves(t_cub3d *cub)
{
	if (cub->keyboard[13])
	{
		if(cub->map[(int)(cub->posX + cub->dirX * cub->moveSpeed)][(int)(cub->posY)] == '0') 
			cub->posX += cub->dirX * cub->moveSpeed;
		if(cub->map[(int)(cub->posX)][(int)(cub->posY + cub->dirY * cub->moveSpeed)] == '0') 
			cub->posY += cub->dirY * cub->moveSpeed;
	}
	if (cub->keyboard[0])
	{
		if(cub->map[(int)(cub->posX - cub->planeX * cub->moveSpeed)][(int)(cub->posY)] == '0')
			cub->posX -= cub->planeX * cub->moveSpeed;
		if(cub->map[(int)(cub->posX)][(int)(cub->posY - cub->planeY * cub->moveSpeed)] == '0')
			cub->posY -= cub->planeY * cub->moveSpeed;
	}
	if (cub->keyboard[1])
	{
		if(cub->map[(int)(cub->posX - cub->dirX * cub->moveSpeed)][(int)(cub->posY)] == '0')
			cub->posX -= cub->dirX * cub->moveSpeed;
		if(cub->map[(int)(cub->posX)][(int)(cub->posY - cub->dirY * cub->moveSpeed)] == '0')
			cub->posY -= cub->dirY * cub->moveSpeed;
	}
	if (cub->keyboard[2])
	{
		if(cub->map[(int)(cub->posX + cub->planeX * cub->moveSpeed)][(int)(cub->posY)] == '0')
			cub->posX += cub->planeX * cub->moveSpeed;
		if(cub->map[(int)(cub->posX)][(int)(cub->posY + cub->planeY * cub->moveSpeed)] == '0')
			cub->posY += cub->planeY * cub->moveSpeed;
	}
}

void	look(t_cub3d *cub)
{
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
	}
}

void	calc(t_cub3d *cub)
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
}

void	hit(t_cub3d *cub)
{
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
		if(cub->side == 0 && cub->rayDirX < 0)
			cub->side = 2;
		else if(cub->side == 1 && cub->rayDirY < 0)
			cub->side = 3;
		if (cub->map[cub->mapX][cub->mapY] > '0')
			cub->hit = 1;
	}
}