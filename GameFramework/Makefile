SRCS = $(shell ls *.cpp)
OBJS = ${SRCS:.cpp=.cpp.o}
SDL_EXT_SRCS = $(shell ls SDL_ext/*.c)
#SDL_ext/SDL_framerate.c.o SDL_ext/SDL_gfxBlitFunc.c.o SDL_ext/SDL_gfxPrimitives.c.o SDL_ext/SDL_imageFilter.c.o SDL_ext/SDL_rotozoom.c.o
SDL_EXT_OBJS = ${SDL_EXT_SRCS:.c=.c.o}
SDL_INCLUDE = -I/usr/include/SDL -ISDL_ext
SDL_LIBS = -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image

all: libgameframework.a
libgameframework.a: ${SDL_EXT_OBJS} ${OBJS}
	ar rcs libgameframework.a $?
%.cpp.o: %.cpp
	${CC} ${SDL_INCLUDE} -c $< -o $@
SDL_ext/%.c.o: SDL_ext/%.c
	${CC} -std=c99 ${SDL_INCLUDE} -c $< -o $@
clean:
	-rm ${SDL_EXT_OBJS} ${OBJS}
