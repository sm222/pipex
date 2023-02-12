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
# Sources are all .c files
SRCS	=	main.c


OBJS	=	$(SRCS:.c=.o)

USER = $(shell whoami)

all: $(NAME)
#	@ echo $(shell reset)$(GRN)
	@echo "				pipex made by anboisve\n " $(RESET)
	@cat logo.txt
	@echo $(CYN) "\n\n			correction is made by $(USER)\n\n " $(RESET)
# Generates output file
$(NAME): $(OBJS)
	@$(MAKE) -C $(LDIR)
	@$(CC) $(CFLAGS) $(SRCS) $(LDIR)$(LIBFT) -o $(NAME)
# Removes objects
clean:
	$(RM) $(OBJS)
	$(RM) $(LDIR)*.o
	@ echo $(shell clear) $(GRN) clean *.o$(RESET)

# Removes objects and executables
fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LDIR)$(LIBFT)
	@echo $(shell clear) $(GRN) clean all$(RESET)

run: all
	@./pipex

mc: all clean
	@./pipex

mem: all
	valgrind -s ./pipex
# Removes objects and executables and remakes
re: fclean all