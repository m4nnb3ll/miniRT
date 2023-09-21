#COLORS
GREEN				:=	\033[0;32m
RESET_COLOR			:=	\033[0m

NAME				:=	miniRT
CC					:=	cc
CFLAGS				:=	-Wextra -Wall -Werror -O3
HEADERS				:=	-Ilibft/include -Iinclude -I$(HOME)/MLX42/include/MLX42

# Frameworks
FRAMEWORKS			:=	-framework Cocoa -framework OpenGL -framework IOKit

# Libraries
LIBFT				:=	libft.a
LIBMLX				:=	~/MLX42/build/libmlx42.a
GLFW				:=	~/MLX42/build/_deps/glfw-build/src/libglfw3.a
LIBS				:=	$(LIBMLX) $(GLFW) $(LIBFT) -ldl -lm -pthread

# SRCS
CAMERA				:=	${addprefix camera/, camera.c utils.c}
CANVAS				:=	${addprefix canvas/, color.c window.c utils.c}
PARSING				:=	${addprefix checkmap/, allocate_data.c checkmap.c helpers.c my_strtod.c cam_amb.c\
									light_data.c sph_data.c others.c plane_data.c cy_data.c cone_data.c}
LIGHT_SHADING		:=	${addprefix light_shading/, lighting.c normals.c utils.c}
LSTS				:=	${addprefix lsts/, xs.c}
MATRICES			:=	${addprefix matrices/, matrix_ops.c matrix_transformations.c quaternions.c utils.c}
PPM					:=	${addprefix ppm_file/, ppm.c}
RAY_INTERSECT		:=	${addprefix ray_intersect/, ray.c intersect.c caps.c utils.c}
TUPLES				:=	${addprefix tuples/, tuple_ops.c tuples.c}

SRCS				:=	main.c \
								$(CAMERA) \
								$(CANVAS) \
								$(PARSING) \
								$(LIGHT_SHADING) \
								$(LSTS) \
								$(MATRICES) \
								$(PPM) \
								$(RAY_INTERSECT) \
								$(TUPLES) \


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
									@$(CC) $(OBJS) $(FRAMEWORKS) $(LIBS) -o $(NAME)
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