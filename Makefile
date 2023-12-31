#COLORS
GREEN				:=	\033[0;32m
YELLOW				:=	\033[0;33m
RESET_COLOR			:=	\033[0m

NAME				:=	miniRT
CC					:=	cc
CFLAGS				:=	-Wextra -Wall -Werror -O3 -g
HEADERS				:=	-Ilibft/include -Iinclude -I$(HOME)/libpng/include

# Libraries
LIBFT				:=	libft.a
LIBPNG				:=	-lpng -L ~/libpng/lib
LIBS				:=	$(LIBPNG) $(LIBFT) -ldl -lm -pthread

# SRCS
CAMERA				:=	${addprefix camera/, camera.c utils.c}
CANVAS				:=	${addprefix canvas/, color.c utils.c}
PARSING				:=	${addprefix parsing/, ft_parse.c obj_getters.c utils_0.c utils_1.c utils_2.c}
LIGHT_SHADING		:=	${addprefix light_shading/, lighting.c normals.c normals_helpers.c\
									helpers.c texture_helpers.c reflect.c refract.c}
LSTS				:=	${addprefix lsts/, xs.c objs.c containers.c light_lst.c}
MATRICES			:=	${addprefix matrices/, matrix_ops.c matrix_transformations.c quaternions.c utils.c}
RAY_INTERSECT		:=	${addprefix ray_intersect/, ray.c intersect.c caps.c utils.c}
TUPLES				:=	${addprefix tuples/, tuple_ops.c tuples.c}
PNG					:=	${addprefix png/, ft_png_read.c ft_png_write.c ft_png_utils.c ft_png_img_to_tex.c}

SRCS				:=	main.c \
								$(CAMERA) \
								$(CANVAS) \
								$(PARSING) \
								$(LIGHT_SHADING) \
								$(LSTS) \
								$(MATRICES) \
								$(RAY_INTERSECT) \
								$(TUPLES) \
								$(PNG)


OBJS_DIR			:=	Makefile_objects
OBJS				:=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

$(OBJS_DIR)/%.o		:	%.c
									@mkdir -p $(@D)
									@$(CC) \
									$(CFLAGS) \
									$(HEADERS) \
									-c $< -o $@ \
									&& tput el \
									&& printf "$(YELLOW)Compiling:$(RESET_COLOR) $(notdir $<)\r"

all					:		$(NAME)

$(LIBFT)			:
									@make -C libft/
									@cp libft/$(LIBFT) .
									@make fclean -C libft/
									@tput el && echo "$(GREEN)libft ✓$(RESET_COLOR)"

# FSANITIZE := -fsanitize=address -g

$(NAME)				:		$(LIBFT) $(OBJS)
									@$(CC) $(FSANITIZE) $(OBJS) $(FRAMEWORKS) $(LIBS) -o $(NAME)
									@echo "\n$(GREEN)All Done ✓$(RESET_COLOR)"

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
