/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:21:55 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/17 14:48:09 by hgicquel         ###   ########.fr       */
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
	t_state		*state;
	int			index;
	pthread_t	life;
	t_mutex		eating;
	long		teated;
}	t_philo;

typedef struct s_state
{
	t_params	params;
	t_mutex		*forks;
	t_philo		*philos;
	t_mutex		print;
	t_mutex		full;
	int			nfull;
	pthread_t	fullt;
	pthread_t	deatht;
	t_mutex		ending;
	bool		ended;
}	t_state;

int		ft_atoui(char *s);

long	ft_atoul(char *s);

bool	ft_time(long *r);

bool	ft_sleep(long n);

bool	forks(t_state *s);

bool	lock(t_state *s, int i, int j);

bool	unlock(t_state *s, int i, int j);

bool	threads(t_state *s);

bool	print(t_state *s, int i, char *msg);

bool	getended(t_state *s, bool *r);

bool	incfull(t_state *s);

bool	getfull(t_state *s, int *r);

bool	allfull(t_state *s);

void	*runcheckfull(void *p);

void	*runmonitor(void *p);

void	*runlife(void *p);

bool	eat(t_philo *d);

int		free0(void *p);

#endif