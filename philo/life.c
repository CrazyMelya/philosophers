/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:41:12 by cliza             #+#    #+#             */
/*   Updated: 2021/10/23 16:03:07 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*life(void	*arg)
{
	t_data			*data;
	int				id;

	data = arg;
	id = data->id;
	data->id++;
	while (1)
	{
		if (id % 2)
		{
			if (data->num % 2)
				usleep(50);
			eating_odd(data, id);
		}
		else
			eating_even(data, id);
		sleeping(data, id);
		if (data->cycle == data->ph[id].cycle)
			break ;
		thinking(data, id);
	}
	return (0);
}

void	eating_odd(t_data *data, int id)
{
	pthread_mutex_lock(data->ph[id].right);
	pthread_mutex_lock(&data->death);
	printf("%-6lld %d has taken a fork\n", get_ms(data->start), id + 1);
	pthread_mutex_unlock(&data->death);
	pthread_mutex_lock(data->ph[id].left);
	pthread_mutex_lock(&data->death);
	printf("%-6lld %d has taken a fork\n", get_ms(data->start), id + 1);
	gettimeofday(&data->ph[id].eat, NULL);
	printf("%-6lld %d is eating\n", get_ms(data->start), id + 1);
	pthread_mutex_unlock(&data->death);
	if (data->cycle != -1)
		data->ph[id].cycle++;
	usleeper(data->time_to_eat, data->start);
	pthread_mutex_unlock(data->ph[id].right);
	pthread_mutex_unlock(data->ph[id].left);
}

void	eating_even(t_data *data, int id)
{
	pthread_mutex_lock(data->ph[id].left);
	pthread_mutex_lock(&data->death);
	printf("%-6lld %d has taken a fork\n", get_ms(data->start), id + 1);
	pthread_mutex_unlock(&data->death);
	pthread_mutex_lock(data->ph[id].right);
	pthread_mutex_lock(&data->death);
	printf("%-6lld %d has taken a fork\n", get_ms(data->start), id + 1);
	gettimeofday(&data->ph[id].eat, NULL);
	printf("%-6lld %d is eating\n", get_ms(data->start), id + 1);
	pthread_mutex_unlock(&data->death);
	if (data->cycle != -1)
		data->ph[id].cycle++;
	usleeper(data->time_to_eat, data->start);
	pthread_mutex_unlock(data->ph[id].left);
	pthread_mutex_unlock(data->ph[id].right);
}

void	sleeping(t_data *data, int id)
{
	pthread_mutex_lock(&data->death);
	printf("%-6lld %d is sleeping\n", get_ms(data->start), id + 1);
	pthread_mutex_unlock(&data->death);
	usleeper(data->time_to_sleep, data->start);
}

void	thinking(t_data *data, int id)
{
	pthread_mutex_lock(&data->death);
	printf("%-6lld %d is thinking\n", get_ms(data->start), id + 1);
	pthread_mutex_unlock(&data->death);
}
