T=turbine
T_SRCS = $(shell ls ${T}/*.cc)
T_OBJS = ${T_SRCS:.cc=.o}

SMG=sample_game
SMG_SRCS = $(shell ls ${SMG}/*.cc)
SMG_OBJS = ${SMG_SRCS:.cc=.o}

SFML_LIBS = -lsfml-network -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
CC=g++ -g

${T}/%.o: ${T}/%.cc
	${CC} -I. -I/usr/include -c $< -o $@

libturbine.a: ${T_OBJS}
	ar rvs ${T}/libturbine.a $?

${SMG}/%.o: ${SMG}/%.cc
	${CC} -I. -I/usr/include -c $< -o $@

sample_game: ${SMG_OBJS} ${T}/libturbine.a
	${CC} ${SMG_OBJS} ${T_OBJS} ${SFML_LIBS} -o ${SMG}/sample_game

all: sample_game

clean:
	-rm -f ${T_OBJS} ${SMG_OBJS} ${T}/libturbine.a ${SMG}/sample_game

