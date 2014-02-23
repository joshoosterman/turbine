GF=GameFramework
GF_SRCS = $(shell ls ${GF}/*.cpp)
GF_OBJS = ${GF_SRCS:.cpp=.o}

SMG=SampleGame
SMG_SRCS = $(shell ls ${SMG}/*.cpp)
SMG_OBJS = ${SMG_SRCS:.cpp=.o}

SFML_LIBS = -lsfml-network -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
CC = g++ -g


${GF}/%.o: ${GF}/.%cpp
	${CC} -I${GF} -c $< -o $@

libgameframework.a: ${GF_OBJS}
	ar rvs ${GF}/libgameframework.a $?

${SMG}/%.o: ${SMG}/%.cpp
	${CC} -I${GF} -I${SMG} -c $< -o $@

SampleGame: ${SMG_OBJS} libgameframework.a
	#${CC} ${SMG_OBJS} ${GF}/libgameframework.a ${SFML_LIBS} -o ${SMG}/SampleGame
	${CC} ${SMG_OBJS} ${GF_OBJS} ${SFML_LIBS} -o ${SMG}/SampleGame

all: SampleGame
#SampleGame: ${OBJS} ${GOBJS}
#	${CC} ${GOBJS} ${OBJS} ${LIBS} -o SampleGame
#	${CC} ${OBJS} ../GameFramework/libgameframework.a ${LIBS} -o SampleGame

clean:
	-rm ${GF_OBJS} ${SMG_OBJS}

