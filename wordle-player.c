/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle-assistant.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:25:55 by emende            #+#    #+#             */
/*   Updated: 2022/02/25 02:09:52 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wordle.h"
#include "libft.h"
#include "get_next_line.h"

void    free_wordlist(t_list **abl)
{
	if (*abl != NULL)
	{
		if ((*abl)->next != NULL)
			free_wordlist(&(*abl)->next);
		free((*abl)->content);
		free(*abl);
	}
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
		ft_print_boohoo();
		return (1);
	}
	temp = list;
	i = 1;
	ft_putstr("\n\t\033[1;32mPossible answers:\033[0;37m\n\t\t");
	while (temp)
	{
		ft_putstr((char const *) temp->content);
		ft_putstr(": ");
		ft_putnbr((int ) temp->content_score);
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

void	ft_loop_word(t_list **list, char *guess, char *feedback, char **green, char **yellow)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (ft_isupper((int ) feedback[i]))
			remove_false_green(list, guess[i], i, green);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (ft_islower((int ) feedback[i]))
			remove_yellow_words(list, guess[i], i, yellow);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (feedback[i] == '!')
			remove_gray_words(list, guess[i], green, yellow);
		i++;
	}
}

int	remove_assistant(t_list **list, char *guess, char *feedback)
{
	size_t	i;
	static char	*greenletters;
	static char	*yellowletters;
}
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
	ft_loop_word(list, guess, feedback, &greenletters, &yellowletters);
	return (0);
}

int	ft_check_dup(char *word, size_t i, char c)
{
	size_t	index;

	index = 0;
	while (index < i)
	{
		if (word[index] == c)
			return (0);
		index++;
	}
	return (1);
}

void ft_score_calculator(t_list **list)
{
	size_t	*letter_occurence;
	t_list	*temp;
	char	*word;
	size_t	score;
	size_t	i;

	letter_occurence = (size_t *) malloc(26 * sizeof(size_t));
	ft_memset((void *)letter_occurence, 0, 26 * sizeof(size_t));
	temp = *list;
	while (temp)
	{
		word = (char *)temp->content;
		while (word && *word)
		{
			letter_occurence[*word - 'a'] += 1;
			word++;
		}
		temp = temp->next;
	}
	temp = *list;
	while (temp)
	{
		score = 0;
		i = 0;
		word = (char *)temp->content;
		while (word[i])
		{
			if (ft_check_dup(word, i, word[i]))
				score += letter_occurence[word[i] - 'a'];
			i++;
		}
		temp->content_score = score;
		temp = temp->next;
	}
	ft_memdel((void *) &letter_occurence);
}

char	*ft_get_best(t_list **list)
{
	t_list	*temp;
	char	*best_word;
	size_t	best_score;

	best_score = 0;
	best_word = NULL;
	temp = *list;
	while (temp)
	{
		if (temp->content_score > best_score)
		{
			best_word = (char *)temp->content;
			best_score = temp->content_score;
			printf(" %s : %zu\n ", best_word, best_score);
		}
		temp = temp->next;
	}
	return (best_word);
}

int	main(void)
{
	int		fd;
	int		i;
	int		round;
	char	*line;
	char	*guess;
	char	feedback[6];
	t_list	*word_list;
	t_list *temp;

	guess = ft_strnew(5);
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
	ft_score_calculator(&word_list);
	while (round <= 6)
	{
		printf("\n\t-----------------------------------------------------------------\n");
		printf("\n\tRound %d: ", round);
		if (round == 1)
			guess = ft_strcpy(guess, "audio");
		else
			guess = ft_strcpy(guess, ft_get_best(&word_list));
		printf("\n\tBest guessing word: %s", guess);
		printf("\n\tFeedback %d: ", round);
		scanf("%s", feedback);
		while (ft_strlen(feedback) != 5)
		{
			printf("\n\tFEEDBACK RULES:\tWrite the feedback word so that if a letter is \n\t\t\t- green, substitute it for a CAPITAL LETTER");
			printf("\n\t\t\t- yellow, write it as it is\n\t\t\t- grey, substitute it for a !\n\t\t\tWrite only 5 letters\n");
			printf("\n\tEXAMPLE:\tFor \033[0;33mA\033[0mI\033[0;33mS\033[0mL\033[0;32mE\033[0m you would write: a!s!E\n");
			printf("\n\tFeedback %d: ", round);
			scanf("%s", feedback);
		}
		if ((remove_assistant(&word_list, guess, feedback) == 1))
			break;
		ft_score_calculator(&word_list);
		if (print_list(word_list) == 1)
			break;
		round++;
	}
	ft_strdel(&guess);
	free_wordlist(&word_list);
	return (0);
}
