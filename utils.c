/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 11:56:49 by fhyman            #+#    #+#             */
/*   Updated: 2021/07/26 20:43:56 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int	destroy_mutex(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->arg.num_of_ph)
	{
		pthread_mutex_destroy(&(all->mtx.mutex[i]));
		i++;
	}
	if (all->philo_dead)
		pthread_mutex_unlock(&(all->mtx.talk));
	pthread_mutex_destroy(&(all->mtx.talk));
	free(all->philo);
	free(all->mtx.mutex);
	return (0);
}

void	init_args(t_arg *arg)
{
	arg->num_of_ph = 0;
	arg->time_to_eat = 0;
	arg->time_to_sleep = 0;
	arg->time_to_die = 0;
	arg->num_of_ph_eat = -2;
}

int	error_inval_args(char *err)
{
	printf("%s\n", err);
	return (-1);
}
