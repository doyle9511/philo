# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/02 17:37:26 by donghwi2          #+#    #+#              #
#    Updated: 2025/01/02 17:37:28 by donghwi2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include
LIBS = -pthread
RM = rm -f

SRCS_DIR = source/
SRCS = main.c \
       init.c \
       philo_routin.c \
       util.c

SRCS_PREFIX = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(SRCS_PREFIX:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re