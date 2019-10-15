/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/15 21:29:16 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

# define TRUE 1
# define FALSE 0
# define MAX_INT_LEN 10
# define POINTS_INF 999999
# define GRAV_FACTOR_X 2
# define GRAV_FACTOR_Y 2

void				perror(char const *s);
typedef struct		s_init
{
	char			figure;
	char			enemy_figure;
	/* save size of the board */
	int				x_plateau;
	int				y_plateau;
	/* save size of the piece */
	int				x_piece;
	int				y_piece;
	/* coordinates of the opponenent, correspomding to which i build a heat map */
	int				opp_x_curr;
	int				opp_y_curr;
	int				opp_x_next;
	int				opp_y_next;
	/* helpers for the process of generating heat map */
	int				is_one_piece;
	int				i_was;
	/* preliminary coordinates, which is closest to the enemy */
	int				is_first_iteration;
	int				preliminary_x;
	int				preliminary_y;
	/* answer */
	int				definitive_x;
	int				definitive_y;
	int				temp_x;
	int				temp_y;
	int				temp_x_2;
	int				temp_y_2;
	int				temp_x_3;
	int				temp_y_3;
	int				temp_x_4;
	int				temp_y_4;
	int				temp_x_5;
	int				temp_y_5;
	/* Hotmap: store the distribution of player points. */
	int				player_points_nm;
	int				player_points_x;
	int				player_points_y;
}					t_init;

void				get_player_nb(t_init *initial);
void				get_arr_dim(t_init *initial);
int					read_the_map(t_init *initial, int n, char board[][n]);
void				read_the_piece(t_init **initial, char ***piece);
void				create_hot_board(t_init *initial, int n, char board[][n]);
void				piece_get_placement(t_init *initial, char **piece, int n, char board[][n]);
int					piece_calc_points(t_init *initial, char **piece, int n, char board[][n]);
int					placement_alg(t_init *initial, char **piece, int n, char board[][n]);
int					count_delta_x(t_init *initial, int delta_x, int j);
int					count_delta_y(t_init *initial, int delta_y, int i);
void				catch_next(t_init *initial, int i, int j, int n, char board[][n]);
void				take_care_of_yourself(t_init *initial, int i, int j);

#endif
