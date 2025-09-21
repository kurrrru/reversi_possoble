NAME = reversi
CXX = g++
CXXLAGS = -Wall -Wextra -Werror -O3 -flto -I.
SRCS = main.cpp Board.cpp func.cpp
SRCS_DIR = src/
OBJS = $(SRCS:%.cpp=$(SRCS_DIR)%.o)
RM = rm -f

.DEFAULT_GOAL := all

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXLAGS) -o $@ $^

$(SRCS_DIR)%.o: $(SRCS_DIR)%.cpp
	$(CXX) $(CXXLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
