#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDHT 1280
# define WIN_HEIGHT 960
# define NO 0
# define SO 1
# define WE 2
# define EA 3

# include "../mlx/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_file
{
	char	**file;
	int		file_lines;
	char	**textures;
	char	**colors;
	int		ceiling[3];
	int		floor[3];
	char	**map;
	char	**map_temp;
	int		height;
	int		widht;
} t_file;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
} t_mlx;

typedef struct s_all
{
	t_file *file;
	t_mlx *mlx;
} t_all;

// main
int	init_elements(t_file *file);
void	init_mlx(t_mlx *mlx);
void	render_game(t_mlx *mlx, t_file *file);
void	set_hook(t_mlx *mlx, t_file *file);
int	exit_hook(t_mlx *mlx);
int	key_press_hook(int key, t_mlx *mlx, t_file *file);

//Error

int		check_argc(int argc);
int		check_path(char *path);
int		check_elements(t_file *file);
int		check_empty_file(t_file *file, char *path, int fd);

// Utils
int		ft_isdigit(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *s);
char	*ft_strnstr(char *s1, char *s2, int n);
int	ft_atoi(const char *str);
char	*cpy_no_endl(char *s1);
int	count_mat_size(char **mat);
char	*ft_strdup(char *s);
char	*strdup_mod(char *s, int n);
void	print_mat(char **mat);

char	**ft_split(char *s, char c);

void	get_free(char **mat);
void	free_all(t_file *file);

char	*get_next_line(int fd);

// Read file

int		count_file_lines(char *path);
void	remove_file_endl(t_file *file);
int		read_file(char *path, t_file *file);

// textures

int		get_textures(t_file *file);
int		is_texture(char *str);
int		check_textures(char **mat);
int		split_textures(t_file *file);

// colors

int		get_colors(t_file *file);
int		is_colors(char *str);
int		check_colors(char **mat);
int		split_colors(t_file *file);
int	validate_colors(t_file *file);
int	set_colors(char *str, t_file *file, int type);
int	check_is_digit(char **mat);
int	check_numbers(int *number);

// map

int	is_element(char *str);
void	get_map(t_file *file);
void	remap(t_file *file);

// map_temp
void	set_map_temp(t_file *file);
void	init_map(t_file *file, char **map);
void	cpy_map_to_temp(t_file *file);


// validate map
int validate_map(t_file *file);
int	count_map_width(char **mat);
int	check_player(t_file *file);
int	check_spaces(t_file *file);
int	check_around_spaces(char **map, int i, int j);
int	check_around_player(char **map, int i, int j);

#endif
