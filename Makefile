#COLORS
RED					:=	\033[0;31m
GREEN				:=	\033[0;32m
YELLOW				:=	\033[0;33m
RESET_COLOR			:=	\033[0m

NAME				:=	miniRT
CC					:=	cc
CFLAGS				:=	-Wextra -Wall -Werror -O3 -g
HEADERS				:=	-Ilibft/include -Iinclude -I$(HOME)/MLX42/include/MLX42

# Frameworks
FRAMEWORKS			:=	-framework Cocoa -framework OpenGL -framework IOKit

# Libraries
LIBFT				:=	libft.a
LIBMLX				:=	~/MLX42/build/libmlx42.a
GLFW				:=	~/MLX42/build/_deps/glfw-build/src/libglfw3.a
LIBS				:=	$(LIBMLX) $(GLFW) -ldl $(LIBFT) -lm -pthread

# SRCS
TUPLES				:=	${addprefix tuples/, tuples.c}
CANVAS				:=	${addprefix canvas/, color.c window.c utils.c}
MATRICES			:=	${addprefix matrices/, matrices.c matrix_transformations.c quaternions.c}
RAY_INTERSECT		:=	${addprefix ray_intersect/, ray.c intersect.c}
LSTS				:=	${addprefix lsts/, objs.c xs.c}
SCENE				:=	${addprefix scene/, scene.c camera.c}
LIGHT_SHADING		:=	${addprefix light_shading/, lighting.c normals.c utils.c}
PARSING				:=	${addprefix checkmap/, allocate_data.c checkmap.c helpers.c my_strtod.c split_string.c}
PPM					:=	${addprefix ppm_file/, ppm.c}

SRCS				:=	main.c \
								$(TUPLES) \
								$(CANVAS) \
								$(MATRICES) \
								$(RAY_INTERSECT) \
								$(LSTS) \
								$(SCENE) \
								$(LIGHT_SHADING) \
								$(PARSING) \
								$(PPM) \


OBJS_DIR			:=	Makefile_objects
OBJS				:=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

$(OBJS_DIR)/%.o		:	%.c
									@mkdir -p $(@D)
									@$(CC) \
									$(CFLAGS) \
									$(HEADERS) \
									-c $< -o $@ \
									&& printf "Compiling: $(notdir $<)\n"

all					:		$(NAME)

$(LIBFT)			:
									@make -C libft/
									@cp libft/$(LIBFT) .
									@make fclean -C libft/
									@echo "$(GREEN)libft ✓$(RESET_COLOR)"

$(NAME)				:		$(OBJS) $(LIBFT) 
									@$(CC) $(OBJS) $(FRAMEWORKS) $(LIBS) -fsanitize=address -o $(NAME)
# @$(CC) $(OBJS) $(FRAMEWORKS) $(LIBS) -o $(NAME)
									@echo "$(GREEN)All Done ✓$(RESET_COLOR)"

clean				:
									@rm -f $(OBJS)

clean_all			:
									@rm -f $(OBJS) $(LIBFT)

fclean				:		clean
									@rm -f $(NAME)

fclean_all			:		clean_all
									@rm -f $(NAME)

re					:		clean all

re_all				:		clean_all all

.PHONY				:		all, clean, fclean, re