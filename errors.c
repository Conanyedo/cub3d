/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:08:52 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/11 10:36:09 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exist(t_cub3d *cub)
{
	if (cub->rep.res == 0)
		error_msg_free("ERROR\nResolution not found", cub);
	else if (cub->rep.NO == 0 || cub->rep.SO == 0 || cub->rep.EA == 0 ||
		cub->rep.WE == 0 || cub->rep.S == 0)
		error_msg_free("ERROR\nPath not found", cub);
	else if (cub->rep.F == 0)
		error_msg_free("ERROR\nF not found", cub);
	else if (cub->rep.C == 0)
		error_msg_free("ERROR\nC not found", cub);
	else if (cub->parse.mapline == 0)
		error_msg_free("ERROR\nMap not found", cub);
	free(cub->parse.line);
}

void	error_msg_free(char *s, t_cub3d *cub)
{
	free(cub->parse.line);
	free(cub->path.NO);
	free(cub->path.SO);
	free(cub->path.EA);
	free(cub->path.WE);
	free(cub->path.S);
	if (cub->parse.X > 0)
		ft_free(cub->map);
	ft_putstr_fd(s, 2);
	exit(1);
}

void	error_free(char *s, t_cub3d *cub, char **tofree)
{
	ft_free(tofree);
	free(cub->parse.line);
	free(cub->path.NO);
	free(cub->path.SO);
	free(cub->path.EA);
	free(cub->path.WE);
	free(cub->path.S);
	ft_putstr_fd(s, 2);
	exit(1);
}

void	error_msg(char *s)
{
	ft_putstr_fd(s, 2);
	exit(1);
}

void	ft_free(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	arr = NULL;
}
