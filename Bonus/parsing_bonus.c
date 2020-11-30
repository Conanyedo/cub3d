/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:01:50 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/26 18:33:03 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	cub->res.w = (cub->res.w <= 0) ? cub->res.max_w : cub->res.w;
	cub->res.w = (cub->res.w > cub->res.max_w) ? cub->res.max_w : cub->res.w;
	cub->res.h = ft_atoi(cub->parse.splitted[2]);
	cub->res.h = (cub->res.h <= 0) ? cub->res.max_h : cub->res.h;
	cub->res.h = (cub->res.h > cub->res.max_h) ? cub->res.max_h : cub->res.h;
	ft_free(cub->parse.splitted);
	cub->rep.res = 1;
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
		if ((cub->parse.line[0] == 'S' || cub->parse.line[0] == 'F'
			|| cub->parse.line[0] == 'C') && cub->parse.line[1] != 'O')
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
	else if (*cub->parse.line == 'F' && *(cub->parse.line + 1) == ' ')
		path(&cub->path.f, cub, &cub->fd.f, &cub->rep.f);
	else if (*cub->parse.line == 'C' && *(cub->parse.line + 1) == ' ')
		path(&cub->path.c, cub, &cub->fd.c, &cub->rep.c);
}
