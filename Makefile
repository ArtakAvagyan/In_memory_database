SERVER		= src/client_server/server.cpp
CLIENT		= src/client_server/client.cpp
S_OBJS		= ${SERVER:.cpp=.o}
C_OBJS		= ${CLIENT:.cpp=.o}
CC		= g++
RM		= rm -f
THREADFLAG	= -lpthread
CFLAGS		= -Wall -Wextra -Werror

%.o : %.c
	${CC} ${CFLAGS} -c $< -o obj/${<:.c=.o}

all : ${S_OBJS} ${C_OBJS}
	${CC} ${CFLAGS} ${S_OBJS} -o bin/server ${THREADFLAG}
	${CC} ${CFLAGS} ${C_OBJS} -o bin/client	

clean :
	${RM} ${S_OBJS}
	${RM} ${C_OBJS}

fclean : clean
	${RM} bin/server
	${RM} bin/client

re : fclean all

.PHONY: all clean fclean bonus re .c.o
