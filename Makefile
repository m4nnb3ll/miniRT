#COLORS
RED					:=	\033[0;31m
GREEN				:=	\033[0;32m
YELLOW			:=	\033[0;33m
RESET_COLOR	:=	\033[0m

NAME				:=	miniRT
CC					:=	cc
CFLAGS			:=	-Wextra -Wall -Werror -O3 -g
HEADERS			:=	-Ilibft/include -Iinclude -I~/MLX42/include

# Libraries
LIBFT				:=	libft.a
LIBMLX			:=	~/MLX42/build/libmlx42.a
LIBS				:=	$(LIBMLX) -lglfw3 -ldl -lX11 -pthread $(LIBFT) -lm

# SRCS
TUPLES			:=	${addprefix tuples/, tuples.c}
CANVAS			:=	${addprefix canvas/, canvas.c color.c}
MATRICES		:=	${addprefix matrices/, matrices.c matrix_transformations.c}

SRCS				:=	main.c \
								$(TUPLES) \
								$(CANVAS) \
								$(MATRICES) \

OBJS				:=	${SRCS:.c=.o}

%.o					:		%.c
									@$(CC) \
									$(CFLAGS) \
									$(HEADERS) \
									-c $< -o $@ \
									&& printf "Compiling: $(notdir $<)\n"

all					:		$(NAME)

$(LIBFT)		:
									@make -C libft/
									@cp libft/$(LIBFT) .
									@make fclean -C libft/
									@echo "$(GREEN)libft ✓$(RESET_COLOR)"

$(NAME)			:		$(OBJS) $(LIBFT)
									@$(CC) $(OBJS) $(LIBS) -fsanitize=address -o $(NAME)
									@echo "$(GREEN)All Done ✓$(RESET_COLOR)"

clean				:
									@rm -f $(OBJS)

clean_all		:
									@rm -f $(OBJS) $(LIBFT)

fclean			:		clean
									@rm -f $(NAME)

fclean_all	:		clean_all
									@rm -f $(NAME)

re					:		clean all

re_all			:		clean_all all

.PHONY			:		all, clean, fclean, re