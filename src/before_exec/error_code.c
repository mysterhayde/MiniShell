/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:10:28 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/25 17:16:30 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Expands the error code variable ($?) in a string
 * @param str String containing $?
 * @param return_code The return code to insert
 * @return New string with expanded error code
 */
char	*expand_error_code(char *str, int return_code)
{
	char	*error_code;
	char	*new_str;

	error_code = ft_itoa(return_code);
	if (!error_code)
		return (NULL);
	new_str = ft_strjoin(error_code, str + 2);
	free(error_code);
	if (!new_str)
		return (NULL);
	return (new_str);
}

/**
 * @breif Creates a new string with error code expanded at position i
 * @param str Original string
 * @param i Poisition of $? in the string
 * @param return_code Return code to insert
 * @return New string with error code expanded
 */
char	*replace_error_code(char *str, int i, int return_code)
{
	char	*temp;
	char	*expanded;
	char	*new_str;

	expanded = expand_error_code(str + i, return_code);
	if (!expanded)
		return (free(str), NULL);
	temp = ft_substr(str, 0, i);
	if (!temp)
		return (free(str), free(expanded), NULL);
	new_str = ft_strjoin(temp, expanded);
	free(temp);
	free(expanded);
	if (!new_str)
		return (free(str), NULL);
	free(str);
	return (new_str);
}

/**
 * @brief Searches for error code variable ($?) in a string and expands it
 * @param return_code The return code to insert
 * @param str String to search in
 * @return New string with all error codes expanded
 */
char	*search_error_code(int return_code, char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += (skip_until_next_quote(str, str[i], i) - 1);
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			new_str = replace_error_code(str, i, return_code);
			return (search_error_code(return_code, new_str));
		}
		i++;
	}
	return (str);
}
