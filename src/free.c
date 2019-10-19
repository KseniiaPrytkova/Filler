/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <kprytkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:58 by kprytkov          #+#    #+#             */
/*   Updated: 2019/10/19 20:55:26 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

void		board_cleaner(t_init *initial)
{
	int	i;

	i = 0;
	while (i < initial->y_plateau)
	{
		free(initial->board[i]);
		i++;
	}
	free(initial->board);
}
