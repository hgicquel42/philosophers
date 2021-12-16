/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:52:33 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/16 15:49:10 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	smart_sleep(long n)
{
	long	start;
	long	current;

	if (!gettime(&start))
		return (0);
	while (gettime(&current))
		if (current - start > n)
			return (1);
		else
			usleep(1000);
	return (0);
}

bool	run(t_philo *d)
{
	t_state	*s;
	int		i;
	int		n;

	s = d->state;
	i = d->index;
	n = 0;
	while (1)
	{
		if (!print(s, i, "is thinking"))
			return (0);
		if (!lock(s, i, i + (i == 0)))
			return (0);
		if (!lock(s, i, i + (i != 0)))
			return (0);
		if (!print(s, i, "is eating"))
			return (0);
		smart_sleep(s->params.tteat);
		if (pthread_mutex_lock(&d->eating))
			return (0);
		if (!gettime(&d->teated))
			return (0);
		if (pthread_mutex_unlock(&d->eating))
			return (0);
		if (n++ == s->params.maxeat && !incfull(s))
			return (0);
		if (!unlock(s, i, i) || !unlock(s, i, i + 1))
			return (0);
		if (!print(s, i, "is sleeping"))
			return (0);
		smart_sleep(s->params.ttsleep);
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
	if (!gettime(&a[i].teated))
		return (0);
	if (pthread_mutex_init(&a[i].eating, NULL))
		return (0);
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
	i = 0;
	while (i < s->params.count)
		if (!spawn(s, a, i++))
			return (free0(a));
	s->philos = a;
	return (1);
}
