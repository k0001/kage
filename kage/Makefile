INCLUDES = $(shell pkg-config --cflags OGRE OIS) -Iinclude

CXXFLAGS = -fPIC -O2 -g -Wall -fmessage-length=0 -ggdb -DDEBUG

OBJS = build/kage/application_state.o \
       build/kage/application.o

LIBS = $(shell pkg-config --libs OGRE OIS)

TARGET = libkage.so
MAJOR = $(TARGET).1
REV = $(MAJOR).0

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -shared -Wl,-soname,$(MAJOR) -o $(REV)
	ln -sf $(REV) $(MAJOR)
	ln -sf $(MAJOR) $(TARGET)

build/kage/%.o: src/kage/%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $? -o $@

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(MAJOR) $(REV)
