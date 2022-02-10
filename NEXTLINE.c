#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int len( char * str );
void append_from_buffer( char ** dest, char * buf, int start, int end );
void update_buff( int fd, char * buf, int buf_size, int index );
char * get_next_line( int fd );

int main()
{
    int fd ;

    fd = open( "text.txt", O_RDONLY | O_CREAT );

    char * str = get_next_line( fd );
    while ( str )
     {
         printf( "%s", str );
         str = get_next_line( fd );
    }

    printf( "EOF\n" );
    return 0;
}

int len( char * str )
{
	int length;
	length = 0;

	if ( str == NULL )
		return 0;

	while ( str[length] )
		length++;

	return length;
}

void append_from_buffer( char ** dest, char * buf, int start, int end )
{
	char * tmp;
	int prev_len ;
	int i;

	i = -1;
	prev_len = len( *dest ) ;
	tmp = (char*) malloc( prev_len + end - start + 1 );

	while ( ++i < prev_len )
		tmp[i] = (*dest)[i];

	free( *dest );

	while ( i < prev_len + end - start )
	{
		tmp[i] = buf[ start + i - prev_len ];
		i++;
	}
	tmp[ i ] = '\0';
	*dest = tmp;
    if (i==0)
        *dest = NULL;
}

void update_buff( int fd, char * buf, int buf_size, int index )
{
	int r;

	if ( index == 0 )
	{
		r = read(fd, buf, buf_size);
		if ( r < 0 )
			r = 0;
		else if ( r < buf_size )
			buf[ r ] = '\0';
	}
}

char * get_next_line(int fd)
{
	static	char		buf[BUFF_SIZE];
	char				*line;
	static int			start_index;
	int i;

	i = start_index;
	line = NULL;
	
	while ( 1 )
	{
		if ( i >= BUFF_SIZE )
		{
			append_from_buffer( &line , buf, start_index , BUFF_SIZE);
			i = 0;
			start_index = 0;
		}
		update_buff( fd, buf, BUFF_SIZE, i );
		if ( buf[i] == '\0' )
			break;
		if ( buf[i++] == '\n' )
			break;
	}
	append_from_buffer( &line , buf, start_index , i);
    start_index = i;
	return line;
}
