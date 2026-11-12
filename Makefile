# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/12 14:53:14 by rpanetta          #+#    #+#              #
#    Updated: 2026/11/12 17:30:42 by rpanetta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

SOURCES = src/main.c\
src/errors.c\
src/parse.c\
src/validate_scheduler.c\

OBJECTS = $(SOURCES:%.c=%.o)

CC = cc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -pthread -Iincludes

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c includes/codexion.h Makefile
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re