#include "../minishell.h"

int		open_file(char type, int r_type, char **filename)
{
	int		fd;

	fd = -1;
	if (type == '>')
	{
		if (r_type == 2)
			fd = open(*filename, O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (r_type == 1)
			fd = open(*filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else
		fd = open(*filename, O_RDWR, 0644);
	free(*filename);
	return (fd);
}

void	move_pointer_to(char **p, char c)
{
	char	*pp;

	pp = *p;
	if (ft_strlen(*p))
		while (*pp && *pp != c)
			pp++;
	*p = pp;
}

char	*determine_filename(char **p, size_t *index, char type, int *r_type)
{
	size_t	kc;
	char	*tmp;
	char	*filename;
	size_t	i;
	char	*pp;

	*r_type = 0;
	kc = 0;
	i = *index;
	pp = *p;
	while (pp[i] == ' ' || pp[i] == type)
	{
		if (pp[i] == type)
		{
			*r_type += 1;
			kc++;
		}
		i += 1;
	}
	*index = i;
	tmp = pp;
	*p = ft_substr(*p, kc, ft_strlen(*p));
	filename = ft_take_word(p);
	return (filename);
}