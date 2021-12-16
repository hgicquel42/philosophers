/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:21:55 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/16 12:54:44 by hgicquel         ###   ########.fr       */
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

typedef struct s_state	t_state;

typedef pthread_mutex_t	t_mutex;

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
	long		tate;
	t_state		*state;
}	t_philo;

typedef struct s_state
{
	t_params	params;
	t_philo		*philos;
	t_mutex		*forks;
	t_mutex		print;
	t_mutex		full;
	int			nfull;
	pthread_t	fullt;
	pthread_t	deatht;
	bool		ended;
}	t_state;

int		ft_atoui(char *s);

long	ft_atoul(char *s);

bool	forks(t_state *s);

bool	lock(t_state *s, int i);

bool	unlock(t_state *s, int i);

bool	threads(t_state *s);

bool	gettime(long *r);

bool	print(t_state *s, int i, char *msg);

bool	incfull(t_state *s);

bool	getfull(t_state *s, int *r);

bool	allfull(t_state *s);

void	*runcheckfull(void *p);

void	*runcheckdeath(void *p);

int		free0(void *p);

#endif