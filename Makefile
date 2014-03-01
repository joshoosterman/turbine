SFML_LIBS = -lsfml-network -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
CC=g++ -g

all: sample_game/sample_game vegetables/vegetables

T_SRCS = $(shell ls turbine/*.cc)
T_OBJS = ${T_SRCS:.cc=.o}

SMG_SRCS = $(shell ls sample_game/*.cc)
SMG_OBJS = ${SMG_SRCS:.cc=.o}

VEG_SRCS = $(shell ls vegetables/*.cc)
VEG_OBJS = ${VEG_SRCS:.cc=.o}


turbine/%.o: turbine/%.cc
	${CC} -I. -I/usr/include -c $< -o $@

turbine/libturbine.a: ${T_OBJS}
	ar rvs turbine/libturbine.a $?


sample_game/%.o: sample_game/%.cc
	${CC} -I. -I/usr/include -c $< -o $@

sample_game/sample_game: ${SMG_OBJS} turbine/libturbine.a
	${CC} ${SMG_OBJS} ${T_OBJS} ${SFML_LIBS} -o sample_game/sample_game


vegetables/%.o: vegetables/%.cc
	${CC} -I. -I/usr/include -c $< -o $@

vegetables/vegetables: ${VEG_OBJS} turbine/libturbine.a
	${CC} ${VEG_OBJS} ${T_OBJS} ${SFML_LIBS} -o vegetables/vegetables


clean:
	-rm -f ${T_OBJS} ${SMG_OBJS} turbine/libturbine.a sample_game/sample_game

