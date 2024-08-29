# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:11:30 by jmakkone          #+#    #+#              #
#    Updated: 2024/08/29 14:00:12 by hello            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME            = minishell
LIBFT_DIR       = ./libft
SRC_DIR         = src
INC_DIR         = inc

SRC             = $(SRC_DIR)/main.c \
				  $(SRC_DIR)/utils/arr_len.c \
				  $(SRC_DIR)/utils/parse_input.c \
				  $(SRC_DIR)/utils/create_path.c \
				  $(SRC_DIR)/utils/free_arr.c \
				  $(SRC_DIR)/utils/path_errors.c \
				  $(SRC_DIR)/env/env_handler.c \
				  $(SRC_DIR)/prompt/prompt.c \

OBJ_DIR         = obj
OBJ             = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT           = $(LIBFT_DIR)/libft.a

RM              = rm -f
CC              = clang
CFLAGS          = -Wall -Wextra -Werror \
				  -I$(INC_DIR) -Og -ggdb3 #-fsanitize=thread
LDFLAGS			= -lreadline


all:	$(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
