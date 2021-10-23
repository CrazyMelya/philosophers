/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 14:20:14 by cliza             #+#    #+#             */
/*   Updated: 2021/10/23 18:49:46 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	finish(t_data *data)
{
	int	i;
	int	s;
	int	j;

	i = 0;
	s = 0;
	j = 0;
	while (i < data->num)
	{
		waitpid(-1, &s, 0);
		i++;
		if (s)
		{
			while (j < data->num)
				kill(data->pid[j++], 9);
		}
	}
	sem_close(data->forks);
	sem_close(data->write);
	exit(0);
}

void	semaphore_init(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	data->forks = sem_open("/forks", O_CREAT, 0666, data->num);
	data->write = sem_open("/write", O_CREAT, 0666, 1);
}

void	data_create(int argc, char **argv, t_data *data)
{
	int		i;

	data->id = 0;
	data->num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->cycle = 0;
	semaphore_init(data);
	gettimeofday(&data->start, NULL);
	if (argc == 6)
		data->cycle = ft_atoi(argv[5]);
	data->ph = malloc(sizeof(t_philo) * data->num);
	data->pid = malloc(sizeof(pid_t) * data->num);
	if (!data->pid || !data->ph)
	{
		data->error = 1;
		return ;
	}
	i = -1;
	while (++i < data->num)
	{
		data->ph[i].cycle = 0;
		gettimeofday(&data->ph[i].eat, NULL);
	}
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
		while (j < (int)ft_strlen(argv[i]))
		{
			if (ft_atoi(argv[i]) < 1)
				return (-1);
			if (!ft_isdigit(argv[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
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
		data.pid[i] = fork();
		if (data.pid[i] == 0)
			life(&data, i);
		i++;
	}
	finish(&data);
}
