CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11

CPP_FILES = $(wildcard *.cpp) $(wildcard ui/*.cpp)

OBJS =		$(CPP_FILES:.cpp=.o)

LIBS = -lSDL2

TARGET =	sdl_gui

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
