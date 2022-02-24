/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle-assistant.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:25:55 by emende            #+#    #+#             */
/*   Updated: 2022/02/24 18:26:33 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wordle.h"
#include "../../libftproject/libftvogo/libft.h"
//#include "libft.h"
#include "../../gnl/gnlvogo/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>//free and exit

void    free_wordlist(t_list **abl)
{
    if ((*abl)->next != NULL)
        free_wordlist(&(*abl)->next);
    free((*abl)->content);
    free(*abl);
}

void	ft_lstpop(t_list **alst, char *content)
{
	t_list	*temp;
	t_list	*next;

	temp = *alst;
	if (temp->content == content)
	{
		*alst = (*alst)->next;
		return ;
	}
	while (temp != NULL)
	{
		if (temp->next && ft_strcmp((const char *) (temp->next)->content, (char const *) content) == 0)
		{
			next = temp->next->next;
			ft_memdel((void **) &(temp->next)->content);
			(temp->next)->content_size = 0;
			ft_memdel((void **) &(temp->next));
			temp->next = next;
			return ;
		}
		temp = temp->next;
	}
}

void	ft_lstadd_back(t_list **begin_list, t_list *new)
{
	t_list *list;

	list = *begin_list;
	while (list->next != NULL)
		list = list->next;
	list->next = new;
}

int print_list(t_list *list)
{
	t_list	  *temp;
	int		   i;

	if (list == NULL)
	{
		ft_putendl("\n\t\033[0;31m ▄▄▄▄    ▒█████   ▒█████   ██░ ██  ▒█████   ▒█████  ");
		ft_putendl("\t▓█████▄ ▒██▒  ██▒▒██▒  ██▒▓██░ ██▒▒██▒  ██▒▒██▒  ██▒");
		ft_putendl("\t▒██▒ ▄██▒██░  ██▒▒██░  ██▒▒██▀▀██░▒██░  ██▒▒██░  ██▒");
		ft_putendl("\t▒██░█▀  ▒██   ██░▒██   ██░░▓█ ░██ ▒██   ██░▒██   ██░");
		ft_putendl("\t░▓█  ▀█▓░ ████▓▒░░ ████▓▒░░▓█▒░██▓░ ████▓▒░░ ████▓▒░");
		ft_putendl("\t░▒▓███▀▒░ ▒░▒░▒░ ░ ▒░▒░▒░  ▒ ░░▒░▒░ ▒░▒░▒░ ░ ▒░▒░▒░ ");
		ft_putendl("\t▒░▒   ░   ░ ▒ ▒░   ░ ▒ ▒░  ▒ ░▒░ ░  ░ ▒ ▒░   ░ ▒ ▒░ ");
		ft_putendl("\t ░    ░ ░ ░ ░ ▒  ░ ░ ░ ▒   ░  ░░ ░░ ░ ░ ▒  ░ ░ ░ ▒  ");
		ft_putendl("\t ░          ░ ░      ░ ░   ░  ░  ░    ░ ░      ░ ░  ");
		ft_putendl("\t      ░                                             \033[0;37m");

		ft_putstr("\t\t\033[1;31mNo words remaining... Or you used whitespaces -.-\033[0;37m\n\n");
		return (1);
	}
	temp = list;
	i = 1;
	ft_putstr("\n\t\033[1;32mPossible answers:\033[0;37m\n\t\t");
	while (temp)
	{
		ft_putstr((char const *) temp->content);
		if (i % 5 == 0)
			ft_putstr("\n\t\t");
		else if (temp->next == NULL)
			ft_putchar('\n');
		else
			ft_putstr(", ");
		temp = temp->next;
		i++;
	}
	return (0);
}

int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

void	remove_gray_words(t_list **list, char c, char **greenletters, char **yellowletters)
{
	t_list	*temp;
	char	*word;
	int		i;

	temp = *list;
	while (temp)
	{
		word = (char *) temp->content;
		i = 0;
		while (word[i])
		{
			if (word[i] == c && !(ft_strchr(*greenletters, c)) && !(ft_strchr(*yellowletters, c)))
				ft_lstpop(list, word);
			i++;
		}
		temp = temp->next;
	}
}

void	remove_yellow_words(t_list **list, char c, size_t pos, char **yellowletters)
{
	t_list	*temp;
	char	*word;
	size_t	i;
	size_t	count;

	i = 0;
	if (!ft_strchr((*yellowletters),  c))
	{
		while (i < 5)
		{
			if ((*yellowletters)[i] == '.')
			{
				(*yellowletters)[i] = c;
				break;
			}
			i++;
		}
	}
	temp = *list;
	while (temp)
	{
		word = (char *) temp->content;
		if (word[pos] == c)
			ft_lstpop(list, word);
		else
		{
			i = 0;
			count = 0;
			while (word[i])
			{
				if (word[i] == c)
					count++;
				i++;
			}
			if (count == 0)
				ft_lstpop(list, word);
		}
		temp = temp->next;
	}
}

void remove_false_green(t_list **list, char c, size_t i,  char **greenletters)
{
	t_list	*temp;
	char	*word;

	(*greenletters)[i] = c;
	temp = *list;
	while (temp)
	{
		word = (char *) temp->content;
		if (word[i] != c)
			ft_lstpop(list, word);
		temp = temp->next;
	}
}

void	ft_print_congrats(void)
{
	printf("\n\t-----------------------------------------------------------------\n");
	ft_putendl("\033[1;32m ▄████▄   ▒█████   ███▄    █   ▄████  ██▀███   ▄▄▄     ▄▄▄█████▓  ██████  ▐██▌ ");
	ft_putendl("▒██▀ ▀█  ▒██▒  ██▒ ██ ▀█   █  ██▒ ▀█▒▓██ ▒ ██▒▒████▄   ▓  ██▒ ▓▒▒██    ▒  ▐██▌ ");
	ft_putendl("▒▓█    ▄ ▒██░  ██▒▓██  ▀█ ██▒▒██░▄▄▄░▓██ ░▄█ ▒▒██  ▀█▄ ▒ ▓██░ ▒░░ ▓██▄    ▐██▌ ");
	ft_putendl("▒▓▓▄ ▄██▒▒██   ██░▓██▒  ▐▌██▒░▓█  ██▓▒██▀▀█▄  ░██▄▄▄▄██░ ▓██▓ ░   ▒   ██▒ ▓██▒ ");
	ft_putendl("▒ ▓███▀ ░░ ████▓▒░▒██░   ▓██░░▒▓███▀▒░██▓ ▒██▒ ▓█   ▓██▒ ▒██▒ ░ ▒██████▒▒ ▒▄▄  ");
	ft_putendl("░ ░▒ ▒  ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒  ░▒   ▒ ░ ▒▓ ░▒▓░ ▒▒   ▓▒█░ ▒ ░░   ▒ ▒▓▒ ▒ ░ ░▀▀▒ ");
	ft_putendl("  ░  ▒     ░ ▒ ▒░ ░ ░░   ░ ▒░  ░   ░   ░▒ ░ ▒░  ▒   ▒▒ ░   ░    ░ ░▒  ░ ░ ░  ░ ");
	ft_putendl("░        ░ ░ ░ ▒     ░   ░ ░ ░ ░   ░   ░░   ░   ░   ▒    ░      ░  ░  ░      ░ ");
	ft_putendl("░ ░          ░ ░           ░       ░    ░           ░  ░              ░   ░    ");
	ft_putendl("░                                                                              \033[0;37m");
}

int	remove_assistant(t_list **list, char *guess, char *feedback)
{
	size_t	i;
	static char	*greenletters;
	static char	*yellowletters;

	if (!greenletters)
	{
		greenletters = ft_strnew(5);
		ft_memset(greenletters,  '.', 5);
	}
	if (!yellowletters)
	{
		yellowletters = ft_strnew(5);
		ft_memset(yellowletters,  '.', 5);
	}
	i = 0;
	while (ft_isupper((int) feedback[i]) && i < 5)
	{
		i++;
		if (i == 5)
		{
			ft_print_congrats();
			return (1);
		}
	}
	i = 0;
	while (i < 5)
	{
		if (feedback[i] == '!')
			remove_gray_words(list, guess[i], &greenletters, &yellowletters);
		if (ft_islower((int ) feedback[i]))
			remove_yellow_words(list, guess[i], i, &yellowletters);
		else if (ft_isupper((int ) feedback[i]))
			remove_false_green(list, guess[i], i, &greenletters);
		i++;
	}
	return (0);
}

void	ft_printrules(void)
{
	printf("\n\tGUESS RULES:\tWrite the guessed word in lowercase letters\n\t\t\tWrite only 5 letters\n");
	printf("\n\tFEEDBACK RULES:\tWrite the feedback word so that if a letter is \n\t\t\t- green, substitute it for a CAPITAL LETTER");
	printf("\n\t\t\t- yellow, write it as it is\n\t\t\t- grey, substitute it for a !\n");
	printf("\n\tEXAMPLE:\tFor \033[0;33mA\033[0mI\033[0;33mS\033[0mL\033[0;32mE\033[0m you would write: a!s!E\n");
	printf("\n\tIMPORTANT:\tDO NOT USE WHITESPACES (SPACES, TABS, ...)\n\t\t\tOr you will experience undefined behaviour\n\n\t\t\tGOOD LUCK\n");
}

int	main(void)
{
	int		fd;
	int		i;
	int		round;
	char	*line;
	char	guess[6];
	char	feedback[6];
	t_list	*word_list;
	t_list *temp;

	fd = open("wordle-answers.txt", O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("error\n", 2);
		return (-1);
	}
	i = 0;
	get_next_line(fd, &line);
	word_list = ft_lstnew((void const *) line, 6);
	free(line);
	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&word_list, ft_lstnew((void const *) line, 6));
		free(line);
	}
	i = 0;
	temp = word_list;
	round = 1;
	printf("\n\t\t\tWelcome to WORLDE ASSISTANT\n\t-----------------------------------------------------------------\n");
	ft_printrules();
	while (round <= 6)
	{
		printf("\n\t-----------------------------------------------------------------\n");
		printf("\n\tGuess %d: ", round);
		scanf("%s", guess);
		while (ft_strlen(guess) != 5)
		{
			printf("\n\tGUESS RULES:\tWrite the guessed word in lowercase letters\n\t\t\tWrite only 5 letters\n");
			printf("\n\tGuess %d: ", round);
			scanf("%s", guess);
		}
		printf("\n\tFeedback %d: ", round);
		scanf("%s", feedback);
		while (ft_strlen(feedback) != 5)
		{
			printf("\n\tFEEDBACK RULES:\tWrite the feedback word so that if a letter is \n\t\t\t- green, substitute it for a CAPITAL LETTER");
			printf("\n\t\t\t- yellow, write it as it is\n\t\t\t- grey, substitute it for a !\n\t\t\tWrite only 5 letters\n");
			printf("\n\tEXAMPLE:\tFor \033[0;33mA\033[0mI\033[0;33mS\033[0mL\033[0;32mE\033[0m you would write: a!s!E\n");
			printf("\n\tGuess %d: ", round);
			scanf("%s", feedback);
		}
		if ((remove_assistant(&word_list, guess, feedback) == 1) || (print_list(word_list) == 1))
			break;
//		else
//			print_list(word_list);
		round++;
	}
	free_wordlist(&word_list);
	system("leaks a.out");
	return (0);
}
