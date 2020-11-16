/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 13:39:49 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/16 12:25:25 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	last_line(t_cub3d *cub)
{
	cub->parse.Y = 0;
	while (cub->map[cub->parse.X - 1][cub->parse.Y])
	{
		if (cub->map[cub->parse.X - 1][cub->parse.Y] > 'E' &&
				cub->map[cub->parse.X][cub->parse.Y] != '1')
			error_msg_free("ERROR\nSpawning position in an invalid place", cub);
		cub->parse.Y++;
	}
	cub->parse.Y = 0;
	while (cub->map[cub->parse.X][cub->parse.Y])
	{
		if (cub->map[cub->parse.X][cub->parse.Y] != ' ' &&
				cub->map[cub->parse.X][cub->parse.Y] != '1')
			error_msg_free("ERROR\nLast line invalid", cub);
		cub->parse.Y++;
	}
}

void	first_line(t_cub3d *cub)
{
	cub->parse.Y = 0;
	while (cub->map[cub->parse.X][cub->parse.Y])
	{
		if (cub->map[cub->parse.X][cub->parse.Y] != ' ' &&
				cub->map[cub->parse.X][cub->parse.Y] != '1')
			error_msg_free("ERROR\nFirst line invalid", cub);
		cub->parse.Y++;
	}
}

void	map_errors(t_cub3d *cub)
{
	int	i;

	i = -1;
	if (!cub->parse.spawn)
		error_msg_free("ERROR\nSpawning position not found or invalid", cub);
	while (cub->map[--cub->parse.X][0] == '\0')
		cub->map[cub->parse.X] = NULL;
	last_line(cub);
	cub->parse.Y = 0;
	while (++i < cub->parse.X)
	{
		cub->parse.Y = 0;
		while (cub->map[i][cub->parse.Y])
		{
			map_check_next(cub, i);
			if (cub->map[i][cub->parse.Y] == '1')
				cub->parse.Y++;
			else if (cub->map[i][cub->parse.Y] == '2')
				spriteposition(cub, i);
			else
				cub->parse.Y++;
		}
	}
}

void	map_check_next(t_cub3d *cub, int i)
{
	if (cub->map[i][cub->parse.Y] == ' ' &&
			cub->map[i + 1][cub->parse.Y] == '0' &&
			cub->parse.Y < (int)ft_strlen(cub->map[i + 1]))
		error_msg_free("ERROR\n0 beneath space", cub);
	else if (cub->map[i][cub->parse.Y] == '0' &&
			(cub->map[i + 1][cub->parse.Y] == ' ' ||
			cub->map[i + 1][cub->parse.Y] == '\0'))
		error_msg_free("ERROR\nSpace or end of line beneath 0", cub);
}
