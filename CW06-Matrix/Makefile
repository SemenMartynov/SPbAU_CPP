CXXFLAGS =	-m32 -O2 -g -Wall -fmessage-length=0

OBJS =		main.o

LIBS =

TARGET =	matrix

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
