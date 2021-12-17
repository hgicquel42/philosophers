/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:33:00 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/17 15:08:29 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_atoui(char *s)
{
	int	x;

	x = 0;
	while (*s >= '0' && *s <= '9')
		x = (x * 10) + (*s++ - '0');
	return (x);
}

long	ft_atoul(char *s)
{
	long	x;

	x = 0;
	while (*s >= '0' && *s <= '9')
		x = (x * 10) + (*s++ - '0');
	return (x);
}

bool	ft_time(long *r)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	*r = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (1);
}

bool	ft_sleep(long n)
{
	long	start;
	long	current;

	if (!ft_time(&start))
		return (0);
	while (ft_time(&current))
	{
		if (current - start >= n)
			return (1);
		usleep(50);
	}
	return (0);
}

int	free0(void *p)
{
	free(p);
	return (0);
}
