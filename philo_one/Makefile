# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/08 17:53:33 by hthomas           #+#    #+#              #
#    Updated: 2021/04/30 12:13:08 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:
.SUFFIXES: .c .o

SHELL		= /bin/sh

NAME		= philo_one

OBJSDIR		= build/

SRCSDIR		= srcs/

SRCS		= \
			  philo_one.c \
			  check_args.c \
			  messages.c \
			  exit.c \
			  utils.c \
			  fork.c \
			  monitor.c \
			  time.c

OBJS		= $(addprefix $(OBJSDIR), $(SRCS:%.c=%.o))

CC			= clang
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -g3
LDFLAGS		= #-fsanitize=address

THREADFLAGS	= -pthread

all:	$(NAME)

$(OBJSDIR)%.o : $(SRCSDIR)%.c
		mkdir -p build
		$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(THREADFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJS)


fclean:	clean
		$(RM) $(NAME)

re:		fclean
	make all

.PHONY : all clean fclean re
.SILENT: