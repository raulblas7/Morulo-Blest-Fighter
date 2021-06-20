CC = g++
#CFLAGS = -g -I.
DEPS   = GameServer.h  GameClient.h GameMessage.h  Socket.h GameWorld.h GameObject.h  Player.h Vector2D.h Resources.h Texture.h TexturesManager.h Serializable.h SDLGame.h InputHandler.h 
CLIENT = GameClient.o  GameMessage.o Socket.o GameWorld.o GameObject.o Player.o  Vector2D.o  Resources.o  Texture.o  TexturesManager.o  SDLGame.o  InputHandler.o 
SERVER = GameServer.o GameMessage.o Socket.o GameWorld.o GameObject.o   Vector2D.o  Resources.o  Player.o Texture.o
LIBS   =  -lpthread 
LIBSSDL=-lSDL2 -lSDL2_image -lSDL2_ttf
%.o: %.cc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)
all: cs cc
cs: $(SERVER) Server.o
	g++ -o $@ $^ $(CFLAGS) `pkg-config --cflags --libs sdl2` $(LIBS) $(LIBSSDL) 
cc: $(CLIENT) Client.o
	g++ -o $@ $^ $(CFLAGS) `pkg-config --cflags --libs sdl2` $(LIBS) $(LIBSSDL) 
.PHONY: clean
clean:
	rm -f *.o server client