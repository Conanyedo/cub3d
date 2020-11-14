/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:01:50 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/12 10:19:27 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resolution(t_cub3d *cub)
{
	if (cub->rep.res == 1)
		error_msg_free("ERROR\nRepetition of res", cub);
	cub->parse.line++;
	if (*cub->parse.line != ' ')
		error_msg_free("ERROR\nAnother char found after R", cub);
	cub->parse.splitted = ft_split(cub->parse.line, ' ');
	if (cub->parse.splitted[2] || !cub->parse.splitted[1])
		error_free("ERROR\nR must have only 2 param", cub, cub->parse.splitted);
	checker(cub->parse.splitted, cub);
	cub->res.w = ft_atoi(cub->parse.splitted[0]);
	cub->res.w = (cub->res.w > 2560) ? 2560 : cub->res.w;
	cub->res.w = cub->res.w < 640 ? 640 : cub->res.w;
	cub->res.h = ft_atoi(cub->parse.splitted[1]);
	cub->res.h = (cub->res.h > 1440) ? 1440 : cub->res.h;
	cub->res.h = cub->res.h < 360 ? 360 : cub->res.h;
	ft_free(cub->parse.splitted);
	printf("R : %d | %d\n", cub->res.w, cub->res.h);
	cub->rep.res = 1;
}

void	fc_color(t_rgb *fc, t_parse *parse, int *rep, t_cub3d *cub)
{
	ft_free(parse->splitted);
	parse->rgb = 0;
	while (parse->colors[parse->rgb])
		parse->rgb++;
	if (parse->rgb != 3)
		error_free("Error\nWrong format of rgb\n", cub, parse->colors);
	checker(parse->colors, cub);
	fc->r = ft_atoi(parse->colors[0]);
	fc->g = ft_atoi(parse->colors[1]);
	fc->b = ft_atoi(parse->colors[2]);
	ft_free(parse->colors);
	range(fc, cub);
	*rep = 1;
	printf("F/C |r : %d | g : %d | g : %d|\n", fc->r, fc->g, fc->b);
}

void	fc(t_cub3d *cub)
{
	if (*cub->parse.line == 'F')
	{
		if (cub->rep.F == 1)
			error_msg_free("Error\nRepetition of F\n", cub);
		if (cub->parse.line[1] != ' ')
			error_msg_free("Error\nAnother char found after F\n", cub);
		cub->parse.splitted = ft_split(cub->parse.line, ' ');
		fc_checker(&cub->parse, cub);
		cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
		fc_color(&cub->F, &cub->parse, &cub->rep.F, cub);
	}
	else if (*cub->parse.line == 'C')
	{
		if (cub->rep.C == 1)
			error_msg_free("Error\nRepetition of C\n", cub);
		if (cub->parse.line[1] != ' ')
			error_msg_free("Error\nAnother char found after C\n", cub);
		cub->parse.splitted = ft_split(cub->parse.line, ' ');
		fc_checker(&cub->parse, cub);
		cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
		fc_color(&cub->C, &cub->parse, &cub->rep.C, cub);
	}
}

void	path(char **path, t_cub3d *cub, int *fd, int *rep)
{
	if (*rep == 1)
		error_msg_free("Error\nAdditional path found\n", cub);
	if (cub->parse.line[0] == 'S' && cub->parse.line[1] != 'O'
		&& cub->parse.line[2] == ' ')
		error_msg_free("Error\nInvalid indentifier\n", cub);
	if (cub->parse.line[2] != ' ')
	{
		if (cub->parse.line[0] == 'S' && cub->parse.line[1] != 'O')
		{
			if (cub->parse.line[1] != ' ')
				error_msg_free("Error\nInvalid indentifier\n", cub);
		}
		else
			error_msg_free("Error\nInvalid indentifier\n", cub);
	}
	cub->parse.splitted = ft_split(cub->parse.line, ' ');
	if (cub->parse.splitted[2])
		error_free("Error\nInvalid indentifier\n", cub, cub->parse.splitted);
	*path = ft_strdup(cub->parse.splitted[1]);
	ft_free(cub->parse.splitted);
	*fd = open(*path, O_RDONLY);
	if (*fd == -1)
		error_msg_free("Error\nPath not found\n", cub);
	*rep = 1;
}

void	identifier(t_cub3d *cub)
{
	if (*cub->parse.line == 'S' && *(cub->parse.line + 1) != 'O')
	{
		path(&cub->path.S, cub, &cub->fd.S, &cub->rep.S);
		printf("S : %s\n", cub->path.S);
	}
	else if (*cub->parse.line == 'N' && *(cub->parse.line + 1) == 'O')
	{
		path(&cub->path.NO, cub, &cub->fd.NO, &cub->rep.NO);
		printf("NO : %s\n", cub->path.NO);
	}
	else if (*cub->parse.line == 'S' && *(cub->parse.line + 1) == 'O')
	{
		path(&cub->path.SO, cub, &cub->fd.SO, &cub->rep.SO);
		printf("SO : %s\n", cub->path.SO);
	}
	else if (*cub->parse.line == 'W' && *(cub->parse.line + 1) == 'E')
	{
		path(&cub->path.WE, cub, &cub->fd.WE, &cub->rep.WE);
		printf("WE : %s\n", cub->path.WE);
	}
	else if (*cub->parse.line == 'E' && *(cub->parse.line + 1) == 'A')
	{
		path(&cub->path.EA, cub, &cub->fd.EA, &cub->rep.EA);
		printf("EA : %s\n", cub->path.EA);
	}
}