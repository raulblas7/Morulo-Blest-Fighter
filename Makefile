DEPS = Vector2D.h Resources.h Texture.h TexturesManager.h Socket.h SDLGame.h\
	Player.h Game.h GameObject.h GameWorld.h GameClient.h GameServer.h Serializable.h\
	Client.h Server.h GameMessage.h InputHandler.h 
	
	

SERVER = Vector2D.o  Resources.o Socket.o  GameServer.o GameMessage.o Player.o
CLIENT = Vector2D.o  Resources.o Texture.o TexturesManager.o Socket.o GameMessage.o  SDLGame.o GameClient.o InputHandler.o Player.o
#LINKER_FLAGS specifies the libraries we're linking against
LIBS =  -lpthread 
LIBSSDL=-lSDL2 -lSDL2_image -lSDL2_ttf
%.o: %.cc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)
all: cs cc
cs: $(SERVER) Server.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
cc: $(CLIENT) Client.o
	g++ -o $@ $^ $(CFLAGS) `pkg-config --cflags --libs sdl2` $(LIBS) $(LIBSSDL) 
.PHONY: clean
clean:
	rm -f *.o server client