/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hot_map_catch_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/15 21:14:58 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		catch_next_handle(t_init *initial, int i, int *j)
{
	if ((initial->board[*j][i] == initial->enemy_figure) ||
		(initial->board[*j][i] == initial->enemy_figure - 32))
	{
		initial->opp_x_next = *j;
		initial->opp_y_next = i;
		initial->is_one_piece = -1;
		return (0);
	}
	(*j)++;
	return (1);
}

void	catch_next_final(t_init *initial)
{
	if (initial->is_one_piece == -1)
		initial->i_was++;
	else
		initial->is_one_piece = TRUE;
}

void	catch_next(t_init *initial, int i, int j)
{
	int	temp_i;
	int	temp_j;
	int	first;

	temp_i = i;
	temp_j = j + 1;
	first = 0;
	initial->is_one_piece = FALSE;
	while (temp_i < initial->y_plateau)
	{
		temp_j = 0 ? first : temp_j;
		while (temp_j < initial->x_plateau)
		{
			first = 1;
			if (!catch_next_handle(initial, temp_i, &temp_j))
				break ;
		}
		if (initial->is_one_piece == -1)
			break ;
		temp_i++;
	}
	catch_next_final(initial);
}
