#include "minishell.h"

// static size_t	count_words(char *string, char c)
// {
// 	size_t	index;
// 	size_t	counter;
// 	char	*p;
// 	int		flag;

// 	index = 0;
// 	counter = 0;
// 	p = string;
// 	while (p[index])
// 	{
// 		if (p[index] == c)
// 		{
// 			flag;
// 			counter++;
// 		}
// 		index++;
// 	}
// 	return (counter);
// }

// char	**ft_separator(char *string, char c)
// {
// 	char	**separated;
// 	char	*p;
// 	size_t	index;
// 	size_t	words_quantity;
// 	size_t	w;

// 	p = string;
// 	w = 0;
// 	index = 0;
// 	words_quantity = count_words(string, c);
// 	separated = malloc(sizeof(char *) * words_quantity + 1);
// 	separated[words_quantity] = NULL;
// 	printf("%zu\n", words_quantity);
// 	while (words_quantity + 1 > index)
// 	{
// 		separated[index] = ft_take_word2(string + w);
// 		printf("current el: %s\n", separated[index]);
// 		w += ft_strlen(ft_take_word2(string + w));
// 		index++;
// 	}
// 	print_array(separated);
// 	return (separated);
// }