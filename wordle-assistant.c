/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldle-assistant.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:25:55 by emende            #+#    #+#             */
/*   Updated: 2022/02/23 17:36:11 by emende           ###   ########.fr       */
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
		if (ft_strcmp((const char *) (temp->next)->content, (char const *) content) == 0)
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

int	main(void)
{
	int		fd;
	int		i;
/*	int		round; */
	char	*line;
/*	char	guess[10];
	char	feedback[10];
	char	*array[ALLOWED_COUNT]; */
	t_list	*word_list;
	t_list *temp;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("error\n", 2);
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
	ft_lstpop(&word_list, "five");
	while (word_list != NULL)
	{
		ft_putendl((char const *) word_list->content);
		word_list = word_list->next;
	}
/*	while (array[i])
	{
		ft_putendl((const char *) array[i++]);
	} */
/*	round = 1;
	while (round <= 5)
	{
		printf("Guess %d: ", round);
		scanf("%s", guess);
		printf("Your guess: %s\n", guess);
		printf("Feedback %d: ", round);
		scanf("%s", feedback);
		printf("Your feedback: %s\n", feedback);
		round++;
	} */
}
