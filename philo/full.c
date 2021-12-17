/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:03:21 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/17 11:32:26 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	incfull(t_state *s)
{
	if (pthread_mutex_lock(&s->full))
		return (0);
	s->nfull++;
	if (pthread_mutex_unlock(&s->full))
		return (0);
	return (1);
}

bool	getfull(t_state *s, int *r)
{
	if (pthread_mutex_lock(&s->full))
		return (0);
	*r = s->nfull;
	if (pthread_mutex_unlock(&s->full))
		return (0);
	return (1);
}

bool	allfull(t_state *s)
{
	bool	e;

	if (pthread_mutex_lock(&s->print))
		return (0);
	if (!getended(s, &e) || e)
	{
		if (pthread_mutex_unlock(&s->print))
			return (0);
		return (e);
	}
	if (printf("All philosophers are full\n") < 0)
		return (0);
	if (pthread_mutex_lock(&s->ending))
		return (0);
	s->ended = 1;
	if (pthread_mutex_unlock(&s->ending))
		return (0);
	if (pthread_mutex_unlock(&s->print))
		return (0);
	return (1);
}

bool	checkfull(t_state *s)
{
	int		n;
	bool	e;

	n = 0;
	while (getfull(s, &n) && getended(s, &e) && !e)
		if (n == s->params.count)
			return (allfull(s));
	return (e);
}

void	*runcheckfull(void *p)
{
	if (!checkfull(p))
		printf("An error occured in a thread\n");
	return (0);
}
