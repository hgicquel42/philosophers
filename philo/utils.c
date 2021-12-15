/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:33:00 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/15 17:40:22 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_atoui(char *s)
{
	int	x;

	while (*s >= '0' && *s <= '9')
		x = (x * 10) + (*s++ - '0');
	return (x);
}

long	ft_atoul(char *s)
{
	long	x;

	while (*s >= '0' && *s <= '9')
		x = (x * 10) + (*s++ - '0');
	return (x);
}

int	free0(void *p)
{
	free(p);
	return (0);
}
