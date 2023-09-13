/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:07:42 by abelayad          #+#    #+#             */
/*   Updated: 2023/02/15 20:50:51 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_n_return(char	**ptr, char *to_ret)
{
	free(*ptr);
	*ptr = NULL;
	return (to_ret);
}

int	ft_got_line(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_line(char *acc_str, char (*buff)[BUFFER_SIZE + 1])
{
	size_t	i;
	size_t	j;
	char	*line;

	if (!acc_str)
		return (NULL);
	i = 0;
	while (acc_str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1 + 1));
	if (!line)
		return (free(acc_str), NULL);
	j = 0;
	while (j < i + 1)
	{
		line[j] = acc_str[j];
		j++;
	}
	line[j] = 0;
	j = 0;
	while (acc_str[i++])
		(*buff)[j++] = acc_str[i];
	while (j < BUFFER_SIZE + 1)
		(*buff)[j++] = 0;
	return (free(acc_str), line);
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE + 1];
	char			*acc_str;
	ssize_t			read_sig;

	acc_str = ft_strjoin(buff, "");
	if (!acc_str)
		return (NULL);
	while (!ft_got_line(acc_str))
	{
		read_sig = 0;
		while (read_sig < BUFFER_SIZE + 1)
			buff[read_sig++] = 0;
		read_sig = read(fd, buff, BUFFER_SIZE);
		if (read_sig < 0 || (!ft_strlen(buff) && !ft_strlen(acc_str)))
			return (ft_free_n_return(&acc_str, NULL));
		if (!read_sig)
			return (ft_free_n_return(&acc_str, ft_strjoin(acc_str, buff)));
		acc_str = ft_free_n_return(&acc_str, ft_strjoin(acc_str, buff));
		if (!acc_str)
			return (NULL);
	}
	return (ft_get_line(acc_str, &buff));
}
