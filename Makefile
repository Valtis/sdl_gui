CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11

CPP_FILES = $(wildcard *.cpp) $(wildcard **/*.cpp)

OBJS =		$(CPP_FILES:.cpp=.o)

LIBS = -lSDL2 -lpugixml

TARGET =	sdl_gui

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
