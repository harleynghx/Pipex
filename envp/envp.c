#include <stdio.h>
#include "pipexHeader.h"
#include "libft/libft.h"

void    all(char **envp);
void    path(char **envp);
void    split(char **envp);

int main(int argc, char **argv, char **envp){

    if(argc > 0){
        if (strncmp(argv[1], "all", 3) == 0)
            all(envp);
        else if(strncmp(argv[1], "path", 4) == 0)
            path(envp);
        else if (strncmp(argv[1], "split", 5) == 0)
            split(envp);
    }
    return(0);
}
void    all(char **envp){
    int i = 0;
    while (envp[i] != NULL){
        printf("%s\n", envp[i]);
        i++;
    }
    return ;
}
void    path(char **envp){
    int i = 0;

    while(strnstr(envp[i], "PATH", 4) == 0)
        i++;
    printf("%s", envp[i]);
    return ;
}
void    split(char **envp){
    int i = 0;

    while(strnstr(envp[i], "PATH", 4) == 0)
        i++;
    char **temp = ft_split(envp[i], ':');
    i = 0;
    while (temp[i] != NULL)
        printf("%s\n", temp[i++]);
    return ;
}
static int	is_sep(char c, char set)
{
	if (c == set)
		return (1);
	return (0);
}

static int	word_count(char const *str, char set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_sep(str[i], set))
			i++;
		if (str[i] && !is_sep(str[i], set))
			count++;
		while (str[i] && !is_sep(str[i], set))
			i++;
	}
	return (count);
}

static char	*fill_letters(char const *str, char set)
{
	char	*newstr;
	int		i;

	i = 0;
	while (!is_sep(str[i], set) && str[i])
		i++;
	newstr = malloc(sizeof(char) * (i + 1));
	if (!newstr)
		return (0);
	i = 0;
	while (!is_sep(str[i], set) && str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	**ft_split(char const *s, char set)
{
	char	**split_str;
	int		count;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	count = word_count(s, set);
	split_str = malloc(sizeof(char *) * (count + 1));
	if (!split_str)
		return (0);
	while (*s)
	{
		while (*s && is_sep(*s, set))
			s++;
		if (*s)
		{
			split_str[i] = fill_letters(s, set);
			i++;
			while (*s && !is_sep(*s, set))
				s++;
		}
	}
	split_str[i] = 0;
	return (split_str);
}