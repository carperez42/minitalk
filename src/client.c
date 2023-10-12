/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:21:36 by carperez          #+#    #+#             */
/*   Updated: 2023/10/10 18:14:30 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/minitalk.h"

//"g_status" is a global variable used by the client process to determine
// which actions to apply in each case.
int		g_status = 0;

//"ft_msg_converter" is a function that converts each character of the message
// sent from the client process to the server process into binary and stores it
// in dynamic memory allocation.
static void	ft_msg_converter(char **sBinary, const char *sMSG)
{
	char	*p_bit;
	int		ia;
	int		ib;

	ia = 0;
	p_bit = *sBinary;
	while (ia < (int)ft_strlen(sMSG))
	{
		ib = 7;
		while (ib >= 0)
		{
			if (sMSG[ia] & (1 << ib))
				*p_bit++ = '1';
			else
				*p_bit++ = '0';
			ib --;
		}
		ia ++;
	}
}

//"ft_msg_transfer" is a function that sends a signal upon execution from
// the client process to the server process: SIGUSR1 when it encounters the
// binary character 1 or SIGUSR2 when it encounters 0. When it encounters
// a newline character, it signals the client process to terminate
// the transmission.
static void	ft_msg_transfer(int nPID, char *sBinary)
{
	static char	*p_place;
	static int	v_pid;

	usleep(50);
	if (sBinary)
		p_place = sBinary;
	if (nPID)
		v_pid = nPID;
	if (*p_place == '\0')
		g_status = 3;
	if (*p_place == '1')
	{
		if (kill(v_pid, SIGUSR1) == -1)
			g_status = 1;
	}
	else if (*p_place == '0')
	{
		if (kill(v_pid, SIGUSR2) == -1)
			g_status = 1;
	}
	p_place ++;
	if (g_status != 1 && g_status != 3)
		g_status = 2;
}

//"ft_sig_trigger" is a function that runs every time the client process
// receives a signal from the server process. It indicates the position
// of the last bit sent up to that point and requests the transmission of
// the next bit.
static void	ft_sig_trigger(int signum, siginfo_t *info, void *ucontent)
{
	static int	n_bit;

	(void)ucontent;
	if (signum == SIGUSR1)
	{
		if (!g_status)
			n_bit = 1;
		ft_msg_1(1, info->si_pid, &n_bit, NULL);
		if (g_status == 2)
			ft_msg_transfer(0, 0);
	}
}

//"ft_status_manager" is a function that listens for signals coming from
// the server process and manages each of the states of the client process.
static void	ft_status_manager(int nPID, char *sBinary)
{
	struct sigaction	s_act4signal;

	s_act4signal.sa_sigaction = &ft_sig_trigger;
	s_act4signal.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &s_act4signal, NULL) == -1
		|| sigaction(SIGUSR2, &s_act4signal, NULL) == -1)
		ft_msg_2(1, nPID, sBinary, NULL);
	if (g_status == 1)
		ft_msg_2(0, nPID, sBinary, NULL);
	else if (g_status == 3)
		ft_msg_1(2, nPID, NULL, sBinary);
}

//Main function of the client process, which expects to receive two input
// parameters: the server process's PID and the message to transmit."
int	main(int nInputs, char **vInputs)
{
	int					v_pidsrv;
	char				*p_msg2bin;

	p_msg2bin = NULL;
	if (nInputs == 3 && ft_pid_checker(vInputs[1]))
	{
		v_pidsrv = ft_atoi(vInputs[1]);
		if (v_pidsrv >= 100 && v_pidsrv <= 99998)
		{
			p_msg2bin = ft_buffer_creator((8 * (ft_strlen(vInputs[2])
							+ 1)), '0');
			ft_msg_converter(&p_msg2bin, vInputs[2]);
			ft_putstr_fd(COLOR_BRIGHT_YELLOW, 1);
			ft_printf("\nBinary message/Long-number bits->"
				" %s/%d\n\n", p_msg2bin, ft_strlen(p_msg2bin));
			ft_msg_transfer(v_pidsrv, p_msg2bin);
			while (1)
			{
				ft_status_manager(v_pidsrv, p_msg2bin);
				pause();
			}
		}
	}
	ft_msg_1(0, 0, NULL, NULL);
	return (0);
}

//END