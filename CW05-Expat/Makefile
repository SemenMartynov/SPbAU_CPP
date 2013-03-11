CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		main.o

LIBS =		-lexpat

TARGET =	xmlparser

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
