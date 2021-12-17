/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:52:33 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/17 10:08:29 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	spawn(t_state *s, t_philo *a, int i)
{
	a[i].index = i;
	a[i].state = s;
	if (pthread_mutex_init(&a[i].eating, NULL))
		return (0);
	if (pthread_create(&a[i].life, NULL, runlife, a + i))
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
