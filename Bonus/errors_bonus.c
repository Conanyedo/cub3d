/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:08:52 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/25 14:29:54 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	exist(t_cub3d *cub)
{
	if (cub->rep.res == 0)
		error_msg_free("ERROR\nResolution not found", cub);
	else if (cub->rep.no == 0 || cub->rep.so == 0 || cub->rep.ea == 0 ||
		cub->rep.we == 0 || cub->rep.s == 0)
		error_msg_free("ERROR\nPath not found", cub);
	else if (cub->rep.f == 0)
		error_msg_free("ERROR\nF not found", cub);
	else if (cub->rep.c == 0)
		error_msg_free("ERROR\nC not found", cub);
	if (cub->parse.x == 0)
	{
		cub->map = (char**)malloc(2 * sizeof(char*));
		cub->map[0] = ft_strdup(cub->parse.line);
		cub->map[1] = NULL;
	}
	else
		push(cub);
}

void	error_msg_free(char *s, t_cub3d *cub)
{
	free(cub->parse.line);
	free(cub->path.no);
	free(cub->path.so);
	free(cub->path.ea);
	free(cub->path.we);
	free(cub->path.s);
	free(cub->path.f);
	free(cub->path.c);
	if (cub->parse.x > 0)
		ft_free(cub->map);
	ft_putstr_fd(s, 2);
	exit(1);
}

void	error_free(char *s, t_cub3d *cub, char **tofree)
{
	ft_free(tofree);
	free(cub->parse.line);
	free(cub->path.no);
	free(cub->path.so);
	free(cub->path.ea);
	free(cub->path.we);
	free(cub->path.s);
	free(cub->path.f);
	free(cub->path.c);
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
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
