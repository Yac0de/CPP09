NAME = btc

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_FILES = main BitcoinExchange
SRC = $(addsuffix .cpp, $(SRC_FILES))
OBJ = $(SRC:.cpp=.o)

RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling $(NAME)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Compiled: $<$(NO_COLOR)"

clean:
	@echo "$(RED)Cleaning objects...$(NO_COLOR)"
	@$(RM) $(OBJ)

fclean: clean
	@echo "$(RED)Full cleaning...$(NO_COLOR)"
	@$(RM) $(NAME)

re: fclean all
	@echo "$(GREEN)Recompiled$(NO_COLOR)"

.PHONY: all clean fclean re