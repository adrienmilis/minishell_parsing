#include "parser.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str_cat;
	int		i;
	int		j;

	if (s1 == NULL)
		s1 = ft_strdup("");
	if (s2 == NULL)
		s2 = ft_strdup("");
	if (!(str_cat = malloc((ft_strlen((char*)s1) +
			ft_strlen((char*)s2) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str_cat[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str_cat[i++] = s2[j++];
	str_cat[i] = '\0';
	free(s1);
	free(s2);
	return (str_cat);
}

char	*ft_strdup_len(char *str, int len)
{
	char	*str_cpy;
	int		i;

	i = 0;
	str_cpy = malloc((len + 1) * sizeof(char));
	if (str_cpy == NULL)
		return (NULL);
	while (i < len)
	{
		str_cpy[i] = str[i];
		i++;
	}
	str_cpy[i] = '\0';
	return (str_cpy);
}

char	*ft_strdup(char *str)
{
	char	*str_cpy;
	int		str_len;
	int		i;

	i = 0;
	str_len = ft_strlen(str);
	str_cpy = malloc((str_len + 1) * sizeof(char));
	if (str_cpy == NULL)
		return (NULL);
	while (i < str_len)
	{
		str_cpy[i] = str[i];
		i++;
	}
	str_cpy[i] = '\0';
	return (str_cpy);
}

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_letter(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	valid_var_char(char c)
{
	if (is_number(c) || is_letter(c) || c == '_' || c == '?')
		return (1);
	return (0);
}