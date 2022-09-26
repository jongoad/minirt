#--------------------------------#
#    Name and file information   #
#--------------------------------#
NAME			:= rt


CPP_FILES		:= main.c /parse/parse.c /parse/parse_utils.c /parse/parse_objects.c math/matrix.c

#---------------------------------------------------------#
#   Directory information and object directory building   #
#---------------------------------------------------------#
INC				:= ./includes

SRC_DIR			= ./srcs
SRCS			= $(addprefix $(SRC_DIR)/, $(CPP_FILES))

OBJ_DIR			= ./obj
OBJS			= $(addprefix $(OBJ_DIR)/, $(CPP_FILES:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling $@
	@$(CC) $(CFLAGS) -o $@ -c $<

#--------------------------------#
#  Compiler settings and flags   #
#--------------------------------#
CC				= gcc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -I./includes -I./libft/ -g

#--------------------------------#
#   Makefile rules and targets   #
#--------------------------------#

all:			$(NAME)
				@echo Done.

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a

clean:			
				@$(RM) $(OBJ_DIR)
				@echo Clean complete.

fclean:			clean
				@$(RM) $(NAME)
				@echo Full clean complete.

re:				fclean $(NAME)

.PHONY:			all clean fclean re