/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:21:25 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/15 12:55:29 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef struct s_state
{
	t_params	p;
	t_philo		*a;
}	t_state;


bool	parse(int argc, char **argv, t_state *s)
{
	int	t;

	s->p.count = ft_atoui(argv[1]);
	s->p.ttdie = ft_atoul(argv[2]);
	s->p.tteat = ft_atoul(argv[3]);
	s->p.ttsleep = ft_atoul(argv[4]);
	if (argc == 5)
		s->p.maxeat = ft_atoui(argv[5]);
	else
		s->p.maxeat = -1;
	return (1);
}

void	run(t_philo *d)
{
	
}

void	thread(void *p)
{
	run(p);
}

bool	spawn(t_state *s, t_philo *d)
{
	pthread_create(&(a[i].thread), NULL, thread, a + i);
}

bool	threads(t_state *s)
{
	t_philo	*a;
	int		i;

	a = malloc(s->p.count * sizeof(t_philo));
	if (!a)
		return (0);
	i = -1;
	while (++i < s->p.count)
		if (pthread_create(&(a[i].thread), NULL, thread, a + i))
			return (free0(a));
	s->a = a;
	return (1);
}

int	main(int argc, char **argv)
{
	t_state	s;

	if (argc < 4)
		return (1);
	if (argc > 5)
		return (1);
	if (!parse(argc, argv, &p))
		return (1);
	if (!threads(&p))
		return (1);
	return (0);
}
