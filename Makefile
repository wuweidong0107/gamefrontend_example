CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lSDL -lSDL_ttf -lboost_system -lboost_filesystem
SOURCES=main.cpp \
Renderer.cpp GuiComponent.cpp GuiTitleScreen.cpp InputManager.cpp \
GUIList.cpp GuiGameList.cpp GameData.cpp SystemData.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=frontend

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ./*.o