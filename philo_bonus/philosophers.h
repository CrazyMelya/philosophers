/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 14:20:06 by cliza             #+#    #+#             */
/*   Updated: 2021/10/25 13:44:04 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				cycle;
	struct timeval	eat;
}				t_philo;

typedef struct s_data
{
	t_philo			*ph;
	sem_t			*forks;
	sem_t			*write;
	pid_t			*pid;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num;
	int				cycle;
	int				id;
	int				error;
	struct timeval	start;
}				t_data;

int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
long long	get_ms(struct timeval old);
void		usleeper(long time, struct timeval now);
void		*checker(void *arg);
int			check_stomacks(t_data *data);
size_t		ft_strlen(const char *str);
int			ft_isdigit(int c);
void		life(t_data *data, int id);
void		eating(t_data *data, int i);

#endif