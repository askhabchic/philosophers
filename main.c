/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 22:15:41 by fhyman            #+#    #+#             */
/*   Updated: 2021/07/29 21:16:02 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	mysleep(long time)
{
	long	timing;
	long	cur_time;

	cur_time = get_time();
	timing = cur_time;
	while (time > timing - cur_time)
	{
		timing = get_time();
		usleep(200);
	}
}

int	dead_checker(t_all *all, int i)
{
	long	cur_time;
	int		k;

	k = 0;
	cur_time = get_time() - all->philo[i].time;
	if (cur_time - all->philo[i].last_eat > all->arg.time_to_die)
	{
		pthread_mutex_lock(&(all->philo[i].mtx.talk));
		printf("%li ms %d died!\n", cur_time, all->philo[i].i);
		while (k < all->arg.num_of_ph)
		{
			pthread_detach(all->philo[k].philo);
			k++;
		}
		all->philo_dead = 1;
		return (1);
	}
	return (0);
}

void	*dead(void *arg)
{
	t_all	*all;
	int		i;

	all = (t_all *)arg;
	while (1)
	{
		i = 0;
		while (i < all->arg.num_of_ph)
		{
			if (all->philo[i].eat_count == all->arg.num_of_ph_eat && \
			!all->philo[i].eat_philo)
			{
				all->philo[i].eat_philo = 1;
				all->eat_philo++;
			}
			if (dead_checker(all, i))
				return (0);
			i++;
		}
		if (all->eat_philo == all->arg.num_of_ph)
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_all		all;
	int			i;

	i = 0;
	if ((argc != 5 && argc != 6) || pars_args(&all.arg, argc, argv))
		return (error_inval_args("Invalid arguments!"));
	if (init_all(&all) || init_mutex(&all))
		return (error_inval_args(MEM));
	pthread_create(&all.dead, NULL, dead, &all);
	if (create_treads(&all))
		return (error_inval_args("Threads not created!"));
	destroy_mutex(&all);
	return (0);
}
