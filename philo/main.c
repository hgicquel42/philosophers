/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:21:25 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/17 12:03:14 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	parse(int argc, char **argv, t_state *s)
{
	s->params.count = ft_atoui(argv[1]);
	s->params.ttdie = ft_atoul(argv[2]);
	s->params.tteat = ft_atoul(argv[3]);
	s->params.ttsleep = ft_atoul(argv[4]);
	if (argc == 6)
		s->params.maxeat = ft_atoui(argv[5]);
	else
		s->params.maxeat = -1;
	return (1);
}

bool	getended(t_state *s, bool *r)
{
	if (pthread_mutex_lock(&s->ending))
		return (0);
	*r = s->ended;
	if (pthread_mutex_unlock(&s->ending))
		return (0);
	return (1);
}

bool	loopended(t_state *s)
{
	bool	e;

	while (getended(s, &e) && !e)
		usleep(100);
	return (e);
}

bool	safequit(t_state *s)
{
	int	i;

	printf("Safely quitting\n");
	i = 0;
	while (i < s->params.count)
	{
		if (pthread_join(s->philos[i].life, 0))
			return (0);
		if (pthread_join(s->philos[i].monitor, 0))
			return (0);
		i++;
	}
	i = 0;
	while (i < s->params.count)
		if (pthread_mutex_destroy(&s->forks[i++]))
			return (0);
	if (pthread_join(s->fullt, 0))
		return (0);
	free(s->forks);
	free(s->philos);
	return (1);
}

int	main(int argc, char **argv)
{
	t_state	s;

	if (argc < 5 || argc > 6)
		return (1);
	if (pthread_mutex_init(&s.print, NULL))
		return (safequit(&s) || 1);
	if (pthread_mutex_init(&s.full, NULL))
		return (safequit(&s) || 1);
	if (pthread_mutex_init(&s.ending, NULL))
		return (safequit(&s) || 1);
	s.ended = 0;
	s.nfull = 0;
	if (!parse(argc, argv, &s))
		return (safequit(&s) || 1);
	if (!forks(&s))
		return (safequit(&s) || 1);
	if (!threads(&s))
		return (safequit(&s) || 1);
	if (pthread_create(&s.fullt, NULL, runcheckfull, &s))
		return (safequit(&s) || 1);
	if (!loopended(&s))
		return (safequit(&s) + 1);
	return (safequit(&s));
}
