NAME	= CHIP-8

CC	= gcc

RM	= rm -f

SRCS	=	./srcs/core.c			\
	 		./srcs/main.c			\
	 		./srcs/graphics.c		\
	 		./srcs/keyboard.c		\
	 		./srcs/opcodes.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./headers/ -I/Library/Frameworks/SDL2.framework/Headers
CFLAGS += -Wall -Wextra
LDFLAGS = -L/Library/Frameworks/SDL2.framework/ -lSDL2

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
