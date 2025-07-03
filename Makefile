# ==================== #
#    Color Settings    #
# ==================== #
BOLD        = \033[1m
RED         = \033[31m
GREEN       = \033[32m
YELLOW      = \033[33m
BLUE        = \033[34m
CYAN        = \033[36m
RESET       = \033[0m

# ====================== #
#    Compiler & Flags    #
# ====================== #
CC          = cc
C_FLAGS     = -Wall -Wextra -Werror -Isrc
RL_FLAGS    = -lreadline -lhistory

SRC_DIR     = src
OBJ_DIR     = obj
BIN_DIR     = bin

# ================= #
#    Directories    #
# ================= #
UTILS_DIREC = $(SRC_DIR)/utils
BUILTIN_DIR = $(SRC_DIR)/builtin
EXECUTE_DIR = $(SRC_DIR)/command
ENVIRON_DIR = $(SRC_DIR)/environ
PARSER_DIR  = $(SRC_DIR)/parser
BONUS_DIR   = $(SRC_DIR)/bonus

# ================================= #
#    Mandatory Part Source Files    #
# ================================= #
UTILS_FILES = $(UTILS_DIREC)/string_utils_char_check.c       \
			  $(UTILS_DIREC)/string_utils_search.c           \
			  $(UTILS_DIREC)/string_utils_copy.c             \
			  $(UTILS_DIREC)/string_utils_malloc.c           \
			  $(UTILS_DIREC)/string_utils_quick_sort.c       \
			  $(UTILS_DIREC)/string_utils_strtok.c           \
			  $(UTILS_DIREC)/string_utils_type_conversions.c \
			  $(UTILS_DIREC)/string_utils_gnl.c              \
			  $(UTILS_DIREC)/node_functions.c

BUILTIN_SRC = $(BUILTIN_DIR)/builtin_commands.c				 \
			  $(BUILTIN_DIR)/builtin_command_cd.c			 \
			  $(BUILTIN_DIR)/builtin_command_export.c		 \
			  $(BUILTIN_DIR)/builtin_command_exit.c

EXECUTE_SRC = $(EXECUTE_DIR)/command_calls.c				 \
			  $(EXECUTE_DIR)/command_utils.c				 \
			  $(EXECUTE_DIR)/command_execute.c				 \
			  $(EXECUTE_DIR)/command_execute_pipeline.c

ENVIRON_SRC = $(ENVIRON_DIR)/environ_set.c					 \
			  $(ENVIRON_DIR)/environ_append.c				 \
			  $(ENVIRON_DIR)/environ_remove.c

PARSER_SRC  = $(PARSER_DIR)/parse_string.c					 \
			  $(PARSER_DIR)/parse_quotes.c					 \
			  $(PARSER_DIR)/parse_pipe.c					 \
			  $(PARSER_DIR)/parse_environ.c					 \
			  $(PARSER_DIR)/parse_here_document.c			 \
			  $(PARSER_DIR)/parse_redirections.c			 \
			  $(PARSER_DIR)/parse_utils.c					 \
			  $(PARSER_DIR)/node_sub_parser.c				 \
			  $(PARSER_DIR)/static_fd_variables.c

MAIN_SRC    = $(SRC_DIR)/minishell.c						 \
			  $(SRC_DIR)/static_variables.c					 \
			  $(SRC_DIR)/error_calls.c						 \
			  $(SRC_DIR)/set_prompt.c						 \
			  $(SRC_DIR)/set_hostname.c						 \
			  $(SRC_DIR)/read_input.c						 \
			  $(SRC_DIR)/syntax_check_valid.c				 \
			  $(SRC_DIR)/exit_status_code.c

# ============================= #
#    Bonus Part Source Files    #
# ============================= #

PARSER_BNS  = $(filter-out $(PARSER_DIR)/parse_string.c, $(PARSER_SRC))
MAIN_BNS	= $(filter-out $(SRC_DIR)/syntax_check_valid.c, $(MAIN_SRC))

BONUS_SRC   = $(BONUS_DIR)/parse_string_bonus.c				 \
			  $(BONUS_DIR)/syntax_check_valid_bonus.c		 \
			  $(BONUS_DIR)/parse_parentheses_bonus.c		 \
			  $(BONUS_DIR)/parse_operators_bonus.c			 \
			  $(BONUS_DIR)/wildcard_utils_bonus.c			 \
			  $(BONUS_DIR)/wildcard_insert_bonus.c			 \
			  $(BONUS_DIR)/parse_wildcard_bonus.c

# ============================== #
#    Main & Bonus Source Sets    #
# ============================== #
SRC     	= $(MAIN_SRC)    \
	          $(UTILS_FILES) \
	          $(BUILTIN_SRC) \
	          $(EXECUTE_SRC) \
	          $(ENVIRON_SRC) \
	          $(PARSER_SRC)


BONUS       = $(MAIN_BNS)    \
			  $(UTILS_FILES) \
			  $(BUILTIN_SRC) \
			  $(EXECUTE_SRC) \
			  $(ENVIRON_SRC) \
			  $(PARSER_BNS)  \
			  $(BONUS_SRC)

# ================== #
#    Object Files    #
# ================== #
OBJ         = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/main/%.o)
BONUS_OBJ   = $(BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/bonus/%.o)

# =================== #
#    Output Binary    #
# =================== #
NAME        = $(BIN_DIR)/minishell
NAME_BONUS  = $(BIN_DIR)/bonus/minishell

all:     $(NAME) $(NAME_BONUS)

man:     $(NAME)
bonus:   $(NAME_BONUS)

$(NAME): $(OBJ) | $(BIN_DIR)
	@echo "$(BLUE)Linking mandatory: $(NAME)...$(RESET)"
	$(CC) $(RL_FLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Mandatory: $(NAME) created successfully!$(RESET)"

$(OBJ_DIR)/main/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/main
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME_BONUS): $(BONUS_OBJ) | $(BIN_DIR)/bonus
	@echo "$(BLUE)Linking bonus: $(NAME_BONUS)...$(RESET)"
	$(CC) $(RL_FLAGS) $(BONUS_OBJ) -o $(NAME_BONUS)
	@echo "$(GREEN)$(BOLD)Bonus: $(NAME_BONUS) created successfully!$(RESET)"

$(OBJ_DIR)/bonus/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/bonus
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(C_FLAGS) -c $< -o $@

$(OBJ_DIR)/main $(OBJ_DIR)/bonus:
	@mkdir -p $@
	@echo "$(CYAN)'$(OBJ_DIR)' directory created...$(RESET)"

$(BIN_DIR) $(BIN_DIR)/bonus:
	@mkdir -p $@
	@echo "$(CYAN)'$(BIN_DIR)' directory created...$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Cleaned object files...$(RESET)"

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BIN_DIR)
	@echo "$(RED)Cleaned object files and bin directory...$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
