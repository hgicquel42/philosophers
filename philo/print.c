/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:04:31 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/15 15:23:16 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	time(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000);
}

void	print(t_state *s, char *msg)
{
	
}
