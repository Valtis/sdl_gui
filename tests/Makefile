CXX = g++
CXXFLAGS =	-g -Wall -fmessage-length=0 -std=c++11

CPP_FILES = $(wildcard *.cpp) $(wildcard ../ui/*.cpp) $(wildcard ../ui/components/*.cpp) $(wildcard ../ui/creation/*.cpp) $(wildcard ../serialization/*.cpp) $(wildcard ../ui/utility/*.cpp)

OBJS =		$(CPP_FILES:.cpp=.o)

LIBS = -lpugixml -lSDL2 -lSDL2_ttf -lcppunit
 
TARGET =	sdl_gui

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

test: clean all 

clean:
	rm -f $(OBJS) $(TARGET)
