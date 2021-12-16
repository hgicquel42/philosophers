/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:03:21 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/16 12:57:02 by hgicquel         ###   ########.fr       */
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
	if (pthread_mutex_lock(&s->print))
		return (0);
	if (printf("All philosophers are full\n") < 0)
		return (0);
	s->ended = 1;
	return (1);
}

bool	checkfull(t_state *s)
{
	int	n;

	n = 0;
	while (getfull(s, &n))
		if (n == s->params.count)
			return (allfull(s));
	return (1);
}

void	*runcheckfull(void *p)
{
	if (!checkfull(p))
		printf("An error occured in a thread\n");
	return (0);
}
