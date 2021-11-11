/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:53:43 by fhyman            #+#    #+#             */
/*   Updated: 2021/07/26 20:43:47 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		str++;
	if (str[res] == '-' || str[res] == '+')
	{
		if (str[res] == '-')
			sign = -1;
		str++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - '0';
		str++;
	}
	return (res * sign);
}

int	check_args(char *arg)
{
	int	i_arg;

	i_arg = ft_atoi(arg);
	if (i_arg <= 0)
		return (-1);
	return (i_arg);
}

int	fill_args(int argc, char **argv, t_arg *arg)
{
	arg->num_of_ph = check_args(argv[1]);
	arg->time_to_die = check_args(argv[2]);
	arg->time_to_eat = check_args(argv[3]);
	arg->time_to_sleep = check_args(argv[4]);
	if (argv[5])
		arg->num_of_ph_eat
			= check_args(argv[5]);
	if (arg->num_of_ph == -1 || arg->time_to_eat == -1
		|| arg->time_to_sleep == -1 || arg->time_to_die == -1
		|| (argv[5] && arg->num_of_ph_eat
			== -1))
		return (1);
	return (0);
}

int	check_arg_val(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		else
			i++;
	}
	return (0);
}

int	pars_args(t_arg *arg, int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	num = argc;
	init_args(arg);
	while (num > 0)
	{
		while (argv[i])
		{
			if (check_arg_val(argv[i]))
				return (1);
			else
				i++;
		}
		num--;
	}
	if (fill_args(argc, argv, arg))
		return (1);
	return (0);
}
