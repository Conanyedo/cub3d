/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 13:39:49 by ybouddou          #+#    #+#             */
/*   Updated: 2020/10/31 14:44:58 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    last_line(t_cub3d *cub)
{
	cub->parse.Y = 0;
    while (cub->map[cub->parse.X - 1][cub->parse.Y])
    {
        if (cub->map[cub->parse.X - 1][cub->parse.Y] > 'A' && cub->map[cub->parse.X][cub->parse.Y] != '1')
            error_msg("ERROR\nSpawning position in an invalid place");
        cub->parse.Y++;
    }
    cub->parse.Y = 0;
	while (cub->map[cub->parse.X][cub->parse.Y])
	{
		if (cub->map[cub->parse.X][cub->parse.Y] != ' ' && cub->map[cub->parse.X][cub->parse.Y] != '1')
            error_msg("ERROR\nLast line invalid");
		cub->parse.Y++;
	}
}

void    first_line(t_cub3d *cub)
{
    cub->parse.Y = 0;
    while (cub->map[cub->parse.X][cub->parse.Y])
    {
        if (cub->map[cub->parse.X][cub->parse.Y] != ' ' &&
         cub->map[cub->parse.X][cub->parse.Y] != '1')
            error_msg("ERROR\nFirst line invalid");
        cub->parse.Y++;
    }
}

void    map_errors(t_cub3d *cub)
{
	int i;

	i = -1;
    if (!cub->parse.spawn)
        error_msg("ERROR\nSpawning position not found or invalid");
    while (cub->map[--cub->parse.X][0] == '\0')
		cub->map[cub->parse.X] = NULL;
        last_line(cub);
	cub->parse.Y = 0;
	while (++i < cub->parse.X)
	{
		cub->parse.Y = 0;
		if (!cub->map[i][0])
            error_msg_free("ERROR\nEmpty line", cub->map);
		while (cub->map[i][cub->parse.Y])
		{
			if (cub->map[i][cub->parse.Y] == ' ' &&
             cub->map[i + 1][cub->parse.Y] == '0' && cub->parse.Y < (int)ft_strlen(cub->map[i + 1]))
                error_msg_free("ERROR\n0 beneath space", cub->map);
			else if (cub->map[i][cub->parse.Y] == '1')
				cub->parse.Y++;
			else if (cub->map[i][cub->parse.Y] == '0' &&
             (cub->map[i + 1][cub->parse.Y] == ' ' || cub->map[i + 1][cub->parse.Y] == '\0'))  
                error_msg_free("ERROR\nSpace or empty line beneath 0", cub->map);
            else if (cub->map[i][cub->parse.Y] == '2')
                sprite(cub, i);
            else
                cub->parse.Y++;
		}
	}
}

void    space(t_cub3d *cub)
{
    if (cub->map[cub->parse.X][cub->parse.Y - 1] != ' ' &&
     cub->map[cub->parse.X][cub->parse.Y - 1] != '1')
        error_msg_free("ERROR\nInvalid char before space", cub->map);
    else if (cub->map[cub->parse.X][cub->parse.Y + 1] != ' ' &&
     cub->map[cub->parse.X][cub->parse.Y + 1] != '1' && cub->map[cub->parse.X][cub->parse.Y + 1] != '\0')
        error_msg_free("ERROR\nInvalid char after space", cub->map);
    else if (cub->parse.X - 1 >= 0 && cub->map[cub->parse.X - 1][cub->parse.Y] != ' ' &&
     cub->map[cub->parse.X - 1][cub->parse.Y] != '1')
    {
        if (cub->parse.Y < (int)ft_strlen(cub->map[cub->parse.X - 1]))
            error_msg_free("ERROR\nInvalid char above space", cub->map);
    }
    cub->parse.Y++;
}

void    zero(t_cub3d *cub)
{
    if (cub->map[cub->parse.X][cub->parse.Y - 1] == ' ')
        error_msg_free("ERROR\nSpace before 0", cub->map);
    else if (cub->map[cub->parse.X][cub->parse.Y + 1] == ' ')
        error_msg_free("ERROR\nSpace after 0", cub->map);
    else if (cub->map[cub->parse.X][cub->parse.Y + 1] == '\0')
        error_msg_free("ERROR\n0 at the end of the line", cub->map);
    else if (cub->parse.X - 1 >= 0 && cub->map[cub->parse.X - 1][cub->parse.Y] <= 32)
        error_msg_free("ERROR\nSpace or empty line above 0", cub->map);
    cub->parse.Y++;
}
