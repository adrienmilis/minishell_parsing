# minishell parser

Parses shell commands and returns a linked list for execution of said commands.

Syntax rules include single quotes, double quotes, semicolons, environment variables, pipes, redirections (<, >, >>)

## Syntax rules

### Quotes

Single-quotes ( '' ):  shall preserve the literal value of each character within the single-quotes. A single-quote cannot occur within single-quotes. If uneven number of single quotes, unvalid command. Even env variables stay as strings.

Double-quotes (“”): 

- the $ shall retain its special meaning introducing parameter expansion.
- The \ shall retain its special meaning, only when followed by one of the following characters when considered special : $ “ \ 

Si plusieurs quotes (double ou simple) a la suite, concatener leur resultat. (ex : echo """salut" = echo "" + echo "salut")

Quotes can be anywhere in the command (in the exec, options or arguments)

### Redirections

- Redirections can be placed anywhere in the command. Then, it only takes the next argument as the file used for the redirection.
The other arguments are arguments to the command
- If there are several redirections in a row, all files are created (if forward redirection). However, the redirection goes only to the last file
(ex : echo bonjour > file1 >file2 >> file3)
- The argument to a redirection can be delimited by whitespaces, another redirection operator, pipes or semi-colons
- If there is an input redirection AND a pipe, the input redirection wins
- It's ok if there is no space between an argument and a redirection (echo salut>salut)

### $ (env variables)

- Variables can only be a set of alphanumeric characters and _ . If an env variable is followed by a character other than those, the expanded variable
and whatever is after are concatenated
- If the specified environment variable doesn't exist, it is ignored (not replaced by an empty string)

### Built-ins and executables

- They are not case-sensitive

### Other

- Spaces that are escaped (\ ) are not considered argument separators, but simply characters
- Always print a space between two arguments, even if one of the arguments is an empty string

### Possible errors

#### Quotes

- Quotes are unclosed (either ' or ")

#### Semicolons (;)

- Before any character other than a whitespace (beginning of the command)
- Two or more in a row (even separated by whitespaces)

#### Pipes (|)

- No pipe at the beginning or end of a command (even with whitespaces)
- Two or more in a row (even separated by whitespaces)
- No pipe right after a semicolon

#### Redirections (<, >, >>)

- Input redirection from a file that doesn't exist



