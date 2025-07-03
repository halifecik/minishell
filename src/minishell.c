#include "minishell.h"

int	main(void)
{
	environ_set();
	while (1)
	{
		read_input();
		parse_string(*get_input());
		command_calls(get_cmd_list(), 0);
		node_destroy_list(get_cmd_list());
	}
	return (0);
}
