/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:01:22 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/17 10:59:41 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	printdeath(t_state *s, int i, long t)
{
	bool	e;

	if (pthread_mutex_lock(&s->print))
		return (0);
	if (!getended(s, &e) || e)
	{
		if (pthread_mutex_unlock(&s->print))
			return (0);
		return (e);
	}
	if (printf("%ld %d %s\n", t, i + 1, "died") < 0)
		return (0);
	if (pthread_mutex_lock(&s->ending))
		return (0);
	s->ended = 1;
	if (pthread_mutex_unlock(&s->ending))
		return (0);
	if (pthread_mutex_unlock(&s->print))
		return (0);
	return (1);
}

bool	monitor(t_philo *d)
{
	t_state	*s;
	long	t;
	bool	e;

	s = d->state;
	if (!eat(d))
		return (0);
	while (getended(s, &e) && !e)
	{
		if (pthread_mutex_lock(&d->eating))
			return (0);
		if (!ft_time(&t))
			return (0);
		if (t - d->teated > s->params.ttdie)
		{
			if (pthread_mutex_unlock(&d->eating))
				return (0);
			return (printdeath(s, d->index, t));
		}
		if (pthread_mutex_unlock(&d->eating))
			return (0);
		usleep(1000);
	}
	return (e);
}

void	*runmonitor(void *p)
{
	if (!monitor(p))
		printf("An error occured in a thread\n");
	return (0);
}
