#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
readline, 
rl_clear_history, 
rl_on_new_line,
rl_replace_line, 
rl_redisplay, 
add_history,
*/
int main(void)
{
    char    *line;
	using_history();
	while (1)
	{
		line = readline("minishell-0.1$ ");
		rl_replace_line();
		if (line && *line)
			add_history(line);
		free(line);
	}
    return (0);
}
