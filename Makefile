#COLORS
GREEN				:=	\033[0;32m
YELLOW				:=	\033[0;33m
RESET_COLOR			:=	\033[0m

NAME				:=	miniRT
CC					:=	cc
# TRY TO TEST THE DEBUG FLAG
CFLAGS				:=	-Wextra -Wall -Werror -O3 -g
HEADERS				:=	-Ilibft/include -Iinclude -I$(HOME)/libpng/include

# Libraries
LIBFT				:=	libft.a
LIBPNG				:=	-L ~/libpng/lib -lpng
LIBS				:=	$(LIBPNG) $(LIBFT) -ldl -lm -pthread

# SRCS
CAMERA				:=	${addprefix camera/, camera.c utils.c}
CANVAS				:=	${addprefix canvas/, color.c utils.c}
PARSING				:=	${addprefix checkmap/, allocate_data.c checkmap.c helpers.c my_strtod.c cam_amb.c\
									light_data.c sph_data.c others.c plane_data.c cy_data.c cone_data.c}
LIGHT_SHADING		:=	${addprefix light_shading/, lighting.c normals.c utils.c}
LSTS				:=	${addprefix lsts/, xs.c objs.c containers.c}
MATRICES			:=	${addprefix matrices/, matrix_ops.c matrix_transformations.c quaternions.c utils.c}
RAY_INTERSECT		:=	${addprefix ray_intersect/, ray.c intersect.c caps.c utils.c}
TUPLES				:=	${addprefix tuples/, tuple_ops.c tuples.c}
PNG					:=	${addprefix png/, ft_png_read.c ft_png_write.c ft_png_utils.c ft_png_img_to_btex.c}
PRINT				:=	${addprefix print/, ft_print.c}

SRCS				:=	main.c \
								$(CAMERA) \
								$(CANVAS) \
								$(PARSING) \
								$(LIGHT_SHADING) \
								$(LSTS) \
								$(MATRICES) \
								$(RAY_INTERSECT) \
								$(TUPLES) \
								$(PNG) \
								$(PRINT)


OBJS_DIR			:=	Makefile_objects
OBJS				:=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

$(OBJS_DIR)/%.o		:	%.c
									@mkdir -p $(@D)
									@$(CC) \
									$(CFLAGS) \
									$(HEADERS) \
									-c $< -o $@ \
									&& printf "$(YELLOW)Compiling:$(RESET_COLOR) $(notdir $<)\n"

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