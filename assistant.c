/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assistant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:28:22 by acastano          #+#    #+#             */
/*   Updated: 2022/02/23 23:15:16 by acastano         ###   ########.fr       */
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
*/

int	ft_save_guess(char *guess, char **green, char **yellow)
{
//	char	*letters;//[27] = "abcdefghijklmnopqrstuvwxyz";//26
	int		i;

	i = 0;
	printf("get to A\n");
	if (*yellow == NULL)
		*yellow = ft_strnew(5);
	else
		ft_memset(*yellow, '\0', 5);
	printf("get to B\n");
	while ((size_t)i < ft_strlen(guess))
	{
		printf("get to C\n");
		if (guess[i] >= 'A' && guess[i] <= 'Z')
		{
			printf("get to D\n");
			if (*green == NULL)
				*green = ft_strnew(5);
			*green[i] = guess[i];
		}
		printf("get to E, yellow is %s\n", *yellow);
		if (guess[i] >= 'a' && guess[i] <= 'z')
			*yellow[i] = guess[i];
		i++;
	}
	return (0);
}

int	ft_save_wrong(char *wrong, char **grey)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("get to 1\n");
	if (*grey == NULL)
		*grey = ft_strnew(26);//"abcdefghijklmnopqrstuvwxyz"
	printf("get to 2\n");
	while ((size_t)i < ft_strlen(wrong))
	{
		printf("get to 3\n");
		j = (wrong[i] - 'a');
		*grey[j] = wrong[i];
		i++;
	}
	printf("get to 4\n");
	return (0);
}

int	ft_assistant(char *guess, char *wrong)//a!s!E, il
{
	static char	*info[4];//free at end

//	if ()//TO DO: all caps in guess
//	{
//		printf("You guessed correctly! The word is \033[0;32m%s\033[0m\n", guess);
//		ft_strdel(info);
//		return (1);
//	}
	printf("get to 0, %s %zu, %s %zu\n", guess, ft_strlen(guess), wrong, ft_strlen(wrong));
	if (ft_strlen(guess) > 0)
		ft_save_guess(guess, &info[0], &info[1]);
	printf("get to 0B\n");
	if (ft_strlen(wrong) > 0)
		ft_save_wrong(wrong, &info[2]);
	printf("get to 0C\n");
//Erik's code updates list based on the info in static variable
	if (ft_strlen(info[0]) == 5)
	{
		printf("You guessed correctly! The word is \033[0;32m%s\033[0m\n", guess);
		ft_strdel(info);
		return (1);
	}
	printf("Correct letters: \033[0;32m%s\033[0m \nWrong place: \033[0;33m%s\033[0m \nNot in word: %s", info[0], info[1], info[2]);
	return (0);
}

int	main(void)
{
	int		round;
	char	guess[6];
	char	wrong[6];

	round = 1;
	printf("Possible word list:\n\tErik's code displays list here\n\n");
	while (round <= 1)
	{
		printf("Round %d:\n\tWrite the guessed word so that\n\t\t- If a letter is green, substitute it for a CAPITAL LETTER\n\t\t- Letter is yellow, write it as it is\n\t\t- Letter is grey, substitute it for a !\n\t\tExample: For \033[0;33ma\033[0mi\033[0;33ms\033[0ml\033[0;32me\033[0m you would write: a!s!E\n", round);
		scanf("%s", guess);
		printf("\n\tWrite only the letters that were grey.\n\t\tExample: For \033[0;33ma\033[0mi\033[0;33ms\033[0ml\033[0;32me\033[0m you would write: il\n");
		scanf("%s", wrong);
		if (ft_assistant(guess, wrong) == 1)//correct word, end. TO DO: check free of static variable is in right place, and all frees
			break;
		printf("Possible word list:\n\tErik's code displays list here\n\n");
		round++;
	}
	return (0);
}
