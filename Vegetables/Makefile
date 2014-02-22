GAMEFRAMEWORK=../GameFramework
OBJS=main.o TileControl.o
SDL_INCLUDE=-I/usr/include/SDL -I${GAMEFRAMEWORK}/SDL_ext
SDL_LIBS=-lSDL -lSDL_ttf -lSDL_mixer -lSDL_image

all: SampleGame
SampleGame: ${OBJS}
	${CC} ${OBJS} -L${GAMEFRAMEWORK} ${SDL_LIBS} -lgameframework -o SampleGame
%.o: %.cpp
	${CC} -I${GAMEFRAMEWORK} ${SDL_INCLUDE} -c $< -o $@
clean:
	-rm ${OBJS}
distclean: clean
	-rm SampleGame
