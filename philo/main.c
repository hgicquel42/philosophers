/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:21:25 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/15 18:13:47 by hgicquel         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_state	s;
	int		n;

	if (argc < 4)
		return (1);
	if (argc > 6)
		return (1);
	if (pthread_mutex_init(&s.print, NULL))
		return (1);
	if (pthread_mutex_init(&s.full, NULL))
		return (1);
	s.nfull = 0;
	if (!parse(argc, argv, &s))
		return (1);
	if (!forks(&s))
		return (1);
	if (!threads(&s))
		return (1);
	n = 0;
	while (n < s.params.count)
		if (!getfull(&s, &n))
			return (1);
	printf("All philosophers have eaten\n");
	return (0);
}
