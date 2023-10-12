# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carperez <carperez@student.45madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 11:25:28 by carperez          #+#    #+#              #
#    Updated: 2023/10/10 18:13:55 by carperez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variable definition:
NAME = minitalk.a
LIBFT = libft.a
SERVER = server
CLIENT = client

#variable definition: paths
DIR_HEADER = header/
DIR_LIBFT_h = libft/$(DIR_HEADER)
DIR_OBJ = obj/
DIR_BIN = bin/
DIR_LIBFT_a = libft/$(DIR_BIN)
DIR_SRC = src/
DIR_LIBFT_s = libft/$(DIR_SRC)

#C files
FILES_SRC = server.c client.c minitalk_tools.c 

#O files 
OBJECTS = $(addprefix $(DIR_OBJ),$(FILES_SRC:.c=.o))

#commands 
COM_COMPILER = gcc
COM_FLAGS= -Wall -Werror -Wextra -fsanitize=address -MD -I $(DIR_HEADER) -I $(DIR_LIBFT_h)
COM_STATICLIB = ar rcs
COM_TEMPS = .cache_exists
COM_FOLDERS = mkdir -p
COM_REMOVE = rm -f

#DECLARATED tags
.PHONY: 		all bonus clean fclean re

#CREATION temp subfolders
$(COM_TEMPS):
					@$(COM_FOLDERS) $(DIR_OBJ)
					$(info [SUCCESS] temp folder for $(NAME) created.)

#UPDATE static lib
all:			$(NAME) $(SERVER) $(CLIENT)
$(NAME):		$(OBJECTS)
					@$(COM_FOLDERS) $(DIR_BIN)
					@make -C $(DIR_LIBFT_s) --no-print-directory
					@cp $(DIR_LIBFT_a)$(LIBFT) $(DIR_BIN)
					@mv $(DIR_BIN)$(LIBFT) $(DIR_BIN)$@
					@$(COM_STATICLIB) $(DIR_BIN)$@ $<
					$(info [SUCCESS] static library $@ created.)

#COMPILATION
$(DIR_OBJ)%.o:	$(DIR_SRC)%.c | $(COM_TEMPS)
					@$(COM_COMPILER) $(COM_FLAGS) -c $< -o $@
-include $(DIR_OBJ)%.d

#SERVER_PROCESS compilation
$(SERVER): $(filter-out $(DIR_OBJ)$(CLIENT).o,$(OBJECTS)) $(DIR_BIN)$(NAME)
					@$(COM_COMPILER) $(COM_FLAGS) $^ -o $@
					$(info [SUCCESS] server created.)

#CLIENT_PROCESS compilation
$(CLIENT): $(filter-out $(DIR_OBJ)$(SERVER).o,$(OBJECTS)) $(DIR_BIN)$(NAME)
					@$(COM_COMPILER) $(COM_FLAGS) $^ -o $@
					$(info [SUCCESS] client created.) 

#BONUS tag
bonus: all

#REMOVE temp files
clean:
					@$(COM_REMOVE) -rf $(DIR_OBJ)
					@$(COM_REMOVE) -f $(COM_TEMPS)
					@make clean -C $(DIR_LIBFT_s) --no-print-directory
					$(info [INFO] temp folders removed.)

#REMOVE compilation
fclean:				clean
					@make fclean -C $(DIR_LIBFT_s) --no-print-directory
					@$(COM_REMOVE) -rf $(DIR_BIN)
					@$(COM_REMOVE) -f ./$(CLIENT) ./$(SERVER)
					$(info [INFO] static library $(NAME) removed.)
					$(info [INFO] server removed.)
					$(info [INFO] client removed.)
										

#RECREATE static library and process	
re:				fclean all
