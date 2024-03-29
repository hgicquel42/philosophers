/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:04:31 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/17 10:54:19 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	print(t_state *s, int i, char *msg)
{
	long	t;
	bool	e;

	if (pthread_mutex_lock(&s->print))
		return (0);
	if (!getended(s, &e) || e)
	{
		if (pthread_mutex_unlock(&s->print))
			return (0);
		return (e);
	}
	if (!ft_time(&t))
		return (0);
	if (printf("%ld %d %s\n", t, i + 1, msg) < 0)
		return (0);
	if (pthread_mutex_unlock(&s->print))
		return (0);
	return (1);
}
