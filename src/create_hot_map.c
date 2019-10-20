/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hot_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/19 21:00:24 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	create_hot_board_handle_players_player(t_init *initial, int i, int j)
{
	initial->board[j][i] = 99;
	if (j == initial->opp_x_curr && i == initial->opp_y_curr &&
		initial->is_one_piece == -1)
		catch_next(initial, i, j);
	if (initial->opp_y_next == initial->opp_y_curr)
	{
		initial->opp_x_curr = initial->opp_x_next;
		initial->opp_y_curr = initial->opp_y_next;
	}
}

void	create_hot_board_handle_players_enemy(t_init *initial, int i, int j)
{
	initial->board[j][i] = -99;
	take_care_of_yourself(initial, i, j);
	initial->player_points_nm++;
	initial->player_points_x += j;
	initial->player_points_y += i;
}

int		create_hot_board_handle_players(t_init *initial, int i, int j)
{
	if ((initial->board[j][i] == initial->enemy_figure) ||
		(initial->board[j][i] == initial->enemy_figure - 32))
	{
		create_hot_board_handle_players_player(initial, i, j);
		return (1);
	}
	else if ((initial->board[j][i] == initial->figure) ||
			(initial->board[j][i] == initial->figure - 32))
	{
		create_hot_board_handle_players_enemy(initial, i, j);
		return (1);
	}
	return (0);
}

void	create_hot_board_handle(t_init *initial, int i, int j)
{
	int	delta_x;
	int	delta_y;

	delta_x = 0;
	delta_y = 0;
	if (!create_hot_board_handle_players(initial, i, j))
	{
		delta_x = count_delta_x(initial, delta_x, j);
		delta_y = count_delta_y(initial, delta_y, i);
		if ((initial->board[j][i] = delta_x + delta_y) < 1)
			initial->board[j][i] *= -1;
	}
}

void	create_hot_board(t_init *initial)
{
	int	i;
	int	j;

	initial->player_points_nm = 0;
	initial->player_points_x = 0;
	initial->player_points_y = 0;
	initial->is_one_piece = -1;
	initial->i_was = 0;
	i = -1;
	while (++i < initial->y_plateau)
	{
		if (initial->i_was > 0)
		{
			initial->opp_x_curr = initial->opp_x_next;
			initial->opp_y_curr = initial->opp_y_next;
		}
		j = -1;
		while (++j < initial->x_plateau)
		{
			create_hot_board_handle(initial, i, j);
		}
	}
}
