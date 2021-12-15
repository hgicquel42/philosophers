/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:08:58 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/15 15:19:02 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_mutex	*getfork(t_state *s, int i)
{
	return (s->forks + (i % s->params.count));
}

bool	forks(t_state *s)
{
	t_mutex	*a;
	int		i;

	a = malloc(s->params.count * sizeof(t_mutex));
	if (!a)
		return (0);
	i = -1;
	while (++i < s->params.count)
		if (!pthread_mutex_init(a + i++, NULL))
			return (free0(a));
	s->forks = a;
	return (1);
}
