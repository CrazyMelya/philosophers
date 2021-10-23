/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:06:33 by cliza             #+#    #+#             */
/*   Updated: 2021/10/23 19:03:45 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*checker(void *arg)
{
	t_data	*data;

	data = arg;
	while (1)
	{
		if (get_ms(data->ph[data->id].eat) > data->time_to_die
			&& ((data->cycle && data->cycle != data->ph[data->id].cycle)
				|| !data->cycle))
		{
			sem_wait(data->write);
			printf("%-6lld %d is dead\n", get_ms(data->start), data->id + 1);
			break ;
		}
	}
	exit(1);
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
