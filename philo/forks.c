/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:08:58 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/16 11:54:49 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_mutex	*getfork(t_state *s, int i)
{
	return (s->forks + (i % s->params.count));
}

bool	lock(t_state *s, int i)
{
	if (pthread_mutex_lock(getfork(s, i)))
		return (0);
	if (!print(s, i, "has taken a fork"))
		return (0);
	return (1);
}

bool	unlock(t_state *s, int i)
{
	if (pthread_mutex_unlock(getfork(s, i)))
		return (0);
	return (1);
}

bool	forks(t_state *s)
{
	t_mutex	*a;
	int		i;

	a = malloc(s->params.count * sizeof(t_mutex));
	if (!a)
		return (0);
	i = 0;
	while (i < s->params.count)
		if (pthread_mutex_init(a + i++, NULL))
			return (free0(a));
	s->forks = a;
	return (1);
}
