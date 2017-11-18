NAME = wolf3d

VPATH = src

IDIR = includes/

BIN_DIR = bin/

LIBFT = libft/libft.a

LIBFT_IDIR = libft/

HEADERS = -I $(LIBFT_IDIR) -I $(IDIR)

COMPILER_FLAGS = -Wall -Wextra -Werror -g

ifeq ($(shell uname -s),Linux)
	COMPILER_FLAGS += -lm
	LINKER_FLAGS = -lSDL2
else
	LINKER_FLAGS = -F /Library/Frameworks/ -framework SDL2
endif

SRC_DIR = src/

SRCS = main.c							\
	   parser.c							\
	   player.c							\
	   drawer.c							\
	   utility/vertex.c					\
	   utility/utility.c				\

BINS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

$(BIN_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(shell dirname $@)
	gcc $(COMPILER_FLAGS) $(HEADERS) -c -o $@ $<

all: $(NAME)

$(NAME): $(LIBFT) $(BINS)
	gcc -o $(NAME) $(BINS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(HEADERS) \
		$(LIBFT) $(LIB_GEOMETRY)

$(LIBFT):
	make -j4 -C libft

libclean:
	make -C libft clean

libfclean:
	make -C libft fclean

clean: libclean
	/bin/rm -f $(BINS)

fclean: libfclean clean
	/bin/rm -f $(NAME)

re: fclean all
