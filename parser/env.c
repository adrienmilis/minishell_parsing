#include "parser.h"

int        strcmp_env(char *s1, char *s2)
{
    size_t            i;
    unsigned char    last_char_s1;
    unsigned char    last_char_s2;

    i = 0;
    while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    last_char_s1 = s1[i];
    last_char_s2 = s2[i];
    if (last_char_s1 == '=')
        last_char_s1 = '\0';
    if (last_char_s2 == '=')
        last_char_s2 = '\0';
    return (last_char_s1 - last_char_s2);
}

static size_t	strtablen(char **tab)
{
	size_t	res;

	res = 0;
	if (!tab)
		return (0);
	while (tab[res])
		res++;
	return (res);
}

static char	**free_strtab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	**new_env(char **env)
{
	char	**res;
	size_t	i;

	res = malloc((strtablen(env) + 2) * sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = ft_strdup("?=0");
	if (!res[0])
		return (free_strtab(res));
	i = 0;
	while (env[i])
	{
		res[i + 1] = ft_strdup(env[i]);
		if (!res[i + 1])
			return (free_strtab(res));
		i++;
	}
	res[i + 1] = NULL;
	return (res);
}