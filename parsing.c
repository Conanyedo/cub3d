/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:01:50 by ybouddou          #+#    #+#             */
/*   Updated: 2020/10/19 20:10:03 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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