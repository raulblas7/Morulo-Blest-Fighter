#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
#CFLAGS = -w

#DEPS = Vector2D.h Resources.h Texture.h TextureManager.h Socket.h Game.h GameServer.h SDLGame.h Player.h GameObject.h Client.h GameClient.h Bullet.h BulletsMotion.h BulletsPool.h Component.h ecs.h Font.h FontsManager.h GameObject.h GameWorld.h  InputHandler.h  MoruloBlestFighter.h OBjectPool.h SDL_macros.h  
#DEPS = Vector2D.h  Resources.h SDLTexture.h TextureManager.h Socket.h Message.h GameServer.h SDLApp.h Jugador.h GameObject.h ChatClient.h ChatServer.h

#LINKER_FLAGS specifies the libraries we're linking against
LIBS =  -lpthread 
LIBSSDL=-lSDL2 -lSDL2_image -lSDL2_ttf

TARGET= $(BIN_DIR)/Moruloblest
INC_DIR = ../include
BIN_DIR =  ../bin
OBJ_DIR =  ../obj
SRC_DIR = .

OBJS=   $(OBJ_DIR)Socket.o \
		$(OBJ_DIR)Message.o \
		$(OBJ_DIR)Game.o \
		$(OBJ_DIR)GameServer.o

CLIENT= Vector2D.o  Resources.o SDLTexture.o TextureManager.o Socket.o Message.o SDLApp.o Jugador.o GameObject.o


CFLAGS = -Wall -I$(INC_DIR)



$(TARGET):$(OBJS)
	mkdir -p $(BIN_DIR)
	g++ $(CFLAGS) $(OBJS) -o $(TARGET)
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	mkdir -p $(OBJ_DIR)
	g++  -g -c $(CFLAGS) $< -o $@


-include $(OBJ_DIR)/*.d

#all: Server Client
#Server: $(SERVER) GameServer.o
#	g++ -o $@ $^ $(CFLAGS) $(LIBS)
#Client: $(CLIENT) GameClient.o
#	g++ -o $@ $^ $(CFLAGS) `pkg-config --cflags --libs sdl2` $(LIBS) $(LIBSSDL) 



.PHONY: clean
clean:
	rm -r $(OBJ_DIR) $(BIN_DIR)

