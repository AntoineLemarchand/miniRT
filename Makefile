define building
	make -sC $1 > /dev/null 2> /dev/null
endef

define compiling
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
endef

define finishing
	$(CC) $(CFLAGS) $(CPPFLAGS) $2 -o $1 $(LIBS)
endef

define cleaning
	make $2 -sC $1 > /dev/null
endef

define removing
	$(RM) $1 > /dev/null
endef

SRCS		= $(addprefix srcs/, \
				vectors/vec_basic.c \
				vectors/vec_alg.c \
				utils/get_next_line.c \
				utils/obj_utils.c \
				utils/mlx_utils.c \
				utils/init_utils.c \
				utils/free_utils.c \
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
			  	main.c \
				)

OBJS		= $(SRCS:.c=.o)

NAME		= miniRT

RM			= rm -f

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g -o3

CPPFLAGS	= -Ilibs/libft/includes/ -Ilibs/minilibx/ -Iincludes

LIBS		= libs/libft/libft.a libs/minilibx/libmlx_Linux.a -lXext -lX11 -lm



%.o : %.c
				$(call compiling,$<,$(<:.c=.o),0)

${NAME}:		$(OBJS)
				$(call building,libs/libft)
				$(call building,libs/minilibx)
				$(call finishing,$(NAME), $(OBJS))

all:		$(NAME)

clean:	
				$(call removing,$(OBJS))

fclean:		clean
				$(call cleaning,libs/libft,fclean)
				$(call cleaning,libs/minilibx,clean)
				$(call removing,${NAME})

re:			fclean all
