.SUFFIXES:

NAME	=	cub3D
LIST	=	\

LIST_CPP	=	fixed \
				main \
				cub3D \
				gnl \
				gnl_utils \

HEADER	=	-I includes/
CFLAGS	=	-Wall -Wextra -Werror -MMD
CC		=	gcc

S_DIR	=	srcs/
I_DIR	=	includes/
O_DIR	=	objs/
D_DIR	=	deps/

C_SUFF	=	.c
CPP_SUFF	= .cpp
O_SUFF	=	.o
D_SUFF	=	.d

DIR_O	=	@mkdir -p objs/
DIR_D	=	@mkdir -p deps/

RM_FILE	= rm -f
RM_DIR	= rm -rf

LIST_C	= $(addprefix $(S_DIR), $(LIST))
LIST_O	= $(addprefix $(O_DIR), $(LIST))
LIST_D	= $(addprefix $(D_DIR), $(LIST))
LIST_O_CPP	= $(addprefix $(O_DIR), $(LIST_CPP))

SRCS	= $(addsuffix $(C_SUFF), $(LIST_C))
SRCS_CPP	= $(addsuffix $(CPP_SUFF), $(LIST_CPP))
OBJS	= $(addsuffix $(O_SUFF), $(LIST_O))
OBJS_CPP	= $(addsuffix $(O_SUFF), $(LIST_O_CPP))
DEPS	= $(OBJS:.o=.d)

$(O_DIR)%.o	:	$(S_DIR)%.c
				$(DIR_O)
				$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(O_DIR)%.o	:	$(S_DIR)%.cpp
				$(DIR_O)
				clang++ -std=c++98 $(CFLAGS) $(HEADER) -c $< -o $@
$(NAME)	:		$(OBJS) $(OBJS_CPP)
				clang++ $(CFLAGS) $(OBJS) $(OBJS_CPP) -o $(NAME) -L. ./srcs/minilibx/libmlx.a -lXext -lX11 -lm -lbsd


all	:			$(NAME)

clean	:		
				$(RM_DIR) $(O_DIR) $(D_DIR)

fclean	:		clean
				$(RM_FILE) $(NAME)

re	:			fclean all

.PHONY	:		all clean fclean re

-include	$(DEPS)