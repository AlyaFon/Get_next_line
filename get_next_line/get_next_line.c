/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omtekbas < omtekbas@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:29:00 by omtekbas          #+#    #+#             */
/*   Updated: 2023/02/17 03:28:23 by omtekbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*storage(char *mybase, int fd)
{
	char	*temp_buffer;
	char	*temp2;
	int		rs;

	rs = 1;
	temp_buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	while (!ft_strchr(temp_buffer, '\n') && rs != 0)
	{
		rs = read(fd, temp_buffer, BUFFER_SIZE);
		if (rs == -1)
		{
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[rs] = '\0';
		if (!mybase)
			mybase = ft_strdup("");
		temp2 = mybase;
		mybase = ft_strjoin(temp2, temp_buffer);
	}
	free(temp_buffer);
	return (mybase);
}

char	*pull_my_line(char *mybase)
{
	char	*line;
	int		i;

	i = 0;
	if (!mybase[i])
		return (NULL);
	while (mybase[i] && mybase[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (mybase[i] && mybase[i] != '\n')
	{
		line[i] = mybase[i];
		i++;
	}
	if (mybase[i] == '\n')
	{
		line[i] = mybase[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*seperate(char *mybase)
{
	char	*my_new_base;
	int		rn;
	int		i;

	rn = 0;
	i = 0;
	while (mybase[rn] && mybase[rn] != '\n')
		rn++;
	if (!mybase[rn])
	{
		free(mybase);
		return (NULL);
	}
	my_new_base = (char *)malloc(sizeof(char) * ft_strlen(mybase) - rn + 1);
	if (!my_new_base)
		return (NULL);
	rn++;
	while (mybase[rn])
		my_new_base[i++] = mybase[rn++];
	my_new_base[i] = '\0';
	free(mybase);
	return (my_new_base);
}

char	*get_next_line(int fd)
{
	static char	*mybase;
	char		*line;

	if (!((BUFFER_SIZE > 0) || fd >= 0))
		return (NULL);
	mybase = storage(mybase, fd);
	if (!mybase)
		return (NULL);
	line = pull_my_line(mybase);
	mybase = seperate(mybase);
	return (line);
}



/*
int main()
{
	int a = open("get_next_line.c", O_RDONLY, 0644);
	char *b ;
	b = get_next_line(a);
	while(b)
	{
		printf("%s",b);
		b = get_next_line(a);
	}
	return 0;
}*/

int main()
{
	int fd = open("get_next_line.c", O_RDONLY, 0644);
	char *str = get_next_line(fd);
	printf("%s", str);
	str = get_next_line(fd);
	printf("%s", str);
	close(fd);
}