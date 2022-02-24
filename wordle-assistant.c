/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle-assistant.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:25:55 by emende            #+#    #+#             */
/*   Updated: 2022/02/24 13:55:44 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wordle.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

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

void print_list(t_list *list)
{
	t_list	*temp;

	if (list == NULL)
	{
		ft_putendl_fd("No words remaining...", 2);
		exit (1);
	}
	temp = list;
	while (temp)
	{
		ft_putendl((char const *) temp->content);
		temp = temp->next;
	}
}

int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

void	remove_gray_words(t_list **list, char c, char **greenletters)
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
			if (word[i] == c && !(ft_strchr(*greenletters, c)))
				ft_lstpop(list, word);
			i++;
		}
		temp = temp->next;
	}
}

void	remove_yellow_words(t_list **list, char c, size_t pos)
{
	t_list	*temp;
	char	*word;
	size_t	i;
	size_t	count;

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
//	static char	greenletters[6];

//	if (!greenletters)
//		ft_memset(greenletters,  '.', 5);
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

void	remove_assistant(t_list **list, char *guess, char *feedback)
{
	size_t	i;
	static char	*greenletters;

	if (!greenletters)
	{
		greenletters = ft_strnew(5);
		ft_memset(greenletters,  '.', 5);
	}
	i = 0;
	while (ft_isupper((int) feedback[i]) && i < 5)
	{
		i++;
		if (i == 5)
		{
			ft_putendl("Congratz!");
			exit (1);
		}
	}
	i = 0;
	while (i < 5)
	{
		if (feedback[i] == '!')
			remove_gray_words(list, guess[i], &greenletters);
		if (ft_islower((int ) feedback[i]))
			remove_yellow_words(list, guess[i], i);
		else if (ft_isupper((int ) feedback[i]))
			remove_false_green(list, guess[i], i, &greenletters);
		i++;
	}
}

int	main(void)
{
	int		fd;
	int		i;
	int		round;
	char	*line;
	char	guess[10];
	char	feedback[10];
	t_list	*word_list;
	t_list *temp;
//	static char	greenletters[6];

//	ft_memset(greenletters,  '.', 5);
//	line = ft_strnew(10);
//	guess = ft_strnew(10);
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
/*		ft_putendl(line); */
/*		array[i++] = ft_strdup(line); */
		free(line);
	}
	i = 0;
	temp = word_list;
/*	temp = temp->next->next; */
//	ft_lstpop(&word_list, "five");
//	print_list(word_list);
	round = 1;
	while (round <= 5)
	{
		printf("Guess %d: ", round);
		scanf("%s", guess);
//		remove_blank(&word_list, guess);
//		printf("Your guess: %s\n", guess);
		printf("Feedback %d: ", round);
		scanf("%s", feedback);
		remove_assistant(&word_list, guess, feedback);
//		printf("Your feedback: %s\n", feedback);
		print_list(word_list);
		round++;
	}
	return (0);
}
