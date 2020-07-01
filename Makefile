include sources.mk
include tests.mk

NAME	= CHIP-8

CC		= gcc

RM		= rm -f

CFLAGS 	= -I ./headers/ -I/Library/Frameworks/SDL2.framework/Headers
CFLAGS 	+= -Wall -Wextra
LDFLAGS = -L/Library/Frameworks/SDL2.framework/ -lSDL2

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

tests: $(T_OBJS)
	$(CC) $(T_OBJS) -o $(T_NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(T_OBJS)

fclean: clean
	$(RM) $(NAME) $(TNAME)

re: fclean all

.PHONY: all clean fclean tests re
