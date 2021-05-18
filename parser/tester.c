#include "parser.h"

int nb_of_tests = 0;
char **myenv;

static int	ft_strcmp(char *s1, char *s2)
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

static void semicolon_tester()
{
	printf("---SEMICOLONS TESTER---\n");
	char 	valid_cmds[50][100] = 
	{
		"echo bonjour",
		"echo ; ",
		"echo \" ; \" ; echo",
		"echo ' ; ' ; echo",
		"\"ech\"o bonjour ; echo salut",
		"\\; echo salut",
		"echo \\; salut \"salut ;\" \'salut;\'\"\" ;"
	};
	char	unvalid_cmds[50][100] =
	{
		"; echo bonjour",
		"echo ; ; salut",
		"echo bonjour ;		;",
		"echo ;; bonjour",
		"echo |     ; echo salut",
		"echo | ;",
		"echo bonjour ; echo > ; echo salut",
		"echo bonjour ; echo >> ; echo salut",
		"echo bonjour ; echo < ; echo salut"
	};
	int i = 0;
	int	nb_of_valids = 7;
	int	nb_of_invalids = 9;
	while ( i < nb_of_valids /*valid_cmds[i]*/)
	{
		if (!semicolons_valid(valid_cmds[i]))
			printf("Should be valid : [%s]\n", valid_cmds[i]);
		i++;
	}
	i = 0;
	while (i < nb_of_invalids /*unvalid_cmds[i]*/)
	{
		if (semicolons_valid(unvalid_cmds[i]))
			printf("Should be unvalid : [%s]\n", unvalid_cmds[i]);
		i++;
	}
	nb_of_tests += nb_of_invalids + nb_of_valids;
}

static void	quotes_tester()
{
	printf("---QUOTES TESTER---\n");
	char 	valid_cmds[50][100] = 
	{
		"echo bonjour",
		"echo \"bonjour\"",
		"echo \'salut\'",
		"echo \"bonjour\' \' \' salut\"",
		"echo \'bonjour \"\"\" salut \'",
		"echo \"\"\"bonjour\"",
		"echo \\\' salut",
		"ec\"ho\" bjr slt",
		"echo \" \' \' \\\" \\\" \\\" \' \' \' \" \'\'"
	};
	char	unvalid_cmds[50][100] =
	{
		"echo \'bonjour\'\'",
		"echo \'",
		"echo \"",
		"echo \' salut \' \'",
		"echo \" salut \" \"",
		"echo \" \' \' \\\" \\\" \\\" \' \' \' \" \'\' \""
	};
	int i = 0;
	int	nb_of_valids = 9;
	int	nb_of_invalids = 6;
	while ( i < nb_of_valids)
	{
		if (!quotes_are_closed(valid_cmds[i]))
			printf("Should be valid : [%s]\n", valid_cmds[i]);
		i++;
	}
	i = 0;
	while (i < nb_of_invalids)
	{
		if (quotes_are_closed(unvalid_cmds[i]))
			printf("Should be unvalid : [%s]\n", unvalid_cmds[i]);
		i++;
	}
	nb_of_tests += nb_of_invalids + nb_of_valids;
}

static void	pipe_tester()
{
	printf("---PIPES TESTER---\n");
	char 	valid_cmds[50][100] = 
	{
		"echo bonjour",
		"echo bonjour |",
		"echo bonjour | echo salut",
		"echo bonjour \\|| echo salut",
		"echo bonjour \\| | echo salut",
		"echo \"bonjour |\" | echo salut",
		"echo \'bonjour |\' | echo salut"
	};
	char	unvalid_cmds[50][100] =
	{
		"| echo bonjour",
		"echo bonjour || echo salut",
		"echo bonjour ||",
		"echo bonjour || echo salut",
		"echo bonjour ; | echo salut",
		"echo bonjour > | echo salut",
		"> | echo salut"
	};
	int i = 0;
	int	nb_of_valids = 7;
	int	nb_of_invalids = 7;
	while (i < nb_of_valids)
	{
		if (!pipes_valid(valid_cmds[i]))
			printf("Should be valid : [%s]\n", valid_cmds[i]);
		i++;
	}
	i = 0;
	while (i < nb_of_invalids)
	{
		if (pipes_valid(unvalid_cmds[i]))
			printf("Should be unvalid : [%s]\n", unvalid_cmds[i]);
		i++;
	}
	nb_of_tests += nb_of_invalids + nb_of_valids;
}

