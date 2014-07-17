CXX = g++
CXXFLAGS = -g -Wall -fmessage-length=0 -std=c++11

CPP_FILES = $(wildcard *.cpp) $(wildcard src/*.cpp) $(wildcard src/components/*.cpp) $(wildcard src/creation/*.cpp) \
$(wildcard src/serialization/*.cpp) $(wildcard src/utility/*.cpp) $(wildcard src/rendering/*.cpp)

OBJS =		$(CPP_FILES:.cpp=.o)

LIBS = -lpugixml -lSDL2 -lSDL2_ttf
 
TARGET =	sdl_gui

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
