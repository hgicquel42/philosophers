/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:01:22 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/16 18:27:20 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	printdeath(t_state *s, int i, long t)
{
	if (pthread_mutex_lock(&s->print))
		return (0);
	if (printf("%ld %d %s\n", t, i + 1, "died !!!!!!!!!!!!!") < 0)
		return (0);
	if (pthread_mutex_lock(&s->ending))
		return (0);
	s->ended = 1;
	if (pthread_mutex_unlock(&s->ending))
		return (0);
	return (1);
}

bool	monitor(t_philo *d)
{
	long	t;

	while (ft_time(&t))
	{
		if (pthread_mutex_lock(&s->philos[i].eating))
			return (0);
		if (t - s->philos[i].teated > s->params.ttdie)
			return (printdeath(s, i, t));
		if (pthread_mutex_unlock(&s->philos[i].eating))
			return (0);
	}
	return (0);
}

void	*runmonitor(void *p)
{
	if (!monitor(p))
		printf("An error occured in a thread\n");
	return (0);
}

