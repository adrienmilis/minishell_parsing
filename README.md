# minishell

## Syntax rules

### Quotes

Single-quotes ( '' ):  shall preserve the literal value of each character within the single-quotes. A single-quote cannot occur within single-quotes. If uneven number of single quotes, unvalid command. Even env variables stay as strings.

Double-quotes (“”): 

- the $ shall retain its special meaning introducing parameter expansion.
- The \ shall retain its special meaning, only when followed by one of the following characters when considered special : $ “ \ 
- si plusieurs double-quotes a la suite, concatener leur resultat. (ex : echo """salut" = echo "" + echo "salut")

Quotes can be anywhere in the command (in the exec, options or arguments)

### Redirections

- Redirections can be placed anywhere in the command. Then, it only takes the next argument as the file used for the redirection.
The other arguments are arguments to the command
- If there are several redirections in a row, all files are created (if forward redirection). However, the redirection goes only to the last file
(ex : echo bonjour > file1 >file2 >> file3)
- The argument to a redirection can be delimited by whitespaces, another redirection operator, pipes or semi-colons

### $ (env variables)

- Variables can only be a set of alphanumeric characters and _ . If an env variable is followed by a character other than this one, 

### Possible errors

#### Quotes

- Quotes are unclosed (either ' or ")

#### Semicolons (;)

- Before any character other than a whitespace (beginning of the command)
- Two or more in a row (even separated by whitespaces)

#### Pipes (|)

#### Redirections (<, >, >>)

- Input redirection from a file that doesn't exist

### Parsing



## Method (so far)

1) Check if command can be splitted (first, quotes are closed, then check semi-colons)
2) Split the command on the right semi-colons
3) Go through each sub_command
4) 2 modes : in & out of quotes. 
- if double quotes : expand environment variables
- if in simple quotes : pass
- else, check if pipes and redirections are valid
