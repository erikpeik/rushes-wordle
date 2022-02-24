/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:24:23 by acastano          #+#    #+#             */
/*   Updated: 2022/02/23 18:27:55 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libftproject/libftvogo/libft.h"
#include <stdio.h>
//char	*ft_strchr(const char *s, int c); returns pointer to char or NULL
//int strncmp(const char *s1, const char *s2, size_t n); compares all chars in string, max n chars, returns 0 if equal
//strnequ similar but compares all string and returns 1 if equal, 0 if not
//ft_putstr to output
//ft_putstr_fd to output to list

/*
List of answers
Starting word - feedback
remove words with letters marked out, and letters not in correct possition

int	ft_is_letter(char *word, char *guess)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (word[i])
	{
		while (guess[j])
		{
			if (ft_strchr(word, guess[j]))
			{
				return (1);
			}
			j++;
		}
		i++;
		}
	return (0);
	}
*/

int	ft_is_letteri(char *word, char *c)//returns index where it finds letter, or 5 if it doesn't find it
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (word[i] == c)
			break;
		i++;
	}
	return (i);
}

int	ft_get_info(char *word, char *answer)//fix
{
	char	*info[4];
//	char	*letters;//[27] = "abcdefghijklmnopqrstuvwxyz";//26
	char	*yes;
	char	*somewhere;
	char	*not;

//	letters = "abcdefghijklmnopqrstuvwxyz";//26 + \0
	yes = ft_strnew(5);
	somewhere = ft_strnew(5);
	not = '\0';
//	info[0] = letters;
	info[0] = yes;
	info[1] = somewhere;
	info[2] = not;
	info[3] = NULL;
	int	index = 0;
	int	curr = 0;
	while (i < 5)
	{
		curr = ft_is_letteri(word, answer[i]);
		if (curr == i)
			yes[i] = answer[i];
		else if (curr < 5)
		{
			somewhere[i] = answer[i];
		}
		else
		{
			not = ft_strjoin(not, answer[i]);
//take it from letters?
		}
		i++;
	}
	return (0);
}

int	ft_solver(char *word, char *guess)//burns, crawl
{
	if (ft_strequ(word, guess) == 1)
	{
		printf("You guessed correctly! The word is \033[0;32m%s\033[0m\n", guess);
		return (0);
	}
	ft_get_info(word, guess);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*word;
	char	*guess;

	word = "burns";
	if (argc != 2 || (ft_strlen(argv[1]) != 5))
	{
		ft_putstr("Only one word of 5 characters is allowed");
		return (0);
	}
	guess = argv[1];
	ft_putstr("Your guess is: ");
	ft_putstr(argv[1]);
	ft_putstr("\n");
	ft_solver(word, argv[1]);
	return (0);
}
