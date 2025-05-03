/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:31:14 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/03 15:50:23 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_checker(char *line)
{
	if (ft_strlen(line) == 0)
		return (0);
	if (!line)
		return (0);
	if (check_cote(line) == 0 || check_pipe(line) == 0
		|| check_chevron(line) == 0 || check_else(line) == 0)
		return (0);
	return (1);
}
