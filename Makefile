//INC=/usr/include


//INCLIB=$(INC)/../lib


NAME= fdf
NAME_B= fdf_bonus
SRC = draw_lines.c main.c mlx_utils.c utils.c utils2.c parse.c set_scale.c hook.c parse2.c render.c update.c
SRC_B = draw_lines.c main_bonus.c mlx_utils.c utils.c utils2.c parse.c set_scale.c hook.c parse2.c render.c update.c
OBJ = $(SRC:%.c=%.o)
OBJ_B = $(SRC_B:%.c=%.o)

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Wextra -Werror

CC = gcc $(FLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MLXFLAGS)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: clean all

bonus : $(NAME_B)

$(NAME_B) : $(OBJ_B)
	$(CC) -o $(NAME_B) $(OBJ_B) $(MLXFLAGS)
