/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:21:57 by carperez          #+#    #+#             */
/*   Updated: 2023/10/10 18:14:02 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minitalk.h"

//"g_msg" is the global pointer variable that serves as the header of the list
// in which each node will store a character from most significant to least
// significant.
t_list	*g_msg = NULL;

//"ft_show_char" is a function that displays the character stored in a node.
static void	ft_show_char(void *pChar)
{
	ft_printf("%c", *(unsigned char *)pChar);
}

//"ft_node_creator" is a function that creates a new node and initializes
// it with a character.
static void	*ft_node_creator(unsigned char cChar)
{
	t_list	*p_nodo;

	p_nodo = ft_lstnew(NULL);
	if (p_nodo)
	{
		p_nodo->content = malloc(sizeof(char));
		if (p_nodo->content)
			*(unsigned char *)(p_nodo->content) = cChar;
	}
	else
		ft_msg_2(3, 0, NULL, g_msg);
	return (p_nodo);
}

//"ft_bit_manager" manages the bits received by the client process to interpret
// the corresponding character in the server process.
static int	ft_bit_manager(int nBit, unsigned char *vChar, int signum)
{
	if (nBit < 0)
		nBit = 7;
	if (signum == SIGUSR1)
		*vChar |= (1 << nBit);
	nBit --;
	return (nBit);
}	

//"ft_sig_trigger" is a function that runs every time the server process
// receives a signal from the client process. It manages the storage of
// received characters, the display of the complete received message on
// the terminal, and the confirmation for each received bit.
static void	ft_sig_trigger(int signum, siginfo_t *info, void *ucontent)
{
	static unsigned char	v_char;
	static int				n_octbits;
	static int				v_clpid;
	t_list					*p_aux;

	(void)ucontent;
	if (v_clpid != info->si_pid)
		v_clpid = ft_client_ini(info->si_pid, &n_octbits, &g_msg);
	n_octbits = ft_bit_manager(n_octbits, &v_char, signum);
	if (n_octbits < 0)
	{
		p_aux = ft_node_creator(v_char);
		ft_lstadd_back(&g_msg, p_aux);
		p_aux = NULL;
		if (!v_char)
		{
			ft_lstiter(g_msg, &ft_show_char);
			ft_lstclear(&g_msg, &free);
			g_msg = NULL;
		}
		v_char = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_msg_2(2, info->si_pid, NULL, g_msg);
}

//It is the main function of the server process: it displays the
// process's PID on the terminal and listens for signals from any client
// process.
int	main(void)
{
	pid_t				v_srvpid;
	struct sigaction	s_act4signal;

	v_srvpid = getpid();
	ft_putstr_fd(COLOR_BRIGHT_CYAN, 1);
	ft_printf("Server Process PID --> %d\n", v_srvpid);
	while (1)
	{
		s_act4signal.sa_sigaction = &ft_sig_trigger;
		s_act4signal.sa_flags = SA_SIGINFO;
		if (sigaction(SIGUSR1, &s_act4signal, NULL) == -1
			|| sigaction(SIGUSR2, &s_act4signal, NULL) == -1)
			ft_msg_2(1, v_srvpid, NULL, g_msg);
	}
	return (0);
}

//END