/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:24:15 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/29 01:25:29 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

int		space(char c);

void	msg_syntax_error(char c);

int		check_cote(char *line);

int		check_else(char *line);

int		check_chevron(char *line);

int		check_pipe(char *line);

int		syntax_checker(char *line);

#endif
