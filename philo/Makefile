# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twagner <twagner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/01 15:32:48 by twagner           #+#    #+#              #
#    Updated: 2021/12/18 10:49:04 by twagner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                               PARAMS & COLORS                                #
################################################################################
OS			=  $(shell uname -s)

ifneq (,$(findstring xterm,${TERM}))
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	BLUE         := $(shell tput -Txterm setaf 6)
	RESET		 := $(shell tput -Txterm sgr0)
else
	GREEN        := ""
	YELLOW       := ""
	BLUE         := ""
	RESET        := ""
endif

################################################################################
#                                 COMMANDS                                     #
################################################################################
RM			= rm -f
CC			= gcc
AR			= ar rcs

################################################################################
#                                 SOURCES                                      #
################################################################################
SRCS		= srcs/main.c \
			  srcs/utils.c \
			  srcs/time.c \
			  srcs/philo.c \
			  srcs/fork.c \
			  srcs/routine.c \
			  srcs/status.c \
			  srcs/param.c

OBJS		= $(SRCS:.c=.o)

################################################################################
#                           EXECUTABLES & LIBRARIES                            #
################################################################################
NAME		= philo
LIBPTHREAD	= -lpthread

################################################################################
#                                 DIRECTORIES                                  #
################################################################################
HEADERS		= includes/

################################################################################
#                                     FLAGS                                    #
################################################################################
CFLAGS		:= -Wall -Wextra -Werror

ifeq ($(DEBUG), true)
	CFLAGS	+= -fsanitize=address -g3 -O0
endif
ifeq ($(DTHREAD), true)
	CFLAGS	+= -fsanitize=thread -g3 -O0
endif
ifeq ($(GPROF), true)
	CFLAGS	+= -g -pg
endif

################################################################################
#                                    RULES                                     #
################################################################################
.c.o:
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(HEADERS)

$(NAME):	$(OBJS)
			@printf  "$(BLUE)Creating $(RESET) $(YELLOW)[$(NAME)]$(RESET)" 
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I$(HEADERS) $(LIBPTHREAD)
			@echo " : $(GREEN)OK !$(RESET)"

all:		$(NAME)

bonus:		$(NAME)

clean:
			@printf "$(BLUE)Cleaning $(RESET) $(YELLOW)[objects & libraries]$(RESET)"
			@$(RM) $(OBJS)
			@echo " : $(GREEN)OK !$(RESET)"

fclean:		clean
			@printf "$(BLUE)Cleaning $(RESET) $(YELLOW)[executable(s)]$(RESET)"
			@$(RM) $(NAME)
			@echo " : $(GREEN)OK !$(RESET)"

re:			fclean all

.PHONY:		all clean fclean c.o re
