/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/19 21:05:57 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdint.h>
#include <inttypes.h>

static void	init_structure(t_init *initial)
{
	initial->x_plateau = 0;
	initial->y_plateau = 0;
	initial->is_one_piece = -1;
	initial->i_was = 0;
	initial->opp_x_next = 0;
	initial->opp_y_next = 0;
	initial->preliminary_x = 0;
	initial->preliminary_y = 0;
	initial->definitive_x = 0;
	initial->definitive_y = 0;
	initial->is_first_iteration = TRUE;
}

int			init(t_init **initial)
{
	int i;

	i = 0;
	if (!((*initial) = (t_init *)malloc(sizeof(t_init))))
	{
		perror("Error: bad malloc (structure)");
		return (0);
	}
	init_structure(*initial);
	get_player_nb(*initial);
	if ((*initial)->figure == 'o')
		(*initial)->enemy_figure = 'x';
	else if ((*initial)->figure == 'x')
		(*initial)->enemy_figure = 'o';
	get_arr_dim(*initial);
	(*initial)->board = NULL;
	(*initial)->board = (char**)malloc((*initial)->x_plateau * sizeof(char*));
	i = -1;
	while (++i < (*initial)->x_plateau)
	{
		(*initial)->board[i] = (char*)malloc(
				(*initial)->y_plateau * sizeof(char));
	}
	return (1);
}

int			run_game(t_init *initial, char **piece)
{
	if (!read_the_map(initial))
		return (0);
	read_the_piece(&initial, &piece);
	create_hot_board(initial);
	piece_get_placement(initial, piece);
	/* print the coordinates to filler_vm */
	fprintf(stdout, "%d %d\n", initial->definitive_y, initial->definitive_x);
	fflush(stdout);
	return (1);
}

int			main(void)
{
	t_init	*initial;
	char	**piece;

	initial = NULL;
	piece = NULL;
	if (!init(&initial))
	{
		return (1);
	}
	while (1)
	{
		if (!run_game(initial, piece))
			break ;
	}
	if (piece != NULL)
		piece_cleaner(initial, piece);
	board_cleaner(initial);
	free(initial);
	return (0);
}
