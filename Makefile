define building
	make -sC $1 > /dev/null 2> /dev/null
endef

define compiling
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
endef

define finishing
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME) $(LIBS)
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
				obj_utils.c \
				mlx_utils.c \
			  	main.c \
				)

OBJS		= $(SRCS:.c=.o)

NAME		= miniRT

RM			= rm -f

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g

CPPFLAGS	= -Ilibft/includes -I minilibx/ -Iincludes

LIBS		= ./libft/libft.a minilibx/libmlx_Linux.a -lXext -lX11 -lm



%.o : %.c
			$(call compiling,$<,$(<:.c=.o),0)

${NAME}:	$(OBJS)
			$(call building,libft)
			$(call building,minilibx)
			$(call finishing,$(NAME))

all:		$(NAME)

clean:	
			$(call removing,$(OBJS))

fclean:		clean
			$(call cleaning,libft,fclean)
			$(call cleaning,minilibx,clean)
			$(call removing,${NAME})

re:			fclean all
