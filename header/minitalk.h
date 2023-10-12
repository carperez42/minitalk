/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:22:48 by carperez          #+#    #+#             */
/*   Updated: 2023/10/10 12:03:26 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/header/libft.h"
# include <signal.h>

# define COLOR_BRIGHT_RED "\x1b[91m"
# define COLOR_BRIGHT_GREEN "\x1b[92m"
# define COLOR_BRIGHT_YELLOW "\x1b[93m"
# define COLOR_BRIGHT_MAGENTA "\x1b[95m"
# define COLOR_BRIGHT_CYAN "\x1b[96m"
# define COLOR_RESET "\x1b[0m"

void	ft_memliberator(char **pMemory);
int		ft_pid_checker(const char *pStr);
void	ft_msg_1(int numCase, int nPID, int *numBit, char *pBinary);
void	ft_msg_2(int numCase, int nPID, char *pBinary, t_list *pMSG);
int		ft_client_ini(int nPID, int *nBits, t_list **pMSG);
#endif
