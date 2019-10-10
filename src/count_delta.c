#include "filler.h"

//static int count_delta_x(t_init *initial, int delta_x, int j)
int count_delta_x(t_init *initial, int delta_x, int j)
{
	if ((delta_x = j - initial->opp_x_curr) < 0)
		delta_x *= -1;

	return (delta_x);
}

//static int count_delta_y(t_init *initial, int delta_y, int i)
int count_delta_y(t_init *initial, int delta_y, int i)
{
	if ((delta_y = i - initial->opp_y_curr) < 0)
		delta_y *= -1;

	return (delta_y);
}