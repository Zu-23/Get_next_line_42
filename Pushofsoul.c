#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#define BUFFER_SIZE 5
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
	int len ;
	int i;

	i = -1;
	len = ftstrlen(*line_addr) ;
	tmp = (char*) malloc(len + end - start + 1);

	while (++i < len)
		tmp[i] = (*line_addr)[i];
	len = 0;
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
	static char		*buf;
	static int		index;
	char			*line;
	int				i;
	printf("inside get next line and value of fd %d\n",fd);
	line = NULL;
	//buf = NULL;

	while (1)
	{
		if (index != 0 && index < BUFFER_SIZE)
			treat_line(&line, buf, BUFFER_SIZE, index);
		index = 0;
		i = read(fd, buf, BUFFER_SIZE);
		printf("the value of i = read: %d\n", i);
		if (i >= BUFFER_SIZE)
		{
			printf("inside i>= buff");
			i = 0;
			while (i <= BUFFER_SIZE)
			{
				if (buf[i] == '\n')
				{
					index = i;
					treat_line(&line, buf, i, 0);
					return (line);
				}
				i++;
			}
			printf("the buf: %s\n",buf);
		treat_line(&line, buf, i, 0);
		}
		else
		{
			printf("\n im in else");
			treat_line(&line, buf, i, 0);
			return (line);
		}
	}
}

// int main()
// {
//     int fd ;

//     fd = open( "text.txt", O_RDONLY | O_CREAT );
//     char * str = get_next_line( fd );
//     while ( str )
//      {
//          printf( "%s", str );
//          str = get_next_line( fd );
//     }

//     printf( "EOF\n" );
//     return 0;
// }