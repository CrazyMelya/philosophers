/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:44:01 by cliza             #+#    #+#             */
/*   Updated: 2021/10/23 18:24:26 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	life(t_data *data, int id)
{
	pthread_t	philo;

	pthread_create(&philo, NULL, checker, data);
	pthread_detach(philo);
	data->id = id;
	while (1)
	{
		eating(data, id);
		if (data->cycle != -1)
			data->ph[id].cycle++;
		usleeper(data->time_to_eat, data->start);
		sem_post(data->forks), sem_post(data->forks);
		if (data->cycle == data->ph[id].cycle)
			break ;
		sem_wait(data->write);
		printf("%-6lld %d is sleeping\n", get_ms(data->start), id + 1);
		sem_post(data->write);
		usleeper(data->time_to_sleep, data->start);
		sem_wait(data->write);
		printf("%-6lld %d is thinking\n", get_ms(data->start), id + 1);
		sem_post(data->write);
	}
	exit(0);
}

void	eating(t_data *data, int i)
{
	if (i % 2 && data->num % 2)
		usleep(50);
	sem_wait(data->forks);
	sem_wait(data->write);
	printf("%-6lld %d has taken a fork\n", get_ms(data->start), i + 1);
	sem_post(data->write);
	sem_wait(data->forks);
	sem_wait(data->write);
	printf("%-6lld %d has taken a fork\n", get_ms(data->start), i + 1);
	gettimeofday(&data->ph[i].eat, NULL);
	printf("%-6lld %d is eating\n", get_ms(data->start), i + 1);
	sem_post(data->write);
}
