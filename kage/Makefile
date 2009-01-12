.PHONY: clean all

INCLUDES = $(shell pkg-config --cflags OGRE OIS liblog4cxx) -Iinclude

LIBS = $(shell pkg-config --libs OGRE OIS liblog4cxx)

CXXFLAGS = -fPIC -O2 -g -Wall -fmessage-length=0 -ggdb -Wno-deprecated

DEFINES = -DDEBUG

OBJS = build/kage/fsm.o \
       build/kage/task.o \
       build/kage/application.o \
       build/kage/input.o \
       build/kage/input_buffered.o \
       build/kage/ois_input_buffered.o \
       build/kage/ogre_application.o \
       build/kage/logging.o

TARGET_NAME = libkage
MAJOR = 0
MINOR = 1

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
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $? -o $@

clean:
	rm -f $(OBJS) *.so *.so.* *.a *.a.*
