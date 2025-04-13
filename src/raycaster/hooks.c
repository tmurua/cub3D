/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:55:52 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/13 21:26:51 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"

int	handle_keypress(int keycode, t_data *d)
{
	if (keycode == XK_Escape)
		destroy(d);
	if (keycode == XK_r)
	{
		d->running_speed = 0.0;
		if (d->radio_car == 0)
			d->radio_car = 1;
		else
			d->radio_car = 0;
	}
	if (keycode == XK_a)
		d->move[3] = 1;
	if (keycode == XK_s || keycode == XK_Down)
		d->move[1] = 1;
	if (keycode == XK_d)
		d->move[2] = 1;
	if (keycode == XK_w || keycode == XK_Up)
		d->move[0] = 1;
	if (keycode == XK_Right)
		d->move[4] = 1;
	if (keycode == XK_Left)
		d->move[5] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_data *d)
{
	if (keycode == XK_a)
		d->move[3] = 0;
	if (keycode == XK_s || keycode == XK_Down)
		d->move[1] = 0;
	if (keycode == XK_d)
		d->move[2] = 0;
	if (keycode == XK_w || keycode == XK_Up)
		d->move[0] = 0;
	if (keycode == XK_Right)
		d->move[4] = 0;
	if (keycode == XK_Left)
		d->move[5] = 0;
	return (0);
}
