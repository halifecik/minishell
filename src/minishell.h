/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:51:40 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:51:41 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// <stddefs.h>
# include "utils/string_utils.h"
// bool
# include <stdbool.h>
// pid_t
# include <sys/types.h>

/*	MAIN_SRC	*/
//variable_declarations.c
t_list	**get_cmd_list(void);
char	**get_input(void);
char	**get_prompt(void);
char	*pwd_variable(void);
//error_calls.c
void	free_resources_and_exit(t_uint8 exit_code);
t_uint8	error_malloc(void);
//prompt functions
char	*set_hostname(void);
char	*set_prompt(void);
void	free_full_prompt(void);
//syntax_check_valid.c
char	*syntax_check_valid(char *input);
//read_input.c
void	read_input(void);
//exit_status_code.c
void	set_exit_status_code(t_uint8 status_code);
t_uint8	get_exit_status_code(void);

/*	PARSER_SRC	*/
//static_fd_variables.c
int		*get_prev_pipe_read(void);
void	close_prev_pipe_read(void);
int		*get_fd_redirection(void);
void	copy_fd_redirection(int rd_number);
void	reset_fd_redirection(void);
//node_sub_parser.c
char	*sub_parser(char **input);
//check_redirections.c
void	check_redirections(char **end, char **start);
//parse_here_document.c
int		here_document_read(char **end);
//parse_operators.c
void	check_pipe(char **end, char **start);
//parse_environ.c
void	check_environ(char **end, char **start, char in_quotes);
//parse_quotes.c
void	check_quotes(char **end, char **start);
//parse_string.c
bool	*inside_word(void);
char	*parse_string(char *input);
//parse_utils.c
void	break_parse(char **end);
void	error_syntax(char **end, char *token);
void	error_redirection(char **end, char *str);

/*	BUILTIN_SRC	*/
//builtin commands
void	command_exit(void);
void	command_env(void);
void	command_unset(void);
void	command_export(t_list *cmd_list);
void	command_pwd(void);
void	command_cd(t_list *args);
void	command_echo(t_list *args);

/*	EXECUTE_SRC	*/
//command_calls.c
void	command_calls(t_list **cmd_list, char is_forked);
//command_utils.c
void	check_wait_status(pid_t pid);
t_uint8	error_child(char *cmd, char mode);
void	error_syscall(char *msg, char **end);
//command_execute.c
void	command_execute(char is_forked);
//command_execute_pipeline.c
void	create_child_process(char **end);
void	create_last_child_process(char **end);

/*	ENVIRON_SRC	*/
//environ_set.c
void	environ_set(void);
void	environ_destroy(void);
//environ_append.c
void	environ_append(char *str);
//environ_remove.c
void	environ_remove(char *str);

/*	BONUS_SRC	*/
//wildcard_utils_bonus.c
void	free_entries(char **entries, char **end);
char	**resolve_dir_name(char **end);
//wildcard_insert_bonus.c
char	insert_dirs_to_list(char **dirs, char *prefix, char *suffix);
//parse_wildcard_bonus.c
void	check_wildcard(char **end, char **start);
//parse_parenthesis_bonus.c
void	check_parentheses(char **end, char **start);
//parse_operators_bonus.c
void	check_operator_or(char **end, char **start);
void	check_operator_and(char **end, char **start);

#endif
