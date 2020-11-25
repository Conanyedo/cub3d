/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:47:27 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/25 13:38:43 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "Utils/utils.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_resolution
{
	int		h;
	int		w;
}				t_res;

typedef struct	s_mlx
{
	void	*p;
	void	*w;
}				t_mlx;

typedef	struct	s_fd
{
	int		lines;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		s;
}				t_fd;

typedef struct	s_repetition
{
	int		res;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		s;
	int		f;
	int		c;
}				t_rep;

typedef struct	s_path
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
}				t_path;

typedef struct	s_parse
{
	int		r;
	char	*line;
	char	**splitted;
	char	**colors;
	int		x;
	int		y;
	int		spawn;
	int		rgb;
}				t_parse;

typedef struct	s_img
{
	void	*img_ptr;
	int		*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		w;
	int		h;
}				t_img;

typedef struct	s_scale
{
	int		x;
	int		y;
}				t_scale;

typedef struct	s_mini
{
	int		x;
	int		y;
	int		len;
	int		row;
	int		mini_len;
	int		mini_row;
	t_scale	scale;
	int		show;
}				t_mini;

typedef struct	s_bmp
{
	int		pad;
	int		filesize;
	int		fd;
	int		i;
}				t_bmp;

typedef struct	s_rgb
{
	int		r;
	int		g;
	int		b;
}				t_rgb;

typedef struct	s_sprite
{
	double	x;
	double	y;
	double	dist;
	int		order;
}				t_sprite;

typedef struct	s_cub3d
{
	t_res		res;
	t_rep		rep;
	t_mlx		mlx;
	t_path		path;
	t_rgb		f;
	t_rgb		c;
	t_parse		parse;
	t_img		img;
	t_bmp		bmp;
	t_fd		fd;
	t_img		txt[5];
	t_sprite	*sprite;
	t_mini		mini;

	int			view;
	int			half_height;
	char		**mini_map;
	char		*image;
	int			color;
	int			len;
	int			ac;
	int			bmp_pos;
	int			abrv;
	int			keyboard[300];
	char		**map;
	char		**tmp;
	int			ray;
	int			mapx;
	int			mapy;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		olddirx;
	double		oldplanex;
	double		rotatespeed;
	double		movespeed;
	double		camerx;
	double		raydirx;
	double		raydiry;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			texwidth;
	int			texheight;
	double		wallx;
	int			tex_x;
	int			tex_y;
	double		step;
	double		texpos;
	int			sprite_num;
	int			sprite_n;
	double		*sprite_buf;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			drawstarty;
	int			drawstartx;
	int			drawendy;
	int			drawendx;
	int			spriteline;
	int			d;
}				t_cub3d;

void			init(t_cub3d *cub);
void			ft_free(char **arr);
void			checker(char **s, t_cub3d *cub, int i);
void			range(t_rgb *rgb, t_cub3d *cub);
int				key_pressed(int key, t_cub3d *cub);
int				key_released(int key, t_cub3d *cub);
int				key_close(t_cub3d *cub);
int				create_rgb(t_rgb *rgb);
void			resolution(t_cub3d *cub);
void			identifier(t_cub3d *cub);
void			fc(t_cub3d *cub);
void			sprit(t_cub3d *cub);
void			map(t_cub3d *cub);
void			map_checker(t_cub3d *cub);
void			map_errors(t_cub3d *cub);
void			map_check_next(t_cub3d *cub, int i);
void			push(t_cub3d *cub);
void			exist(t_cub3d *cub);
void			error_msg_free(char *s, t_cub3d *cub);
void			error_free(char *s, t_cub3d *cub, char **tofree);
void			error_msg(char *s);
void			free_path(t_cub3d *cub);
void			free_all(t_cub3d *cub);
void			fc_color(t_rgb *fc, t_parse *parse, int *rep, t_cub3d *cub);
void			fc_checker(t_parse *parse, t_cub3d *cub);
void			path(char **path, t_cub3d *cub, int *fd, int *rep);
void			first_line(t_cub3d *cub);
void			space(t_cub3d *cub);
void			zero(t_cub3d *cub);
void			last_line(t_cub3d *cub);
void			spawning(t_cub3d *cub);
void			spawning_ns(t_cub3d *cub);
void			spawning_ew(t_cub3d *cub);
int				character(t_cub3d *cub);
void			moves_up_down(t_cub3d *cub);
void			movesides(t_cub3d *cub);
void			look(t_cub3d *cub);
void			calc(t_cub3d *cub);
void			sidedist(t_cub3d *cub);
void			hit(t_cub3d *cub);
void			wall(t_cub3d *cub);
void			rendering(t_cub3d *cub);
void			wallrendering(t_cub3d *cub);
void			spriteposition(t_cub3d *cub, int x);
void			spritedistance(t_cub3d *cub);
void			spritesort(t_cub3d *cub);
void			sprite(t_cub3d *cub);
void			spriterendering(t_cub3d *cub);
void			sprite_image(t_cub3d *cub);
void			if_sprite(t_cub3d *cub);
void			bmp(t_cub3d *cub, int ac, char **av);
void			bmp_save(t_cub3d *cub);
void			bmp_filling(t_cub3d *cub, t_rgb *fc);
int				line_lenth(t_cub3d *cub, int i);
void			minimap(t_cub3d *cub);
void			create_mini(t_cub3d *cub);
void			resize_map(t_cub3d *cub);
void			create_pixel(t_cub3d *cub, int x, int y, t_scale scale);

#endif