static void	unesc_char_tester()
{
	int ret;
	char *str;

	printf("---UNESC CHAR TESTER---\n");
	str = "ceci \\\\\\; test";	// 3
	ret = is_unesc_char(&str[8], 8);
	if (ret != 0)
		printf("error with str : %s\n", str);

	str = "ceci \\\\\\\\; test";	// 4
	ret = is_unesc_char(&str[9], 9);
	if (ret != 1)
		printf("error with str : %s\n", str);

	str = "ceci \\\\\\\\\\\\\\\\\\\\\\\\; test";	// 12	
	ret = is_unesc_char(&str[17], 17);
	if (ret != 1)
		printf("error with str : %s\n", str);

	str = "ceci \\; test";	// 1
	ret = is_unesc_char(&str[6], 6);
	if (ret != 0)
		printf("error with str : %s\n", str);

	str = "; test";	// 0
	ret = is_unesc_char(&str[0], 0);
	if (ret != 1)
		printf("error with str : %s\n", str);

	str = "\\; test";	// 1
	ret = is_unesc_char(&str[1], 1);
	if (ret != 0)
		printf("error with str : %s\n", str);

	str = "\\\\; test";	// 2
	ret = is_unesc_char(&str[2], 2);
	if (ret != 1)
		printf("error with str : %s\n", str);

	nb_of_tests += 7;
}

static void gnw_tester()
{
	char	*word;
	t_pars	p;
	printf("---GNW TESTER---\n");
	
	p.i = 5;
	word = get_next_word("ceci est test", &p, NULL);
	if (ft_strcmp(word, "est"))
		printf("Error test 1 ; word is [%s]\n", word);

	p.i = 9;
	word = get_next_word("ceci est ungros>test", &p, NULL);
	if (ft_strcmp(word, "ungros"))
		printf("Error test 2 ; word is [%s]\n", word);

	p.i = 9;
	word = get_next_word("ceci est ungros<test", &p, NULL);
	if (ft_strcmp(word, "ungros"))
		printf("Error test 3 ; word is [%s]\n", word);

	p.i = 9;
	word = get_next_word("ceci est ungros;test", &p, NULL);
	if (ft_strcmp(word, "ungros"))
		printf("Error test 4 ; word is [%s]\n", word);

	p.i = 9;
	word = get_next_word("ceci est ungros|test", &p, NULL);
	if (ft_strcmp(word, "ungros"))
		printf("Error test 5 ; word is [%s]\n", word);

	p.i = 0;
	word = get_next_word("ceci\\ est un test", &p, NULL);
	if (ft_strcmp(word, "ceci est"))
		printf("Error test 6 ; word is [%s]\n", word);

	p.i = 5;
	word = get_next_word("ceci \\\"est test" , &p, NULL);
	if (ft_strcmp(word, "\"est"))
		printf("Error test 7 ; word is [%s]\n", word);

	p.i = 5;
	word = get_next_word("ceci \\;est test" , &p, NULL);
	if (ft_strcmp(word, ";est"))
		printf("Error test 8 ; word is [%s]\n", word);

	p.i = 0;
	word = get_next_word("\\<ceci \\;est test" , &p, NULL);
	if (ft_strcmp(word, "<ceci"))
		printf("Error test 9 ; word is [%s]\n", word);

	p.i = 5;
	word = get_next_word("ceci      etretest" , &p, NULL);
	if (ft_strcmp(word, "etretest"))
		printf("Error test 10 ; word is [%s]\n", word);

	p.i = 9;
	word = get_next_word("ceci est ungros$test", &p, NULL);
	if (ft_strcmp(word, "ungros"))
		printf("Error test 11 ; word is [%s]\n", word);

	p.i = 9;
	word = get_next_word("ceci est ungros\\$test", &p, NULL);
	if (ft_strcmp(word, "ungros$test"))
		printf("Error test 12 ; word is [%s]\n", word);

	p.i = 9;
	word = get_next_word("ceci est ungros\\\"test", &p, NULL);
	if (ft_strcmp(word, "ungros\"test"))
		printf("Error test 13 ; word is [%s]\n", word);

	p.i = 3;
	word = get_next_word("var $+salut", &p, NULL);
	if (ft_strcmp(word, "$+salut"))
		printf("Error test 14 ; word is [%s]\n", word);

	p.i = 3;
	word = get_next_word("var $\\+salut", &p, NULL);
	if (ft_strcmp(word, "$+salut"))
		printf("Error test 15 ; word is [%s]\n", word);

	p.i = 3;
	word = get_next_word("var \\+salut", &p, NULL);
	if (ft_strcmp(word, "+salut"))
		printf("Error test 16 ; word is [%s]\n", word);

	p.i = 8;
	word = get_next_word("var \\\\\\\\;salut", &p, NULL);
	if (ft_strcmp(word, ""))
		printf("Error test 17 ; word is [%s]\n", word);

	p.i = 4;
	word = get_next_word("var $+ test", &p, NULL);
	if (ft_strcmp(word, "$+"))
		printf("Error test 18 ; word is [%s]\n", word);

	p.i = 5;
	word = get_next_word("echo $", &p, NULL);
	if (ft_strcmp(word, "$"))
		printf("Error test 19 ; word is [%s]\n", word);

	p.i = 5;
	word = get_next_word("echo $salut test", &p, NULL);
	if (ft_strcmp(word, NULL))
		printf("Error test 20 ; word is [%s]\n", word);

	nb_of_tests += 20;
}

int main(int argc, char **argv, char **env)
{
	myenv = new_env(env);
	semicolon_tester();
	quotes_tester();
	pipe_tester();
	printf("\n");
	unesc_char_tester();
	gnw_tester();
	printf("\n[%d tests]\n", nb_of_tests);
}