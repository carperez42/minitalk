# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carperez <carperez@student.45madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 13:25:56 by carperez          #+#    #+#              #
#    Updated: 2023/10/10 18:13:59 by carperez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variable definition: static library name
NAME = libft.a

#variable definition: paths
DIR_HEADER = ../header/
DIR_OBJ = ../obj/
DIR_BIN = ../bin/
DIR_CTYPE = ctype/
DIR_CUSTOM = custom/
DIR_LIST = list/
DIR_STDLIB = stdlib/
DIR_STRING = string/
DIR_FTPRINTF= ft_printf/

#C files
FILES_CTYPE =\
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c
FILES_CUSTOM =\
		ft_substr.c ft_strtrim.c ft_split.c ft_strjoin.c ft_itoa.c ft_strmapi.c ft_striteri.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
FILES_LIST =\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
		ft_lstdelone.c ft_lstclear.c	ft_lstiter.c ft_lstmap.c
FILES_STDLIB =\
		ft_calloc.c ft_atoi.c
FILES_STRING =\
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c\
		ft_strchr.c ft_strrchr.c ft_strlcat.c ft_strncmp.c ft_strnstr.c ft_strdup.c
FILES_FTPRINTF =\
		ft_printf_00.c ft_printf_01_set.c ft_printf_02_chrstr.c\
		ft_printf_03_int.c ft_printf_04_hex.c ft_printf_05_ptr.c\
		ft_printf_06_uns.c ft_printf_07_hex_aux.c\
		ft_printf_08_unsptr_aux.c ft_printf_09_tools.c\

#C files unification
FILES_SRC += $(addprefix $(DIR_CTYPE),$(FILES_CTYPE))
FILES_SRC += $(addprefix $(DIR_CUSTOM),$(FILES_CUSTOM))
FILES_SRC += $(addprefix $(DIR_LIST),$(FILES_LIST))
FILES_SRC += $(addprefix $(DIR_STDLIB),$(FILES_STDLIB))
FILES_SRC += $(addprefix $(DIR_STRING),$(FILES_STRING))
FILES_SRC += $(addprefix $(DIR_FTPRINTF),$(FILES_FTPRINTF))
#SOURCERS = $(addprefix $(DIR_SRC),$(FILES_SRC))
#$(info SOURCERS is $(SOURCERS))

#O files 
OBJECTS = $(addprefix $(DIR_OBJ),$(FILES_SRC:.c=.o))
#$(info OBJECTS is $(OBJECTS))

#commands 
COM_COMPILER = gcc
COM_FLAGS= -Wall -Werror -Wextra -MD -I$(DIR_HEADER) 
COM_STATICLIB = ar rcs
COM_TEMPS = .cache_exists
COM_FOLDERS = mkdir -p
COM_REMOVE = rm -f

#DECLARATED tags
.PHONY: 		all clean fclean re

#CREATION temp subfolders
$(COM_TEMPS):
					@$(COM_FOLDERS) $(DIR_OBJ)
					@$(COM_FOLDERS) $(DIR_OBJ)$(DIR_CTYPE)
					@$(COM_FOLDERS) $(DIR_OBJ)$(DIR_CUSTOM)
					@$(COM_FOLDERS) $(DIR_OBJ)$(DIR_LIST)
					@$(COM_FOLDERS) $(DIR_OBJ)$(DIR_STDLIB)
					@$(COM_FOLDERS) $(DIR_OBJ)$(DIR_STRING)
					@$(COM_FOLDERS) $(DIR_OBJ)$(DIR_FTPRINTF)
					$(info [SUCCESS] temp folder for $(NAME) created.)

#CREATE static library
all:			$(NAME)
$(NAME):		$(OBJECTS)
					@$(COM_FOLDERS) $(DIR_BIN)
					@$(COM_STATICLIB) $(DIR_BIN)$@ $^
					$(info [SUCCESS] static library $@ created.)

#COMPILATION
$(DIR_OBJ)%.o:	%.c | $(COM_TEMPS)
					@$(COM_COMPILER) $(COM_FLAGS) -c $< -o $@
-include $(DIR_OBJ)%.d

#REMOVE objetc files
clean: 
					@$(COM_REMOVE) -rf $(DIR_OBJ)
					@$(COM_REMOVE) -f $(COM_TEMPS)
					$(info [INFO] temp folders removed.)

#REMOVE static library
fclean: 		clean
					@$(COM_REMOVE) -rf $(DIR_BIN)
					$(info [INFO] static library $(NAME) removed.)
					
#RECREATE static library		
re: 			fclean all