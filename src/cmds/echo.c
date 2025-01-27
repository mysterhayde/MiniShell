#include "../../include/minishell.h"

/**
 * @brief Writes str to std output with the option to 
 * @param t_bool newline - TRUE=print "\n" FALSE=dont print "\n"
 * @param char *str - String to print
 * @returns 1 on success 0 on fail
 */
int	echo(t_bool newline, char *str)
{
	int	ret;

	ret = 0;
	if (newline)
		ret += ft_printf("%s", str);
	ret += ft_printf("\n");
	if (ret == 0)
		return (1);
	return (0);
}
