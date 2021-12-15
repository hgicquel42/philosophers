/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:21:55 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/15 12:26:15 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_params
{
	int		count;
	long	ttdie;
	long	tteat;
	long	ttsleep;
	int		maxeat;
}	t_params;

typedef struct s_philo
{
	int			index;
	pthread_t	thread;
}	t_philo;

#endif