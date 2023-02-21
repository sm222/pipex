RED		=	"\x1B[31m"
GRN		=	"\x1B[32m"
YEL		=	"\x1B[33m"
BLU		=	"\x1B[34m"
MAG		=	"\x1B[35m"
CYN		=	"\x1B[36m"
WHT		=	"\x1B[37m"
RESET	=	"\x1B[0m"
NAME	=	pipex
CFLAGS	=	-Wall -Werror -Wextra -g
#-Wall -Werror -Wextra -FD_CLOEXEC
			pipex.c\
#	@echo "				pipex made by anboisve\n " $(RESET)
#	@cat logo.txt
# Removes objects and executables
	@./pipex logo.txt "cat" wc out
	@./pipex
	valgrind -s ./pipex logo.txt "cat" wc out
	leaks -atExit -- ./pipex logo.txt "cat" wc out
# Removes objects and executables and remakes
