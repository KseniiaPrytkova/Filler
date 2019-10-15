/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/15 21:17:59 by kprytkov         ###   ########.fr       */
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

void		piece_cleaner(t_init *initial, char **piece)
{
	int	i;

	i = 0;
	while (i < initial->y_piece && piece[i])
	{
		free(piece[i]);
		i++;
	}
	free(piece);
}

int			init(t_init **initial)
{
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
	return (1);
}

int			run_game(t_init *initial, int n, char board[][n], char **piece)
{
	if (!read_the_map(initial, n, board))
		return (0);
	read_the_piece(&initial, &piece);
	create_hot_board(initial, n, board);
	piece_get_placement(initial, piece, n, board);
	return (1);
}

int			main(void)
{
	t_init	*initial;
	char	**piece;
	char	board[initial->x_plateau][initial->y_plateau];

	initial = NULL;
	piece = NULL;
	if (!init(&initial))
	{
		return (1);
	}
	while (1)
	{
		if (!run_game(initial, initial->y_plateau, board, piece))
			break ;
	}
	if (piece != NULL)
		piece_cleaner(initial, piece);
	free(initial);
	return (0);
}
