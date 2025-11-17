CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++23 -Iinclude -Iinclude/classes -I/opt/homebrew/include  -MMD -MP -O3
LDFLAGS  := -L/opt/homebrew/lib -lglfw -lassimp -framework OpenGL

NAME     := vox

SRC_DIR  := src
INC_DIR  := include
OBJ_DIR  := build

SRCS     := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS     := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS     := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
