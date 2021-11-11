/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:41:09 by fhyman            #+#    #+#             */
/*   Updated: 2021/07/26 20:42:38 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_struct(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->arg.num_of_ph)
	{
		all->philo[i].i = i + 1;
		all->philo[i].time = get_time();
		all->philo[i].left_fork = &all->mtx.mutex[i];
		all->philo[i].right_fork = \
		&all->mtx.mutex[(i + 1) % all->arg.num_of_ph];
		all->philo[i].mtx.talk = all->mtx.talk;
		all->philo[i].args = all->arg;
		all->philo[i].die = all->die;
		all->philo[i].last_eat = 0;
		all->philo[i].eat_count = 0;
		all->philo[i].eat_philo = 0;
		i++;
	}
}

int	init_all(t_all *all)
{
	all->i = 0;
	all->eat_philo = 0;
	all->philo_dead = 0;
	all->philo = (t_philo *)malloc(sizeof(t_philo) \
	* all->arg.num_of_ph);
	all->mtx.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* all->arg.num_of_ph);
	if (!all->philo || !all->mtx.mutex)
		return (1);
	return (0);
}

int	init_mutex(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->arg.num_of_ph)
	{
		if (pthread_mutex_init(&(all->mtx.mutex[i]), NULL))
			return (error_inval_args("pthread_mutex_init error!"));
		i++;
	}
	if (pthread_mutex_init(&(all->mtx.talk), NULL))
		return (error_inval_args("pthread_mutex_init error!"));
	init_philo_struct(all);
	return (0);
}
