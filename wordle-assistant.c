/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldle-assistant.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:25:55 by emende            #+#    #+#             */
/*   Updated: 2022/02/23 14:12:24 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wordle.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
	int		fd;
	int		i;
	int		round;
	char	*line;
	char	guess[10];
	char	feedback[10];
	char	*array[ALLOWED_COUNT];

	fd = open("wordle-allowed-guesses.txt", O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("error\n", 2);
	}
	i = 0;
	while (get_next_line(fd, &line))
	{
/*		ft_putendl(line); */
		array[i++] = ft_strdup(line);
		free(line);
	}
	i = 0;
/*	while (array[i])
	{
		ft_putendl((const char *) array[i++]);
	} */
	round = 1;
	while (round <= 5)
	{
		printf("Guess %d: ", round);
		scanf("%s", guess);
		printf("Your guess: %s\n", guess);
		printf("Feedback %d: ", round);
		scanf("%s", feedback);
		printf("Your feedback: %s\n", feedback);
		round++;
	}
}
