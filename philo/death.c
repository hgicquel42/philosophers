/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:01:22 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/16 15:46:37 by hgicquel         ###   ########.fr       */
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

bool	checkdeath(t_state *s)
{
	int		i;
	long	t;

	while (1)
	{
		i = -1;
		while (++i < s->params.count)
		{
			if (!gettime(&t))
				return (1);
			if (pthread_mutex_lock(&s->philos[i].eating))
				return (1);
			if (t - s->philos[i].teated > s->params.ttdie)
				return (printdeath(s, i, t));
			if (pthread_mutex_unlock(&s->philos[i].eating))
				return (1);
		}
	}
	return (1);
}

void	*runcheckdeath(void *p)
{
	if (!checkdeath(p))
		printf("An error occured in a thread\n");
	return (0);
}
