# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/08 17:53:33 by hthomas           #+#    #+#              #
#    Updated: 2021/05/03 11:54:23 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# .SUFFIXES: .c .o

NAME	=		philo_one

SHELL	=		/bin/sh
CC		=		clang
RM		=		rm -f

CFLAGS	=		-Wall -Wextra -Werror
LDFLAGS	=		#-fsanitize=address -g3
THREADFLAGS	=	-pthread

SRCSDIR	=		srcs/
SRCS	=		philo_one.c \
				check_args.c \
				messages.c \
				exit.c \
				utils.c \
				fork.c \
				monitor.c \
				time.c

OBJSDIR	=		build/
OBJS	=		$(addprefix $(OBJSDIR), $(SRCS:%.c=%.o))

HEADER	=		$(SRCSDIR)philo_one.h


all:	$(NAME)

$(OBJSDIR)%.o:	$(SRCSDIR)%.c $(HEADER)
	@mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(THREADFLAGS) $(OBJS) -o $@

clean:
	$(RM) $(OBJS)


fclean:	clean
	$(RM) $(NAME)

re:		fclean
	make all

.PHONY:	all clean fclean re
.SILENT:
