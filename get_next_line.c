#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
//#define BUFFER_SIZE 1
int ftstrlen(char *str)
{
	int	c;

	c = 0;
	if (str == NULL)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

void	treat_line(char **line_addr, char *buf, int end, int start)
{
	char *tmp;
	int len;
	int i;

	i = -1;
	len = ftstrlen(*line_addr) ;
	tmp = (char*) malloc(len + end - start + 1);

	while (++i < len)
		tmp[i] = (*line_addr)[i];
	free(*line_addr);
	len = start;
	while (len < end )
	{
		tmp[i] = buf[len];
		i++;
		len++;
	}
	tmp[i] = '\0';

	*line_addr = tmp;
    if (i==0)
        *line_addr = NULL;
}

void	read_buf(int fd, char *buf, int buf_size)
{
	int r;

	r = read(fd, buf, buf_size);
	if (r < buf_size)
		buf[r] = '\0';
}
// void	treat_line(char **line_addr, char *buf, int ndx)
// {
// 	char *tmp;
// 	int	len;
// 	int	c;
	
// 	c = 0;
// 	len = ftstrlen(*line_addr);
// 	tmp = (char*)malloc(len + ndx + 1);
// 	if (len != 0)
// 	{
// 		len = 0;
// 		while (*line_addr[len] != '\0')
// 		{
// 			tmp[len] = *line_addr[len];
// 			len++;
// 		}
// 		//*line_addr = NULL;
// 		while (c <= ndx)
// 		{
// 			tmp[len] = buf[c];
// 			len++;
// 			c++;
// 		}
// 		line_addr = &tmp;
// 	}
// 	else
// 	{
// 		while(len <= ndx)
// 		{
// 			tmp[len] = buf[len];
// 			len++;
// 		}
// 		line_addr = &tmp;
// 	}
// }

char *get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static int		index;
	char			*line;
	static int		i;
	line = NULL;

	i = index;
	while (1)
	{
		if (i == BUFFER_SIZE)
		{
			treat_line(&line,buf,i,index);
			index = 0;
			i = 0;
		}
		if (i == 0)
			read_buf(fd,buf,BUFFER_SIZE);
		if (buf[i] == '\0' || buf[i++] == '\n')
			break;
	}
	treat_line(&line,buf,i,index);
	index = i;
	return (line);
}