/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:24:23 by acastano          #+#    #+#             */
/*   Updated: 2022/02/23 15:17:31 by acastano         ###   ########.fr       */
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


int	ft_is_letter(char *word, char *guess)//alter, crawl
{
	int	i;
	i = 0;
	while (word[i])
	{
		while (guess[j])
		{
			if (ft_strchr(word, guess[j]))
			{
				ft_save_letter(guess[j]);
			}
			j++;
		}
		i++;
		}
	return ();
	}

//int	ft_display_list(char *guess);
*/

int	ft_check_letters(char *word, char *answer)//fix
{
	char	*yes;
	char	*maybe;
	char	*not;
	if (ft_is_letter(word, answer) == 1)
		return (1);//same??
	return (0);
	}

int	ft_get_info(char *word, char *answer)//fix
{
	static char	*info[4];
	char	*yes;
	char	*maybe;
	char	*not;

	info[0] = yes;
	info[1] = maybe;
	info[2] = not;
	info[3] = '\0';
	if (ft_is_letter(word, answer, info) == 1)
		return (1);//same??
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
