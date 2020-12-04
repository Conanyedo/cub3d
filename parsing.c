/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:01:50 by ybouddou          #+#    #+#             */
/*   Updated: 2020/12/02 17:10:01 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resolution(t_cub3d *cub)
{
	if (cub->rep.res == 1)
		error_msg_free("ERROR\nRepetition of res", cub);
	if (cub->parse.line[1] != ' ')
		error_msg_free("ERROR\nAnother char found after R", cub);
	cub->parse.splitted = ft_split(cub->parse.line, ' ');
	if (cub->parse.splitted[3] || !cub->parse.splitted[2])
		error_free("ERROR\nR must have only 2 param", cub, cub->parse.splitted);
	checker(cub->parse.splitted, cub, 1);
	cub->res.w = ft_atoi(cub->parse.splitted[1]);
	cub->res.w = (cub->res.w < 0) ? 2560 : cub->res.w;
	cub->res.w = (cub->res.w > 2560) ? 2560 : cub->res.w;
	cub->res.h = ft_atoi(cub->parse.splitted[2]);
	cub->res.h = (cub->res.h < 0) ? 1440 : cub->res.h;
	cub->res.h = (cub->res.h > 1440) ? 1440 : cub->res.h;
	ft_free(cub->parse.splitted);
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
	checker(parse->colors, cub, 0);
	fc->r = ft_atoi(parse->colors[0]);
	fc->g = ft_atoi(parse->colors[1]);
	fc->b = ft_atoi(parse->colors[2]);
	ft_free(parse->colors);
	range(fc, cub);
	*rep = 1;
}

void	fc(t_cub3d *cub)
{
	if (*cub->parse.line == 'F')
	{
		if (cub->rep.f == 1)
			error_msg_free("Error\nRepetition of F\n", cub);
		if (cub->parse.line[1] != ' ')
			error_msg_free("Error\nAnother char found after F\n", cub);
		cub->parse.splitted = ft_split(cub->parse.line, ' ');
		fc_checker(&cub->parse, cub);
		cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
		fc_color(&cub->f, &cub->parse, &cub->rep.f, cub);
	}
	else if (*cub->parse.line == 'C')
	{
		if (cub->rep.c == 1)
			error_msg_free("Error\nRepetition of C\n", cub);
		if (cub->parse.line[1] != ' ')
			error_msg_free("Error\nAnother char found after C\n", cub);
		cub->parse.splitted = ft_split(cub->parse.line, ' ');
		fc_checker(&cub->parse, cub);
		cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
		fc_color(&cub->c, &cub->parse, &cub->rep.c, cub);
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
	ext_error(*path, ".xpm", fd);
	*rep = 1;
}

void	identifier(t_cub3d *cub)
{
	if (*cub->parse.line == 'S' && *(cub->parse.line + 1) != 'O')
		path(&cub->path.s, cub, &cub->fd.s, &cub->rep.s);
	else if (*cub->parse.line == 'N' && *(cub->parse.line + 1) == 'O')
		path(&cub->path.no, cub, &cub->fd.no, &cub->rep.no);
	else if (*cub->parse.line == 'S' && *(cub->parse.line + 1) == 'O')
		path(&cub->path.so, cub, &cub->fd.so, &cub->rep.so);
	else if (*cub->parse.line == 'W' && *(cub->parse.line + 1) == 'E')
		path(&cub->path.we, cub, &cub->fd.we, &cub->rep.we);
	else if (*cub->parse.line == 'E' && *(cub->parse.line + 1) == 'A')
		path(&cub->path.ea, cub, &cub->fd.ea, &cub->rep.ea);
}
