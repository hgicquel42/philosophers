/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:03:21 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/15 18:26:28 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	incfull(t_state *s)
{
	if (pthread_mutex_lock(&s->full))
		return (0);
	s->nfull++;
	print(s, 999, "incfull");
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
