#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <readline/readline.h> 
#include <readline/history.h> 

void	free_resources_and_exit(t_uint8 exit_code)
{
	environ_destroy();
	node_destroy_list(get_cmd_list());
	free(*get_input());
	free_full_prompt();
	free(pwd_variable());
	rl_clear_history();
	close_prev_pipe_read();
	exit(exit_code);
}

t_uint8	error_malloc(void)
{
	write(STDERR_FILENO, "minishell: system failed to allocate memory\n", 44);
	set_exit_status_code(1);
	return (1);
}
