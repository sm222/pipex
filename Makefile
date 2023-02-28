RED		=	"\x1B[31m"
GRN		=	"\x1B[32m"
YEL		=	"\x1B[33m"
BLU		=	"\x1B[34m"
MAG		=	"\x1B[35m"
CYN		=	"\x1B[36m"
WHT		=	"\x1B[37m"
RESET	=	"\x1B[0m"
CLE 	=	\e[1;1H\e[2J

NAME	=	pipex
LIBFT	=	libft.a
LDIR	=	lib_ft/

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM	=	rm	-f

#-Wall -Werror -Wextra -FD_CLOEXEC
#-fsanitize=address
#--recurse-submodules
# Sources are all .c files
SRCS	=	utils.c\
			pipex.c\
			ft_child.c

OBJS	=	$(SRCS:.c=.o)

BSRCS	=	utils.c\
			bonus_pipex.c\
			ft_child.c


BOBJS	=	$(BSRCS:.c=.o)

ifdef WITH_BONUS
OBJS_LIST = $(BOBJS)
else
OBJS_LIST = $(OBJS)
endif


USER = $(shell whoami)

all: libft $(NAME) 
	@echo $(shell reset)$(GRN)
	@echo "				pipex made by anboisve\n " $(RESET)
	@cat logo.txt
	@echo $(CYN) "\n\n			correction is made by $(USER)\n\n " $(RESET)
$(NAME): $(OBJS_LIST)
	@$(CC) $(CFLAGS) $(OBJS_LIST) $(LDIR)$(LIBFT) -o $(NAME)

bonus:
	make WITH_BONUS=1 all

libft:
	@$(MAKE) -C $(LDIR)

# Generates output file
# Removes objects
clean:
	$(RM) $(OBJS)
	$(RM) $(BOBJS)
	$(RM) $(LDIR)*.o
	@echo $(shell clear) $(GRN) clean *.o$(RESET)

# Removes objects and executables
fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LDIR)$(LIBFT)
	@echo $(shell clear) $(GRN) clean all$(RESET)

run: all
	@./pipex logo.txt "cat" wc out

mc: all clean
	@./pipex

mem: all
	valgrind -s ./pipex logo.txt "cat" wc out

mem2: all
	leaks -atExit -- ./pipex logo.txt "cat" wc out
# Removes objects and executables and remakes
re: fclean all

.PHONY: all bonus libft