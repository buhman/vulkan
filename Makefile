CC=$(PREFIX)gcc
CXX=$(PREFIX)g++
OBJCOPY=$(PREFIX)objcopy
AS=$(PREFIX)as

OBJARCH = elf64-x86-64

UNAME := $(shell uname -s)

OPT += -O0 	-march=x86-64-v3

DEBUG = -g

CSTD = -std=gnu23
CXXSTD = -std=gnu++23
CFLAGS += -Wall -Werror
CFLAGS += -Wfatal-errors
CFLAGS += -Wno-error=unused-variable -Wno-error=unused-but-set-variable
CFLAGS += -Wno-error=unused-function
CFLAGS += -Wno-error=array-bounds
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -fno-strict-aliasing
CFLAGS += -I./include
CFLAGS += -I../SDL3-dist/include
CFLAGS += -fpic

FLAGS += -fstack-protector -fstack-protector-all -fno-omit-frame-pointer -fsanitize=address

LDFLAGS += -lm
ifeq ($(UNAME),Linux)
LDFLAGS += -Wl,-z noexecstack
endif
ifeq ($(UNAME),Darwin)
LDFLAGS += -framework Foundation -framework Cocoa -framework IOKit -framework AVFoundation -framework CoreVideo -framework CoreAudio -framework CoreMedia -framework CoreHaptics -framework AudioToolbox -framework GameController -framework ForceFeedback -framework Carbon -framework Metal -framework QuartzCore -framework UniformTypeIdentifiers
LDFLAGS += -lstdc++
endif

OBJS = \
	src/main.o \
	src/volk/volk.o \
	src/file.o \
	src/pack.o

ifeq ($(UNAME),Darwin)
LIBS = \
	 ../SDL3-dist/lib/libSDL3.a
else
LIBS = \
	 ../SDL3-dist/lib64/libSDL3.a
endif

all: main

%.o: %.c
	$(CC) $(ARCH) $(CSTD) $(CFLAGS) $(FLAGS) $(OPT) $(DEBUG) -c $< -o $@

%.o: %.cpp
	$(CXX) $(ARCH) $(CXXSTD) $(CFLAGS) $(FLAGS) $(OPT) $(DEBUG) -c $< -o $@

%.o: %.s
	$(AS) $< -o $@

main: $(OBJS) $(LIBS) $(BINS) $(SHADERS)
	$(CC) $(ARCH) $(LDFLAGS) $(FLAGS) $(OPT) $(DEBUG) $^ -o $@

%.vs.spv: %.hlsl
	../dxc/bin/dxc -spirv -T vs_6_1 -E VSMain -fspv-target-env=vulkan1.3 $< -Fo $@

%.ps.spv: %.hlsl
	../dxc/bin/dxc -spirv -T ps_6_1 -E PSMain -fspv-target-env=vulkan1.3 $< -Fo $@

tool/pack_file: tool/pack_file.cpp
	make -C tool pack_file

PACK_FILENAMES = $(shell cat filenames.txt)
files.pack: tool/pack_file $(PACK_FILENAMES) filenames.txt
	./tool/pack_file $@ $(PACK_FILENAMES)

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean phony dist

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
