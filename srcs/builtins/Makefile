# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twagner <twagner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 11:42:26 by twagner           #+#    #+#              #
#    Updated: 2021/10/12 16:46:06 by twagner          ###   ########.fr        #
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
SCD		= srcs/cd.c
SECHO	= srcs/echo.c
SPWD	= srcs/pwd.c
SEXPORT	= srcs/export.c
SUNSET	= srcs/unset.c
SENV	= srcs/env.c
SEXIT	= srcs/exit.c

OCD		= $(SCD:.c=.o)
OECHO	= $(SECHO:.c=.o)
OPWD	= $(SPWD:.c=.o)
OEXPORT	= $(SEXPORT:.c=.o)
OUNSET	= $(SUNSET:.c=.o)
OENV	= $(SENV:.c=.o)
OEXIT	= $(SEXIT:.c=.o)

################################################################################
#                                 DIRECTORIES                                  #
################################################################################
HEADERS		= ../../includes/
LFTDIR		= ../../
LFTDIRH		= ../../libft/

################################################################################
#                           EXECUTABLES & LIBRARIES                            #
################################################################################
PCD		= cd
PECHO	= echo
PPWD	= pwd
PEXPORT	= export
PUNSET	= unset
PENV	= env
PEXIT	= exit
LFT		= $(LFTDIR)libft.a

################################################################################
#                                     FLAGS                                    #
################################################################################
CFLAGS		:= -Wall -Wextra -Werror
LFTFLAGS	:= -L$(LFTDIR) -lft

ifeq ($(DEBUG), true)
	CFLAGS	+= -fsanitize=address -g3 -O0
endif

################################################################################
#                                    RULES                                     #
################################################################################
.c.o:
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(HEADERS) -I$(LFTDIRH)

$(PCD):		$(LFT) $(OCD)
			@$(CC) $(CFLAGS) $(OCD) -o $(PCD) -I$(HEADERS) $(LFTFLAGS) $(LADDFLAGS)

$(PECHO):	$(LFT) $(OECHO)
			@$(CC) $(CFLAGS) $(OECHO) -o $(PECHO) -I$(HEADERS) $(LFTFLAGS) $(LADDFLAGS)

$(PPWD):	$(LFT) $(OPWD)
			@$(CC) $(CFLAGS) $(OPWD) -o $(PPWD) -I$(HEADERS) $(LFTFLAGS) $(LADDFLAGS)

$(PEXPORT):	$(LFT) $(OEXPORT)
			@$(CC) $(CFLAGS) $(OEXPORT) -o $(PEXPORT) -I$(HEADERS) $(LFTFLAGS) $(LADDFLAGS)

$(PUNSET):	$(LFT) $(OUNSET)
			@$(CC) $(CFLAGS) $(OUNSET) -o $(PUNSET) -I$(HEADERS) $(LFTFLAGS) $(LADDFLAGS)

$(PENV):	$(LFT) $(OENV)
			@$(CC) $(CFLAGS) $(OENV) -o $(PENV) -I$(HEADERS) $(LFTFLAGS) $(LADDFLAGS)

$(PEXIT):	$(LFT) $(OEXIT)
			@$(CC) $(CFLAGS) $(OEXIT) -o $(PEXIT) -I$(HEADERS) $(LFTFLAGS) $(LADDFLAGS)

all:		$(PCD) $(PECHO) $(PPWD) $(PEXPORT) $(PUNSET) $(PENV) $(PEXIT)

clean:
			@$(RM) $(OCD) $(OECHO) $(OPWD) $(OEXPORT) $(OUNSET) $(OENV) $(OEXIT)

fclean:		clean
			@$(RM) $(PCD) $(PECHO) $(PPWD) $(PEXPORT) $(PUNSET) $(PENV) $(PEXIT)

re:			fclean all

.PHONY:		all clean fclean c.o re
