define building
	@echo -n "Building $1 "
	@make -sC $1 > /dev/null 2> /dev/null
	@echo "√"
endef

define compiling
	@echo -n "Compiling $1 "
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
	@echo "√"
endef

define finishing
	@echo -n "Compiling $1 "
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "√"
endef

define cleaning
	@echo -n "Cleaning $1 "
	@make $2 -sC $1 > /dev/null
	@echo "√"
endef

define removing
	@echo -n "Removing $1 "
	@$(RM) $1 > /dev/null
	@echo "√"
endef

SRCS		= $(addprefix srcs/, \
			  	main.c \
				)

OBJS		= $(SRCS:.c=.o)

NAME		= miniRT

RM			= rm -f

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g

CPPFLAGS	= -Ilibft/includes  -I minilibx/ -Iincludes

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
