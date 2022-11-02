NAME		=	minirt

NAME_LINUX	=	minirt_linux

# FOR TESTING PURPOSES
RUN_ARGS = test_maps/42.fdf

SHELL	=	bash

GREEN		=	\033[0;32m
CYAN		=	\033[0;36m
RED			=	\033[0;31m
UYELLOW		=	\033[4;33m
RESET_COL	=	\033[0m

CFILES	=	cleanup.c \
			camera.c \
			color.c \
			display.c \
			main.c \
			ray.c \
			utils.c \
			controls/hooks.c controls/key_hooks.c controls/mouse_hooks.c \
			vector/vectors.c vector/vectors_self.c vector/vectors_utils.c \
			intersection/hit_objs.c \
			intersection/hit_lights.c \
			render/render.c \
			render/shader.c \
			parse/parse.c parse/parse_objects.c parse/parse_utils.c \
			init/init_objects.c init/init.c init/init_utils.c \
			matrix/matrix.c matrix/matrix_utils.c matrix/inv_mat.c \
			texture/texture.c texture/read_ppm.c texture/normal_map.c texture/shape_map.c \
			debug.c

SRC_DIR	= srcs
SRCS	= $(addprefix $(SRC_DIR)/, $(CFILES))


OBJ_DIR	= obj
OBJS	= $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

INCFILES	=	hooks.h \
				minirt.h \
				rt_one_weekend.h

INC_DIR			= ./includes
INCS			= $(addprefix $(INC_DIR)/, $(INCFILES))

INCLFLAGS			= -I$(INC_DIR)
MLX_FLAGS 			= -Lminilibx_macos -lmlx  -framework OpenGL -framework AppKit
MLX_FLAGS_LINUX 	= -Lminilibx_linux -lmlx -lXext -lX11
MLX42_FLAGS 		= -lmlx42 -L MLX42 -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/  -framework OpenGL -framework AppKit
LIBFT_FLAGS			= -lft -Llibft
LIBM_FLAG	= -lm

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -Ofast -g -funsafe-math-optimizations


LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

RM_OBJS			=	rm -rf $(OBJ_DIR)
RM_OBJS_OUT		=	$$($(RM_OBJS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_EXE			=	rm -f $(NAME)
RM_EXE_OUT		=	$$($(RM_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_LIBFT		=	make clean -sC ./libft
RM_LIBFT_OUT	=	$$($(RM_LIBFT) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_EXE				=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(LIBM_FLAG) $(MLX_FLAGS) $(INCLFLAGS) $(OBJS) -o $(NAME)
COMPILE_EXE_OUT			=	$$($(COMPILE_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

# linux
COMPILE_EXE_LINUX		=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(LIBM_FLAG) $(MLX_FLAGS_LINUX) $(INCLFLAGS) $(OBJS) -o $(NAME)
COMPILE_EXE_LINUX_OUT	=	$$($(COMPILE_EXE_LINUX) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_C		=	$(CC) $(CFLAGS) $(INCLFLAGS) -o $@ -c $<
COMPILE_C_OUT	=	$$($(COMPILE_C) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(@D)
	@printf "$(CYAN)%-36s-->%36s $(RESET_COL)$(COMPILE_C_OUT)\n" $< $@
# $(COMPILE_C)


all: $(NAME)
	@if [ -e $(NAME) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Compilation successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Compilation failed\n>>>>>>>>$(RESET_COL)"; \
	fi

linux: $(NAME_LINUX)
	@if [ -e $(NAME_LINUX) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Compilation successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Compilation failed\n>>>>>>>>$(RESET_COL)"; \
	fi


$(NAME):	libft pretty_print $(OBJS)
	@echo -e "\n$(CYAN)>>>>>>>> Compiling into executable $(UYELLOW)./$(NAME)$(RESET_COL)$(COMPILE_EXE_OUT)"

$(NAME_LINUX):	libft pretty_print $(OBJS)
	@echo -e "\n$(CYAN)>>>>>>>> Compiling into executable $(UYELLOW)./$(NAME_LINUX)$(RESET_COL)$(COMPILE_EXE_LINUX_OUT)"

silent_libft:
	@echo -e "------------------------------ libft.a ------------------------------\n"
	@echo -e "$(RED)\t*** WARNING: LIBFT CURRENTLY NOT BUILT ***$(RESET_COL)";
	
# @echo -e "$(CYAN)>>>>>>>> Archiving libft.a ...$(RESET_COL)"
# @make -s bonus -C $(LIBFT_DIR)
# @if [ -e $(LIBFT) ]; \
# 	then \
# 	echo -e "$(GREEN)>>>>>>>> Archive successful\n>>>>>>>>$(RESET_COL)"; \
# else \
# 	echo -e "$(RED)>>>>>>>> Archive failed\n>>>>>>>>$(RESET_COL)"; \
# fi

libft: silent_libft

pretty_print: 
	@echo -e "\n------------------------------ $(NAME) -------------------------------"
											  

clean:
	@echo -e "$(RED)>>>>>>>> Deleting obj files$(RESET_COL)$(RM_OBJS_OUT)"

clean_libft:
	@echo -e "$(RED)\t*** WARNING: LIBFT CURRENTLY NOT BUILT ***$(RESET_COL)";
# @echo -e "$(RED)>>>>>>>> make fclean -sC libft $(RESET_COL)$(RM_LIBFT_OUT)"

fclean:	clean clean_libft
	@echo -e "$(RED)>>>>>>>> Deleting $(NAME)$(RESET_COL)$(RM_EXE_OUT)"

re:	fclean all
reish:	clean
	@${MAKE} -j4

bonus:	all

run: all
	./$(NAME) $(RUN_ARGS)

.PHONY: all clean clean_libft fclean re bonus libft silent_libft pretty_print run
