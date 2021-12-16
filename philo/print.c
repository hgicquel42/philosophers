/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:04:31 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/16 18:02:10 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	print(t_state *s, int i, char *msg)
{
	long	time;

	if (pthread_mutex_lock(&s->print))
		return (0);
	if (!ft_time(&time))
		return (0);
	if (printf("%ld %d %s\n", time, i + 1, msg) < 0)
		return (0);
	if (pthread_mutex_unlock(&s->print))
		return (0);
	return (1);
}
