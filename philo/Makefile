# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 18:26:19 by alajara-          #+#    #+#              #
#    Updated: 2023/06/08 20:16:50 by alajara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		#===========#
# 		||VARIABLES||
#		#===========#

# -=-=-=-=- NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

NAME		:= philo
MKF			:= Makefile

# -=-=-=-=- CLRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

DEFAULT		:= \033[0m
GRAY		:= \033[0;90m
RED			:= \033[0;91m
GREEN		:= \033[0;92m
YELLOW		:= \033[0;93m
BLUE		:= \033[0;94m
MAGENTA		:= \033[0;95m
CYAN		:= \033[0;96m
WHITE		:= \033[0;97m
BRED		:= \033[1;31m
BGREEN		:= \033[1;32m
BYELLOW		:= \033[1;33m
BBLUE		:= \033[1;34m

# -=-=-=-=- PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

INC_DIR		:= inc/								# Headers
SRC_DIR		:= src/
OBJ_DIR		:= .objs/
#DEP_DIR		:= .deps/

# -=-=-=-=- CMND -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

UNAME		= $(shell uname -s)
CFLAGS		= -Wall -Wextra -Werror
#XFLAGS		= -g3 -fsanitize=thread
#XFLAGS		= -g -fsanitize=address
DFLAGS		= -MT $@ -MMD -MP
INCFLAG		= -I $(INC_DIR)
OFLAG		= -Ofast
#DEFS		= -Dsomething

AR			= ar -src
RM			= rm -rf
MK			= mkdir -p
CP			= cp -f
CC			= cc

# -=-=-=-=- FILE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

BASE_SRCS	= main \
			init \
			monitor \
			monitor_checks \
			philo_routine \
			time \
			utils 

SRCS		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(BASE_SRCS)))
OBJS		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BASE_SRCS)))
DEPS		= $(addprefix $(DEP_DIR), $(addsuffix .d, $(BASE_SRCS)))

# -=-=-=-=- RULE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #


all: $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(MKF)
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) $(OFLAG) $(XFLAGS) $(DEFS) $(DFLAGS) $(INCFLAG) -c $< -o $@
			@printf "\r\t$(YELLOW)$< $(GREEN)compiled$(DEFAULT)                             \r"
# 			@mkdir $(DEPDIR)
# 			@mv $(OBJDIR)*.d $(DEPDIR)

$(NAME)::	$(OBJS) $(MKF)
			@$(CC) $(CFLAGS) $(OFLAG) $(XFLAGS) $(DEFS) $(OBJS) -o $(NAME)
			@echo "\n$(GREEN)[ $(BGREEN)$(NAME)$(GREEN) created! ]$(DEFAULT)"

$(NAME)::
			@echo "$(BLUE)[ All done already ]$(DEFAULT)"

clean:
			@$(RM) $(OBJ_DIR)
			@echo "$(BRED)[ Object files cleared ]$(DEFAULT)"

fclean:	clean
			@$(RM) $(NAME)
			@echo "$(RED)[ All created files cleared ]$(DEFAULT)"

re:	fclean all
			@echo "$(BBLUE)[ All cleared and compiled ]$(DEFAULT)"

norm:
			@norminette $(SRCDIR)* $(INCDIR)*


-include $(DEPS)

.PHONY: all clean fclean re norm
