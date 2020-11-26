/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:47:27 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/26 10:39:37 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "mlx.h"
# include "../Utils/utils.h"
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
	int		file;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		s;
	int		f;
	int		c;
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
	char	*f;
	char	*c;
}				t_path;

typedef struct	s_parse
{
	int		r;
	char	*line;
	char	**splitted;
	int		x;
	int		y;
	int		spawn;
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

typedef struct	s_life
{
	int		x;
	int		y;
	int		hearts;
	int		row;
	int		len;
	t_scale	scale;
}				t_life;

typedef struct	s_weapon
{
	int		x;
	int		y;
	int		len;
	int		row;
	t_scale	scale;
	int		fire;
}				t_weapon;

typedef struct	s_fire
{
	int		x;
	int		y;
	int		len;
	int		row;
	t_scale	scale;
	int		fire;
}				t_fire;

typedef struct	s_bullet
{
	int		x;
	int		y;
	int		len;
	int		row;
	t_scale	scale;
	int		bullets;
}				t_bullet;

typedef struct	s_bmp
{
	int			pad;
	int			filesize;
	int			fd;
	int			i;
}				t_bmp;

typedef struct	s_fc
{
	double		raydirx0;
	double		raydiry0;
	double		raydirx1;
	double		raydiry1;
	double		posz;
	double		rowdistance;
	double		floorstepx;
	double		floorstepy;
	double		floorx;
	double		floory;
	int			color;
	int			cellx;
	int			celly;
	int			tx;
	int			ty;
	int			p;
	int			exist;
}				t_fc;

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
	char	item;
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
	t_mini		mini;
	t_life		life;
	t_weapon	weapon;
	t_fire		fire;
	t_bullet	bullet;
	t_bmp		bmp;
	t_fd		fd;
	t_img		txt[7];
	t_sprite	*sprite;
	t_fc		fc;

	int			len;
	char		**mini_map;
	char		**heart;
	char		**weapons;
	char		**shot;
	char		**bullets;
	char		*image;
	int			ac;
	int			color;
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
void			ext_error(char *av, char *ext, int *fd);
void			init_mlx(t_cub3d *cub);
void			ft_free(char **arr);
void			checker(char **s, t_cub3d *cub, int i);
void			range(t_rgb *rgb, t_cub3d *cub);
int				key_pressed(int key, t_cub3d *cub);
int				key_released(int key, t_cub3d *cub);
int				key_close(t_cub3d *cub);
void			resolution(t_cub3d *cub);
int				min_res(t_cub3d *cub);
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
int				character(t_cub3d *cub, int x);
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
void			bmp_filling(t_cub3d *cub);
void			bonus(t_cub3d *cub);
void			floor_ceiling(t_cub3d *cub);
void			fc_calc(t_cub3d *cub, int y);
void			fc_txt(t_cub3d *cub, int y);
void			create_pixel(t_cub3d *cub, int x, int y, t_scale scale);
void			minimap(t_cub3d *cub);
int				line_lenth(t_cub3d *cub, int i);
void			create_mini(t_cub3d *cub);
void			resize_map(t_cub3d *cub);
void			minimap_color(t_cub3d *cub, int i, int j);
void			life_bar(t_cub3d *cub);
void			lifebar_color(t_cub3d *cub, int i, int j);
void			create_heart(t_cub3d *cub, int i);
void			render_heart(t_cub3d *cub, int end, int j);
void			weapon(t_cub3d *cub);
void			weapon_color(t_cub3d *cub, int i, int j);
void			create_weapon(t_cub3d *cub, int i);
void			fire(t_cub3d *cub);
void			create_fire(t_cub3d *cub, int i);
void			bullets(t_cub3d *cub);
void			bullet_color(t_cub3d *cub, int i, int j);
void			render_bullet(t_cub3d *cub, int j, int end);
void			create_bullet(t_cub3d *cub, int i);
void			bonus_keys(t_cub3d *cub);

#endif
