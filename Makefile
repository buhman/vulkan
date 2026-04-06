CC=$(PREFIX)gcc
CXX=$(PREFIX)g++
OBJCOPY=$(PREFIX)objcopy

OBJARCH = elf64-x86-64

OPT = -O0 -march=x86-64-v3

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
CFLAGS += -I../volk
CFLAGS += -fpic

#FLAGS += -fstack-protector -fstack-protector-all -fno-omit-frame-pointer -fsanitize=address

LDFLAGS += -lm
ifeq ($(shell uname),Linux)
LDFLAGS += -Wl,-z noexecstack
endif

OBJS = \
	src/main.o

BINS = \
	index.idx.o \
	position_normal_texture.vtx.o \
	sprite.data.o

SHADERS = \
	shader/triangle.vs.spv.o \
	shader/triangle.ps.spv.o

LIBS = \
	 ../SDL3-dist/lib64/libSDL3.a \
	../volk/volk.o

all: main

define BUILD_BINARY_O
	$(OBJCOPY) -I binary -O $(OBJARCH) $< $@
endef

%.vtx.o: %.vtx
	$(BUILD_BINARY_O)

%.idx.o: %.idx
	$(BUILD_BINARY_O)

%.spv.o: %.spv
	$(BUILD_BINARY_O)

%.data.o: %.data
	$(BUILD_BINARY_O)

%.o: %.c
	$(CC) $(ARCH) $(CSTD) $(CFLAGS) $(FLAGS) $(OPT) $(DEBUG) -c $< -o $@

%.o: %.cpp
	$(CXX) $(ARCH) $(CXXSTD) $(CFLAGS) $(FLAGS) $(OPT) $(DEBUG) -c $< -o $@

main: $(OBJS) $(LIBS) $(BINS) $(SHADERS)
	$(CC) $(ARCH) $(LDFLAGS) $(FLAGS) $(OPT) $(DEBUG) $^ -o $@

%.vs.spv: %.hlsl
	../dxc/bin/dxc -spirv -T vs_6_1 -E VSMain -fspv-target-env=vulkan1.3 $< -Fo $@

%.ps.spv: %.hlsl
	../dxc/bin/dxc -spirv -T ps_6_1 -E PSMain -fspv-target-env=vulkan1.3 $< -Fo $@

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean phony dist

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
