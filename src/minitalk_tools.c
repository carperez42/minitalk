/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:37:21 by carperez          #+#    #+#             */
/*   Updated: 2023/10/10 18:14:35 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minitalk.h"

//"ft_memliberator" This function frees dynamically allocated memory during
// program execution and initializes the associated header pointer to NULL.
void	ft_memliberator(char **pMemory)
{
	free(*pMemory);
	*pMemory = NULL;
}

//"ft_pid_checker" is a function that ensures that the PID parameter consists
// only of numeric characters.
int	ft_pid_checker(const char *pStr)
{
	if (*pStr != '\0')
	{
		if (ft_isdigit(*pStr))
			return (ft_pid_checker(pStr + 1));
		else
			return (0);
	}
	return (1);
}

//"ft_msg_1" is a function that handles unique exceptions in the client process.
void	ft_msg_1(int numCase, int nPID, int *numBit, char *pBinary)
{
	if (!numCase)
	{
		ft_putstr_fd(COLOR_BRIGHT_RED, 2);
		ft_printf("ERROR: Invalid inputs\n");
		ft_putstr_fd(COLOR_BRIGHT_YELLOW, 2);
		ft_printf("FORMAT: [./client <NUM_PID> <STR_MSG>]"
			" (100 <= NUM_PID <= 99998)\n");
		exit(EXIT_FAILURE);
	}	
	else if (numCase == 1)
	{
		ft_putstr_fd(COLOR_BRIGHT_CYAN, 1);
		ft_printf("From serverPID %d to clientPID %d:"
			" ACK of bit %d !!!\n", nPID, (int)getpid(), *numBit);
		*numBit += 1;
	}
	else if (numCase == 2)
	{
		ft_putstr_fd(COLOR_BRIGHT_GREEN, 1);
		ft_printf("clientPID %d: Full message sent"
			" to serverPID %d!!!\n", (int)getpid(), nPID);
		ft_memliberator(&pBinary);
		exit(EXIT_SUCCESS);
	}
}

//"ft_msg_2" is a function that handles various error exceptions.
void	ft_msg_2(int numCase, int nPID, char *pBinary, t_list *pMSG)
{
	ft_putstr_fd(COLOR_BRIGHT_RED, 2);
	if (!numCase)
	{
		ft_printf("From clientPID %d to serverPID %d:"
			" Transmission ERROR!!!\n", (int)getpid(), nPID);
		ft_memliberator(&pBinary);
		exit(EXIT_FAILURE);
	}
	else if (numCase == 1)
	{
		ft_printf("serverPID %d: Unexpected ERROR!!!\n", nPID);
	}
	else if (numCase == 2)
	{
		ft_printf("From serverPID %d to clientPID %d:"
			" Transmission ERROR!!!\n", (int)getpid(), nPID);
		ft_lstclear(&pMSG, &free);
	}
	else
	{
		ft_printf("serverPID %d: Unexpected ERROR!!!\n", (int)getpid());
		ft_lstclear(&pMSG, &free);
		exit(EXIT_FAILURE);
	}
}

//"ft_client_ini" initializes the message capture parameters for a new client
// within the server process."
int	ft_client_ini(int nPID, int *nBits, t_list **pMSG)
{
	*nBits = -1;
	*pMSG = NULL;
	ft_putstr_fd(COLOR_BRIGHT_MAGENTA, 1);
	ft_printf("\nReceived message from clientPID %d: ", nPID);
	ft_putstr_fd(COLOR_BRIGHT_YELLOW, 1);
	return (nPID);
}

//END