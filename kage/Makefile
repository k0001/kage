INCLUDES = $(shell pkg-config --cflags OGRE OIS) -Iinclude

CXXFLAGS = -fPIC -O2 -g -Wall -fmessage-length=0 -ggdb -DDEBUG -Wno-deprecated

OBJS = build/kage/state.o \
       build/kage/application.o \
       build/kage/ogre_application.o \

LIBS = $(shell pkg-config --libs OGRE OIS)

TARGET_NAME = libkage
MAJOR = 1
MINOR = 0

SHARED_TARGET = $(TARGET_NAME).so
SHARED_MAJOR = $(SHARED_TARGET).$(MAJOR)
SHARED_MINOR = $(SHARED_MAJOR).$(MINOR)

STATIC_TARGET = $(TARGET_NAME).a
STATIC_MAJOR = $(STATIC_TARGET).$(MAJOR)
STATIC_MINOR = $(STATIC_MAJOR).$(MINOR)

all: $(STATIC_TARGET) $(SHARED_TARGET)

$(SHARED_TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -shared -Wl,-soname,$(SHARED_MAJOR) -o $(SHARED_MINOR)
	ln -sf $(SHARED_MINOR) $(SHARED_MAJOR)
	ln -sf $(SHARED_MAJOR) $(SHARED_TARGET)

$(STATIC_TARGET): $(OBJS)
	rm -rf $(STATIC_MINOR)
	ar cqs $(STATIC_MINOR) $(OBJS)
	ln -sf $(STATIC_MINOR) $(STATIC_MAJOR)
	ln -sf $(STATIC_MAJOR) $(STATIC_TARGET)

build/kage/%.o: src/kage/%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $? -o $@


clean:
	rm -f $(OBJS) *.so *.so.* *.a *.a.*
