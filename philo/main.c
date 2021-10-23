/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 14:20:14 by cliza             #+#    #+#             */
/*   Updated: 2021/10/23 18:52:10 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	another_data_create(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->death, NULL);
	i = 0;
	while (i < data->num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->ph[i].right = &data->forks[i];
		data->ph[i].cycle = 0;
		gettimeofday(&data->ph[i].eat, NULL);
		if (i == data->num - 1)
			data->ph[i].left = &data->forks[0];
		else
			data->ph[i].left = &data->forks[i + 1];
		i++;
	}
}

void	data_create(int argc, char **argv, t_data *data)
{
	gettimeofday(&data->start, NULL);
	data->id = 0;
	data->num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->cycle = 0;
	if (argc == 6)
		data->cycle = ft_atoi(argv[5]);
	data->error = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num);
	data->ph = malloc(sizeof(t_philo) * data->num);
	if (!data->ph || !data->forks)
	{
		data->error = 1;
		return ;
	}
	another_data_create(data);
}

int	check_parametrs(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (-1);
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		if (ft_atoi(argv[i]) < 1)
			return (-1);
		while (j < (int)ft_strlen(argv[i]))
		{
			if (!ft_isdigit(argv[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	finish(t_data *data, pthread_t *death)
{
	int	i;

	pthread_join(*death, NULL);
	i = 0;
	while (i < data->num)
		pthread_join(data->ph[i++].pth, NULL);
	i = 0;
	while (i < data->num)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->death);
}

int	main(int argc, char **argv)
{
	pthread_t	death;
	t_data		data;
	int			i;

	if (check_parametrs(argc, argv))
	{
		ft_putstr_fd("Wrong parametrs!\n", 2);
		return (0);
	}
	data_create(argc, argv, &data);
	if (data.error)
	{
		ft_putstr_fd("Malloc error!\n", 2);
		return (0);
	}
	i = 0;
	while (i < data.num)
	{
		pthread_create(&data.ph[i].pth, NULL, life, &data);
		pthread_detach(data.ph[i++].pth);
	}
	pthread_create(&death, NULL, checker, &data);
	finish(&data, &death);
}
