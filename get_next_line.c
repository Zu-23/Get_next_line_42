/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhaddoum <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:07:57 by zhaddoum          #+#    #+#             */
/*   Updated: 2022/04/12 20:57:45 by zhaddoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdlib.h>
#define BUFFER_SIZE 1

ssize_t	ftstrlen(char *str)
{
	ssize_t	c;

	c = 0;
	if (str == NULL)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

void	treat_line(char **line_addr, char *buf, ssize_t end, ssize_t start)
{
	char	*tmp;
	ssize_t	len;
	ssize_t	i;

	i = -1;
	len = ftstrlen(*line_addr);
	tmp = (char *) malloc(len + end - start + 1);
	if (!tmp)
		return ;
	while (++i < len)
		tmp[i] = (*line_addr)[i];
	free(*line_addr);
	len = start;
	while (len < end)
		tmp[i++] = buf[len++];
	tmp[i] = '\0';
	*line_addr = tmp;
	if (i == 0)
	{
		free(*line_addr);
		*line_addr = NULL;
	}
}

int	read_buf(int fd, char *buf, ssize_t	buf_size, ssize_t i)
{
	ssize_t	r;

	if (i == 0)
	{
		r = read(fd, buf, buf_size);
		if (r == -1)
			return (-1);
		else if (r < buf_size)
			buf[r] = '\0';
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static ssize_t	index;
	ssize_t			i;
	static char		buf[BUFFER_SIZE];
	char			*line;

	line = NULL;
	i = index;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (i == BUFFER_SIZE)
		{
			treat_line(&line, buf, i, index);
			index = 0;
			i = 0;
		}
		if (read_buf(fd, buf, BUFFER_SIZE, i) == -1)
			return (NULL);
		if (buf[i] == '\0' || buf[i++] == '\n')
			break ;
	}
	treat_line(&line, buf, i, index);
	index = i;
	return (line);
}