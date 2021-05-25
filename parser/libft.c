#include "parser.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if ((!s1 && s2) || (s1 && !s2))
		return (1);
	while (s1[i] != 0 && s2[i] != 0)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str_cat;
	int		i;
	int		j;

	if (s1 == NULL)
		s1 = ft_strdup("");
	if (s2 == NULL)
		s2 = ft_strdup("");
	str_cat = malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (!str_cat)
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
