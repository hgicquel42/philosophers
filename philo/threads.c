/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:52:33 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/16 19:27:47 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	eat(t_philo *d)
{
	if (pthread_mutex_lock(&d->eating))
		return (0);
	if (!ft_time(&d->teated))
		return (0);
	if (pthread_mutex_unlock(&d->eating))
		return (0);
	return (1);
}

bool	life(t_philo *d)
{
	t_state	*s;
	int		i;
	int		n;

	s = d->state;
	i = d->index;
	n = 0;
	if (i % 2 && !ft_sleep(s->params.tteat))
		return (0);
	while (1)
	{
		if (!print(s, i, "is thinking"))
			return (0);
		if (!lock(s, i, i + (i == 0)) || !lock(s, i, i + (i != 0)))
			return (0);
		if (!print(s, i, "is eating") || !ft_sleep(s->params.tteat) || !eat(d))
			return (0);
		if (!unlock(s, i, i + (i == 0)) || !unlock(s, i, i + (i != 0)))
			return (0);
		if (n++ == s->params.maxeat && !incfull(s))
			return (0);
		if (!print(s, i, "is sleeping") || !ft_sleep(s->params.ttsleep))
			return (0);
	}
	return (1);
}

void	*runlife(void *p)
{
	if (!life(p))
		printf("An error occured in a thread\n");
	return (0);
}

bool	spawn(t_state *s, t_philo *a, int i)
{
	a[i].index = i;
	a[i].state = s;
	if (pthread_mutex_init(&a[i].eating, NULL))
		return (0);
	if (pthread_create(&a[i].life, NULL, runlife, a + i))
		return (0);
	if (pthread_create(&a[i].monitor, NULL, runmonitor, a + i))
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
