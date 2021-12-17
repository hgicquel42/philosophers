/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:07:55 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/17 12:03:44 by hgicquel         ###   ########.fr       */
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

bool	life1(t_state *s, int i)
{
	bool	e;

	if (!print(s, i, "is thinking"))
		return (0);
	if (!lock(s, i, i))
		return (0);
	while (getended(s, &e) && !e)
		usleep(s->params.tteat);
	if (!unlock(s, i, i))
		return (0);
	return (e);
}

bool	life2(t_philo *d, t_state *s, int i, int *n)
{
	if (!print(s, i, "is thinking"))
		return (0);
	if (!lock(s, i, i + (i == 0)) || !lock(s, i, i + (i != 0)))
		return (0);
	if (!print(s, i, "is eating") || !ft_sleep(s->params.tteat) || !eat(d))
		return (0);
	if (!unlock(s, i, i + (i == 0)) || !unlock(s, i, i + (i != 0)))
		return (0);
	if ((*n)++ == s->params.maxeat && !incfull(s))
		return (0);
	if (!print(s, i, "is sleeping") || !ft_sleep(s->params.ttsleep))
		return (0);
	return (1);
}

bool	life(t_philo *d)
{
	t_state	*s;
	int		i;
	int		n;
	bool	e;

	s = d->state;
	i = d->index;
	n = 0;
	if (i % 2 == 0 && !ft_sleep(s->params.tteat))
		return (0);
	if (pthread_create(&d->monitor, NULL, runmonitor, d))
		return (0);
	if (s->params.count == 1)
		return (life1(s, i));
	while (getended(s, &e) && !e)
		if (!life2(d, s, i, &n))
			return (0);
	return (e);
}

void	*runlife(void *p)
{
	if (!life(p))
		printf("An error occured in a thread\n");
	return (0);
}
