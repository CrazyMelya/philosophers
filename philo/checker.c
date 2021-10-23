/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:06:33 by cliza             #+#    #+#             */
/*   Updated: 2021/10/23 18:53:02 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*checker(void *arg)
{
	t_data	*data;
	int		i;

	data = arg;
	while (1)
	{
		i = 0;
		while (i < data->num)
		{
			if (get_ms(data->ph[i].eat) > data->time_to_die
				&& ((data->cycle && data->cycle != data->ph[i].cycle)
					|| !data->cycle))
			{
				pthread_mutex_lock(&data->death);
				printf("%-6lld %d is dead\n", get_ms(data->start), i + 1);
				return (0);
			}
			if (check_stomacks(data))
				return (0);
			i++;
		}
	}
}

int	check_stomacks(t_data *data)
{
	int	i;

	i = 0;
	if (data->cycle)
	{
		while (i < data->num)
		{
			if (data->ph[i].cycle != data->cycle)
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

long long	get_ms(struct timeval old)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	new.tv_sec -= old.tv_sec;
	new.tv_usec -= old.tv_usec;
	if (new.tv_usec < 0)
	{
		--new.tv_sec;
		new.tv_usec += 1000000;
	}
	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

void	usleeper(long time, struct timeval now)
{
	long long	cur_time;

	cur_time = get_ms(now);
	while (get_ms(now) < cur_time + time)
		usleep(500);
}
