/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:05:08 by rwallier          #+#    #+#             */
/*   Updated: 2022/10/17 09:06:15 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(t_args *args, const char **argv, int argc)
{
	int	index;

	args->time_to_die = argc - 3;
	args->time_to_eat = argc - 2;
	args->time_to_sleep = argc - 1;
	args->forks = malloc(ft_atoi(argv[argc - 4]) * sizeof(int));
	index = 0;
	while (index < ft_atoi(argv[argc - 4]))
	{
		args->forks[index] = 0;
		index++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long int	res;
	int			i;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '+')
	{
		if (sign == -1)
			return (0);
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (sign * res);
}

