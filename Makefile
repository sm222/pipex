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
B_NAME	=	pipex_bonus
LIBFT	=	libft.a
LDIR	=	lib_ft/

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -f

#-Wall -Werror -Wextra -FD_CLOEXEC
#-fsanitize=address
#--recurse-submodules

# Sources are all .c files
SRCS	=	utils.c\
			pipex.c\
			ft_child.c\
			pid_ft.c

OBJS	=	$(SRCS:.c=.o)

BSRCS	=	utils.c\
			bonus_pipex.c\
			ft_child.c\
			pid_ft.c\
			here_doc.c

BOBJS	=	$(BSRCS:.c=.o)

USER = $(shell whoami)

all: libft $(NAME)
	@echo $(shell reset)$(GRN)
	@echo "				pipex made by anboisve\n " $(RESET)
	@cat .logo.txt
	@echo $(CYN) "\n\n			correction is made by $(USER)\n\n " $(RESET)
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDIR)$(LIBFT) -o $(NAME)

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)

bonus: libft $(B_NAME)
	@echo $(shell reset)$(GRN)
	@echo "				pipex made by anboisve\n " $(RESET)
	@cat .logo.txt
	@echo $(CYN) "\n\n			correction is made by $(USER)\n\n " $(RESET)
$(B_NAME): $(BOBJS)
	@$(CC) $(CFLAGS) $(BOBJS) $(LDIR)$(LIBFT) -o $(B_NAME)


libft:
	@echo $(GRN)making libft$(WHT)
	@$(MAKE) -C $(LDIR)

# Generates output file
# Removes objects
clean:
	@$(RM) $(OBJS)
	@$(RM) $(BOBJS)
	@make -C $(LDIR) clean
	@echo $(shell clear)
	@echo -n $(GRN)
	@echo clean *.o$(RESET)

# Removes objects and executables
fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(B_NAME)
	@make -C $(LDIR) fclean
	@echo $(shell clear)$(GRN)clean all$(RESET)


run:
	@./pipex logo.txt "cat" wc out

mc: all clean

mem:
	@valgrind --leak-check=full --trace-children=yes --track-fds=yes ./pipex .logo.txt "cat" wc out

mem2:
	leaks -atExit -- ./pipex .logo.txt "cat" wc out
# Removes objects and executables and remakes
re: fclean all

.PHONY: all bonus libft