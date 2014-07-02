CXX = g++
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11

CPP_FILES = $(wildcard *.cpp) $(wildcard ui/*.cpp) $(wildcard ui/components/*.cpp) $(wildcard ui/creation/*.cpp) $(wildcard serialization/*.cpp)

OBJS =		$(CPP_FILES:.cpp=.o)

LIBS = -lpugixml -lSDL2 

TARGET =	sdl_gui

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
