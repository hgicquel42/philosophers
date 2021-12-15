/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:52:33 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/15 15:19:31 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	run(t_philo *d)
{
	t_state	*s;
	int		i;
	t_mutex	*l;
	t_mutex	*r;

	s = d->state;
	i = d->index;
	l = getfork(s, i);
	r = getfork(s, i + 1);
	pthread_mutex_lock(l);
	pthread_mutex_lock(r);
	
}

void	thread(void *p)
{
	run(p);
}

bool	spawn(t_state *s, t_philo *a, int i)
{
	a[i].index = i;
	a[i].state = s;
	if (pthread_create(&(a[i].thread), NULL, thread, a + i))
		return (0);
	return (1);
}

bool	threads(t_state *s)
{
	t_philo	*a;
	int		i;

	a = malloc(s->params.count * sizeof(t_philo));
	if (!a)
		return (0);
	i = -1;
	while (++i < s->params.count)
		if (!spawn(s, a, i++))
			return (free0(a));
	s->philos = a;
	return (1);
}
