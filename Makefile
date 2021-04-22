SRCS		= main.cpp
OBJS		= ${SRCS:.cpp=.o}

CXX			= clang++
CXXFLAGS	= -Werror -Wextra -Wall -std=c++98 ${SRCS}

RM = rm -f

NAME = tester

all:	${NAME}

.cpp.o:
	${CXX} ${CXXFLAGS} -c  $< -o ${<:.cpp=.o}

${NAME}:	${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

test: ${NAME}
	./${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all test clean fclean re