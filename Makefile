# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 15:59:15 by fzayani           #+#    #+#              #
#    Updated: 2024/09/30 16:19:07 by fzayani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Werror -Wextra #-fsanitize=address
RM			= rm -rf
INCS		= -I ./includes/ 

SRC_FILES	= main.c create_philo.c utils.c one_philo.c\
			take.c init.c check_args.c


SRCS_PATH	= src/
OBJS_PATH	= .objs/

SRCS		=	$(addprefix $(SRCS_PATH), $(SRC_FILES))
OBJS		=	$(addprefix $(OBJS_PATH), $(SRC_FILES:.c=.o))



all:	$(OBJS_PATH) $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS_PATH)
	@echo "[DONE] Objects files deletion..."

fclean: clean
	$(RM) $(NAME)
	@echo "[DONE] philo deletion..."

re:	fclean
	make all
	@echo "[DONE] philo recompiled..."

.PHONY:	all clean fclean re
