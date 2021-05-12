# minishell

## Syntax rules

### Possible errors ('' and "")

#### Quotes

- Quotes are unclosed (either ' or ")

#### Semicolons (;)

- Before any character other than a whitespace (beginning of the command)
- Two or more in a row (even separated by whitespaces)

#### Pipes (|)

#### Redirections (<, >, >>)



## Method (so far)

1) Check if command can be splitted (first, quotes are closed, then check semi-colons)
2) Split the command on the right semi-colons
3) Go through each sub_command
4) 2 modes : in & out of quotes. 
- if double quotes : expand environment variables
- if in simple quotes : pass
- else, check if pipes and redirections are valid
