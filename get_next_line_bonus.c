/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-eyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:37:45 by mvan-eyn          #+#    #+#             */
/*   Updated: 2019/10/07 13:37:47 by mvan-eyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_free(char **str, int k)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (k);
}

char	*ft_find_dup(const char *src, const char a)
{
	int		i;
	char	*new_str;

	i = 0;
	if (src == NULL)
		return (ft_find_dup("", '\0'));
	while (src[i] != a)
		i++;
	new_str = malloc((i + 1) * sizeof(char*));
	if (new_str == 0)
		return (0);
	i = 0;
	while (src[i] && src[i] != a)
	{
		new_str[i] = src[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int		ft_read(int fd, char **line, char *reste)
{
	int		ret;
	char	buf[BUFFER_SIZE + 1];
	char	*temp;

	if (reste != NULL)
		if ((*line = ft_find_dup(reste, '\0')) == NULL)
			return (ft_free(&reste, -1));
	if (reste == NULL)
		if ((*line = ft_find_dup("", '\0')) == NULL)
			return (-1);
	while ((ft_strchr(*line, '\n') == NULL) &&
	(ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		temp = *line;
		buf[ret] = '\0';
		if ((*line = ft_strjoin(*line, buf)) == NULL)
			return (ft_free(&reste, -1));
		ft_free(&temp, 1);
	}
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	int				ret;
	static char		*reste[FOPEN_MAX];
	char			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if ((ret = ft_read(fd, line, reste[fd])) == -1)
		return (ft_free(&reste[fd], -1));
	if (reste[fd] != NULL)
		ft_free(&reste[fd], 1);
	if ((reste[fd] = ft_find_dup(ft_strchr(*line, '\n'), '\0')) == NULL)
		return (ft_free(&reste[fd], -1));
	if (ft_strchr(*line, '\n') == NULL)
		return (ft_free(&reste[fd], 0));
	temp = *line;
	if ((*line = ft_find_dup(*line, '\n')) == NULL)
		return (ft_free(&reste[fd], -1));
	free(temp);
	temp = NULL;
	return (1);
}
