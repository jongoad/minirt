NAME	=	libft.a

CFILES	=	ft_atoi.c \
			ft_atox.c \
			ft_basic_math.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_get_magnitude.c \
			ft_get_next_line.c \
			ft_get_token.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_is_set.c \
			ft_itoa.c \
			ft_log_calc.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_printhex.c \
			ft_print_split.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strcat_iter.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strjoin_free.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strlen_c.c \
			ft_strmapi.c \
			ft_strcmp.c \
			ft_strncpy.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_swap.c \
			ft_tolower.c \
			ft_toupper.c

CFILES_B	=	ft_lstsize_bonus.c \
				ft_lstmap_bonus.c \
				ft_lstnew_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstadd_back_bonus.c

SRC_DIR =	src

SRCS	=	$(addprefix $(SRC_DIR)/, $(CFILES))

SRCS_B	=	$(addprefix $(SRC_DIR)/, $(CFILES_B))

OBJ_DIR =	obj

OBJS	=	$(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))
#${SRCS:.c=.o}

OBJS_B	=	$(addprefix $(OBJ_DIR)/,$(CFILES_B:.c=.o))
#OBJS_B	=	${SRCS_B:.c=.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I.

AR		=	ar

ARFLAGS	=	-rcs

RM		=	rm -f

#.c.o:
#	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	${AR} ${ARFLAGS} $@ $^

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p obj
	${CC} ${CFLAGS} -o $@ -c $<

all:	${NAME}

clean:
	${RM} ${OBJS} ${OBJS_B}
	${RM} -r ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

#clean:	
#	${RM} ${OBJS} ${OBJS_B}
#
#fclean:	clean
#	${RM} ${NAME}

re:	fclean all

bonus:	${OBJS} ${OBJS_B}
	${AR} ${ARFLAGS} ${NAME} $^

.PHONY: all clean fclean re bonus
