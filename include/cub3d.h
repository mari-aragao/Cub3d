/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:01:48 by maragao           #+#    #+#             */
/*   Updated: 2023/08/03 17:21:40 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 1
# define WIN_WIDTH 1280
# define WIN_HEIGHT 960
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define PI 3.141592653
# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_img
{
	int		height;
	int		width;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
}				t_img;

typedef struct s_file
{
	char	**file;
	int		file_lines;
	char	**textures;
	t_img	img_txt[4];
	char	**colors;
	int		ceiling[3];
	int		floor[3];
	int		dec_ceiling;
	int		dec_floor;
	char	**map;
	char	**map_temp;
	int		height;
	int		width;
}				t_file;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
}				t_mlx;

typedef struct s_rayc
{
	int		x;
	int		y;
	double	pos_x;	
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	olddir_x;
	double	olddir_y;
	double	oldplane_x;
	double	oldplane_y;
	double	cam_x;	
	double	raydir_x;
	double	raydir_y;
	int		map_x;	
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_wall_dist;
	int		step_x;	
	int		step_y;
	int		hit;
	int		side;
	double	move_speed;
	double	rot_speed;
	t_img	*texture;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	int		pitch;
	double	step;
}				t_rayc;

typedef struct s_draw
{
	double			x;
	int				height;	
	int				y_start;
	int				y_end;
	unsigned int	color;

}				t_draw;

typedef struct s_all
{
	t_mlx	*mlx;
	t_file	*file;
	t_rayc	*rc;
}				t_all;

// mlx_functions
int				init_elements(t_file *file);
void			init_mlx(t_mlx *mlx);
void			init_image(t_mlx *mlx);
int				exit_hook(t_all *all);
int				is_wall(t_file *file, int x, int y);
int				key_hook(int key, void *param);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void			my_mlx_get_addr(t_img *img);

//Error

int				start_validation(int argc, char **argv, t_file *file);
int				check_argc(int argc);
int				check_path(char *path);
int				check_elements(t_file *file);
int				check_empty_file(t_file *file, char *path, int fd);

// Utils
int				ft_isdigit(int c);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlen(char *s);
char			*ft_strnstr(char *s1, char *s2, int n);
int				ft_atoi(const char *str);
char			*cpy_no_endl(char *s1);
int				count_mat_size(char **mat);
char			*ft_strdup(char *s);
char			*strdup_mod(char *s, int n);
void			print_mat(char **mat);
char			**ft_split(char *s, char c);
void			get_free(char **mat);
void			free_all(t_file *file);
char			*get_next_line(int fd);
int				ft_strchr_mod(char *s);
char			*ft_strjoin(char *s1, char *s2);
void			calculate_decimal_color(t_file *file);
char			*decimal_to_hexa(int *decimal);
int				hexa_to_decimal(char *hexa);

// Read file

int				count_file_lines(char *path);
void			remove_file_endl(t_file *file);
int				read_file(char *path, t_file *file);

// textures
int				get_textures(t_file *file);
int				is_texture(char *str);
int				check_textures(char **mat);
int				split_textures(t_file *file);
int				is_xpm_file(char *path);
int				set_xpm_img(t_file *file, t_mlx *mlx);
unsigned int	get_pixel_texture(t_img *img, int x, int y);
void			texture_calc(t_rayc *rc, t_draw *wall);

// colors
int				get_colors(t_file *file);
int				is_colors(char *str);
int				check_colors(char **mat);
int				split_colors(t_file *file);
int				validate_colors(t_file *file);
int				set_colors(char *str, t_file *file, int type);
int				check_is_digit(char **mat);
int				check_numbers(int *number);
int				check_comma(char *str);

// map
int				is_element(char *str);
void			get_map(t_file *file);

// map_temp
void			set_map_temp(t_file *file);
void			init_map(t_file *file, char **map);
void			cpy_map_to_temp(t_file *file);

// validate map
int				validate_map(t_file *file);
int				count_map_width(char **mat);
int				is_valid_char(char c);
int				check_player(t_file *file);
int				check_spaces(t_file *file);
int				check_around_spaces(char **map, int i, int j);
int				check_around_player(char **map, int i, int j);

//raycasting
void			raycasting(t_file *file, t_mlx *mlx, t_rayc *rc);
void			render_game(t_mlx *mlx, t_file *file, t_rayc *rc);
void			draw_wall(t_mlx *mlx, t_draw *wall, t_file *file, t_rayc *rc);
void			init_rc(t_file *file, t_rayc *rc);
void			set_initial_pos(t_file *file, t_rayc *rc);
void			check_direction(t_rayc *rc, char dir, int x, int y);

//move_player
int				is_wall(t_file *file, int x, int y);
void			move_w_and_s(int key, t_file *file, t_rayc *rc);
void			move_a_and_d(int key, t_file *file, t_rayc *rc);
void			rotate_left(int key, t_rayc *rc);
void			rotate_right(int key, t_rayc *rc);
int				move_player(int key, t_file *file, t_rayc *rc, t_mlx *mlx);
void			set_texture(t_rayc *rc, t_file *file);
void			calc_texture_pixel(t_file *file, t_rayc *rc, t_draw *wall);
void			calc_side_dist(t_rayc *rc);
void			dda(t_rayc *rc, t_file *file);

#endif
