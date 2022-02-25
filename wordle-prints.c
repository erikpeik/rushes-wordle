/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle-prints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 01:56:10 by acastano          #+#    #+#             */
/*   Updated: 2022/02/25 02:09:35 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wordle.h"
#include "libft.h"
#include "get_next_line.h"

void	ft_print_boohoo(void)
{
	ft_putendl("\n\t\033[0;31m ▄▄▄▄	   ▒█████	▒█████	 ██░ ██	 ▒█████	  ▒█████  ");
	ft_putendl("\t▓█████▄ ▒██▒	██▒▒██▒	 ██▒▓██░ ██▒▒██▒  ██▒▒██▒  ██▒");
	ft_putendl("\t▒██▒ ▄██▒██░	██▒▒██░	 ██▒▒██▀▀██░▒██░  ██▒▒██░  ██▒");
	ft_putendl("\t▒██░█▀  ▒██	██░▒██	 ██░░▓█ ░██ ▒██	  ██░▒██   ██░");
	ft_putendl("\t░▓█  ▀█▓░ ████▓▒░░ ████▓▒░░▓█▒░██▓░ ████▓▒░░ ████▓▒░");
	ft_putendl("\t░▒▓███▀▒░ ▒░▒░▒░ ░ ▒░▒░▒░	 ▒ ░░▒░▒░ ▒░▒░▒░ ░ ▒░▒░▒░ ");
	ft_putendl("\t▒░▒	░	░ ▒ ▒░	 ░ ▒ ▒░	 ▒ ░▒░ ░  ░ ▒ ▒░   ░ ▒ ▒░ ");
	ft_putendl("\t ░	░ ░ ░ ░ ▒  ░ ░ ░ ▒	 ░	░░ ░░ ░ ░ ▒	 ░ ░ ░ ▒  ");
	ft_putendl("\t ░		  ░ ░	   ░ ░	 ░	░  ░	░ ░		 ░ ░  ");
	ft_putendl("\t		░											  \033[0;37m");

	ft_putstr("\t\t\033[1;31mNo words remaining... Or you used whitespaces -.-\033[0;37m\n\n");
}

void	ft_print_congrats(void)
{
	printf("\n\t-----------------------------------------------------------------\n");
	ft_putendl("\033[1;32m ▄████▄	▒█████	 ███▄	 █	 ▄████	██▀███	 ▄▄▄	 ▄▄▄█████▓	██████	▐██▌ ");
	ft_putendl("▒██▀ ▀█	 ▒██▒  ██▒ ██ ▀█   █  ██▒ ▀█▒▓██ ▒ ██▒▒████▄   ▓  ██▒ ▓▒▒██	   ▒  ▐██▌ ");
	ft_putendl("▒▓█	   ▄ ▒██░  ██▒▓██  ▀█ ██▒▒██░▄▄▄░▓██ ░▄█ ▒▒██  ▀█▄ ▒ ▓██░ ▒░░ ▓██▄	  ▐██▌ ");
	ft_putendl("▒▓▓▄ ▄██▒▒██   ██░▓██▒	▐▌██▒░▓█  ██▓▒██▀▀█▄  ░██▄▄▄▄██░ ▓██▓ ░	  ▒	  ██▒ ▓██▒ ");
	ft_putendl("▒ ▓███▀ ░░ ████▓▒░▒██░	 ▓██░░▒▓███▀▒░██▓ ▒██▒ ▓█	▓██▒ ▒██▒ ░ ▒██████▒▒ ▒▄▄  ");
	ft_putendl("░ ░▒ ▒	░░ ▒░▒░▒░ ░ ▒░	 ▒ ▒  ░▒   ▒ ░ ▒▓ ░▒▓░ ▒▒	▓▒█░ ▒ ░░	▒ ▒▓▒ ▒ ░ ░▀▀▒ ");
	ft_putendl("  ░	 ▒	   ░ ▒ ▒░ ░ ░░	 ░ ▒░  ░   ░   ░▒ ░ ▒░	▒	▒▒ ░   ░	░ ░▒  ░ ░ ░	 ░ ");
	ft_putendl("░		 ░ ░ ░ ▒	 ░	 ░ ░ ░ ░   ░   ░░	░	░	▒	 ░		░  ░  ░		 ░ ");
	ft_putendl("░ ░			 ░ ░		   ░	   ░	░			░  ░			  ░	  ░	   ");
	ft_putendl("░																			   \033[0;37m");
}

void	ft_printrules(void)
{
	printf("\n\tGUESS RULES:\tWrite the guessed word in lowercase letters\n\t\t\tWrite only 5 letters\n");
	printf("\n\tFEEDBACK RULES:\tWrite the feedback word so that if a letter is \n\t\t\t- green, substitute it for a CAPITAL LETTER");
	printf("\n\t\t\t- yellow, write it as it is\n\t\t\t- grey, substitute it for a !\n");
	printf("\n\tEXAMPLE:\tFor \033[0;33mA\033[0mI\033[0;33mS\033[0mL\033[0;32mE\033[0m you would write: a!s!E\n");
	printf("\n\tIMPORTANT:\tDO NOT USE WHITESPACES (SPACES, TABS, ...)\n\t\t\tOr you will experience undefined behaviour\n\n\t\t\tGOOD LUCK\n");
}
