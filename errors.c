/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:08:52 by ybouddou          #+#    #+#             */
/*   Updated: 2020/10/21 14:22:50 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	else if (cub->parse.mapline == 0)
		error_msg("ERROR\nMap not found");
}

void	error_msg_free(char *s, char **tofree)
{
	ft_free(tofree);
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
		free(arr[i++]);
	free(arr);
}

void	freeAll(t_cub3d *cub)
{
	//ft_free(cub->map);
	free(cub->path.NO);
	free(cub->path.SO);
	free(cub->path.EA);
	free(cub->path.WE);
	free(cub->path.S);
	ft_putstr_fd("Error\nWrong info\n", 2);
	exit(1);
}
