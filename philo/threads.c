/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:52:33 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/15 17:40:47 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	run(t_philo *d)
{
	t_state	*s;
	int		i;
	int		n;

	s = d->state;
	i = d->index;
	n = 0;
	while (n < s->params.maxeat)
	{
		if (!print(s, i, "is thinking"))
			return (0);
		if (!lock(s, i + (i == 0)))
			return (0);
		if (!lock(s, i + (i != 0)))
			return (0);
		if (!print(s, i, "is eating"))
			return (0);
		usleep(s->params.tteat * 1000);
		if (!unlock(s, i) || !unlock(s, i + 1))
			return (0);
		if (!print(s, i, "is sleeping"))
			return (0);
		usleep(s->params.ttsleep * 1000);
	}
	return (1);
}

void	*thread(void *p)
{
	if (!run(p))
		printf("An error occured in a thread\n");
	return (0);
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
