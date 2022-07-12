define building
	make -sC $1 > /dev/null 2> /dev/null
endef

define compiling
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
endef

define finishing
	$(CC) $(CFLAGS) $(CPPFLAGS) $2 -o $1 $(LIBS) $3
endef

define cleaning
	make $2 -sC $1 > /dev/null
endef

define removing
	$(RM) $1 > /dev/null
endef

FILES			= vectors/vec_basic.c \
				vectors/vec_alg.c \
				vectors/vec_utils.c \
				utils/get_next_line.c \
				utils/obj_utils.c \
				utils/mlx_utils.c \
				utils/init_utils.c \
				utils/free_utils.c \
				utils/load_utils.c \
				utils/check_utils.c \
				init/check_shape.c \
				init/check_objs.c \
				init/init_file.c \
				init/init_shape.c \
				init/init_shapes.c \
				init/init_scene.c \
				raytracing/cam.c \
				raytracing/trace_shapes.c \
				raytracing/shadow_ray.c \
				raytracing/primary_ray.c \
			  	main.c

SRCS		= $(addprefix srcs/, $(FILES))

SRCS_BONUS	= $(addprefix srcs_bonus/, $(FILES) raytracing/trace_triangle.c)

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

NAME		= miniRT

NAME_BONUS	= miniRT_bonus

RM			= rm -f

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g -o3

CPPFLAGS	= -Ilibs/libft/includes/ -Ilibs/minilibx/ -Iincludes

LIBS		= libs/libft/libft.a libs/minilibx/libmlx_Linux.a -lXext -lX11 -lm

%.o : %.c
				$(call compiling,$<,$(<:.c=.o))

${NAME}:		$(OBJS)
				$(call building,libs/libft)
				$(call building,libs/minilibx)
				$(call finishing,$(NAME), $(OBJS))

${NAME_BONUS}:	$(OBJS_BONUS)
				$(call building,libs/libft)
				$(call building,libs/minilibx)
				$(call finishing,$(NAME_BONUS), $(OBJS_BONUS))

all:		$(NAME)

bonus:		$(NAME_BONUS)

clean:	
				$(call removing,$(OBJS))
				$(call removing,$(OBJS_BONUS))

fclean:		clean
				$(call cleaning,libs/libft,fclean)
				$(call cleaning,libs/minilibx,clean)
				$(call removing,${NAME})
				$(call removing,${NAME_BONUS})

re:			fclean all
