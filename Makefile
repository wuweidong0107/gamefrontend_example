CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lSDL
SOURCES=main.cpp Renderer.cpp GuiComponent.cpp GuiTitleScreen.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=renderer_example

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ./*.o