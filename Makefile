NAME				=	minirt
NAME_BONUS			=	minirt_bonus
NAME_LINUX			=	minirt_linux

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -Ofast -g -funsafe-math-optimizations
CFLAGS_BONUS	= -D BONUS=1


# FOR TESTING PURPOSES
RUN_ARGS = scenes/basic.rt

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
			intersection/hit_caps.c \
			intersection/hit_cone.c \
			intersection/hit_cylinder.c \
			intersection/hit_disk.c \
			intersection/hit_lights.c \
			intersection/hit_plane.c \
			intersection/hit_sphere.c \
			render/render.c \
			render/shader.c \
			parse/parse.c parse/parse_objects.c parse/parse_light_camera.c \
			parse/parse_utils.c parse/parse_object_utils.c parse/parse_type_utils.c \
			init/init.c init/init_mlx.c init/init_utils.c \
			init/init_objects.c init/init_light_camera.c init/init_bonus.c \
			matrix/matrix.c matrix/matrix_utils.c \
			texture/texture.c texture/read_ppm.c texture/parse_ppm.c texture/normal_map.c texture/shape_map.c \
			debug.c

SRC_DIR	= srcs
SRCS	= $(addprefix $(SRC_DIR)/, $(CFILES))

OBJ_DIR	= obj
OBJS	= $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

OBJ_DIR_BONUS	= obj_bonus
OBJS_BONUS		= $(addprefix $(OBJ_DIR_BONUS)/, $(CFILES:.c=.o))

INCFILES	=	hooks.h \
				minirt.h \
				defines_enums.h

INC_DIR			= ./includes
INCS			= $(addprefix $(INC_DIR)/, $(INCFILES))

INCLFLAGS			= -I$(INC_DIR)
MLX_FLAGS 			= -Lminilibx_macos -lmlx  -framework OpenGL -framework AppKit
MLX_FLAGS_LINUX 	= -Lminilibx_linux -lmlx -lXext -lX11
LIBFT_FLAGS			= -lft -Llibft
LIBM_FLAG			= -lm

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

RM_OBJS			=	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
RM_EXE			=	rm -f $(NAME) $(NAME_BONUS)
RM_LIBFT		=	make clean -sC ./libft

COMPILE_EXE				=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(LIBM_FLAG) $(MLX_FLAGS) $(INCLFLAGS) $(OBJS) -o $(NAME)
COMPILE_EXE_OUT			=	$$($(COMPILE_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_C		=	$(CC) $(CFLAGS) $(INCLFLAGS) -o $@ -c $<
COMPILE_C_OUT	=	$$($(COMPILE_C) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

# linux
COMPILE_EXE_LINUX		=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(LIBM_FLAG) $(MLX_FLAGS_LINUX) $(INCLFLAGS) $(OBJS) -o $(NAME)
COMPILE_EXE_LINUX_OUT	=	$$($(COMPILE_EXE_LINUX) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

# bonus
COMPILE_C_BONUS			=	$(CC) $(CFLAGS) $(CFLAGS_BONUS) $(INCLFLAGS) -o $@ -c $<
COMPILE_C_BONUS_OUT		=	$$($(COMPILE_C_BONUS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
COMPILE_EXE_BONUS		=	$(CC) $(CFLAGS) $(CFLAGS_BONUS) $(LIBFT_FLAGS) $(LIBM_FLAG) $(MLX_FLAGS) $(INCLFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
COMPILE_EXE_BONUS_OUT	=	$$($(COMPILE_EXE_BONUS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')



$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(@D)
	@printf "$(CYAN)%-40s-->%40s $(RESET_COL)$(COMPILE_C_OUT)\n" $< $@

$(OBJ_DIR_BONUS)/%.o:	$(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(@D)
	@printf "$(CYAN)%-40s-->%40s $(RESET_COL)$(COMPILE_C_BONUS_OUT)\n" $< $@

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
	@echo -e "\n$(CYAN)>>>>>>>> Compiling into executable $(UYELLOW)./$(NAME)$(RESET_COL)"
	@$(COMPILE_EXE_OUT)

$(NAME_BONUS): libft pretty_print $(OBJS_BONUS)
	@echo -e "\n$(CYAN)>>>>>>>> Compiling into executable $(UYELLOW)./$(NAME_BONUS)$(RESET_COL)"
	@$(COMPILE_EXE_BONUS_OUT)

$(NAME_LINUX):	libft pretty_print $(OBJS)
	@echo -e "\n$(CYAN)>>>>>>>> Compiling into executable $(UYELLOW)./$(NAME_LINUX)$(RESET_COL)"
	@$(COMPILE_EXE_LINUX_OUT)

silent_libft:
	@echo -e "------------------------------ libft.a ------------------------------\n"
	@echo -e "$(CYAN)>>>>>>>> Archiving libft.a ...$(RESET_COL)"
	@make -s bonus -C $(LIBFT_DIR)
	

libft: silent_libft

pretty_print: 
	@echo -e "\n------------------------------ $(NAME) -------------------------------"

pretty_print_bonus:
	@echo -e "\n------------------------------ $(NAME_BONUS) -------------------------------"
	
clean:
	@echo -e "$(RED)>>>>>>>> Deleting obj files$(RESET_COL)"
	@$(RM_OBJS)

clean_libft:
	@echo -e "$(RED)>>>>>>>> make fclean -sC libft $(RESET_COL)"
	@$(RM_LIBFT)

fclean:	clean clean_libft
	@echo -e "$(RED)>>>>>>>> Deleting $(NAME)$(RESET_COL)"
	@$(RM_EXE)

re:	fclean all

bonus:	$(NAME_BONUS)
	@if [ -e $(NAME_BONUS) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Compilation successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Compilation failed\n>>>>>>>>$(RESET_COL)"; \
	fi

run: all
	./$(NAME) $(RUN_ARGS)

.PHONY: all clean clean_libft fclean re bonus libft silent_libft pretty_print run pretty_print_bonus
