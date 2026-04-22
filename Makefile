CC=$(PREFIX)gcc
CXX=$(PREFIX)g++
OBJCOPY=$(PREFIX)objcopy
AS=$(PREFIX)as

OBJARCH = elf64-x86-64

UNAME := $(shell uname -s)

OPT += -Os
OPT += -march=core-avx2

DEBUG = -g

CSTD = -std=gnu17
CXXSTD = -std=gnu++20
CFLAGS += -Wall -Werror
CFLAGS += -Wfatal-errors
CFLAGS += -Wno-error=unused-variable
#CFLAGS += -Wno-error=unused-but-set-variable
CFLAGS += -Wno-format-security
CFLAGS += -Wno-format
CFLAGS += -Wno-error=unused-function
CFLAGS += -Wno-error=array-bounds
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -fno-strict-aliasing
CFLAGS += -I./include
CFLAGS += -I./data
CFLAGS += -I../SDL3-dist/include
ifeq ($(UNAME),Darwin)
CFLAGS += -I../MoltenVK/MoltenVK/include
endif
CFLAGS += -I../opus-dist/include
CFLAGS += -fpic
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections

#FLAGS += -fstack-protector -fstack-protector-all -fno-omit-frame-pointer -fsanitize=address

LDFLAGS += -lm
#LDFLAGS += -Wl,--gc-sections
#-Wl,--print-gc-sections
ifeq ($(UNAME),Linux)
LDFLAGS += -Wl,-z noexecstack
endif
ifeq ($(UNAME),Darwin)
LDFLAGS += -framework Foundation -framework Cocoa -framework IOKit -framework AVFoundation -framework CoreVideo -framework CoreAudio -framework CoreMedia -framework CoreHaptics -framework AudioToolbox -framework GameController -framework ForceFeedback -framework Carbon -framework Metal -framework QuartzCore -framework UniformTypeIdentifiers
LDFLAGS += -lstdc++
#LDFLAGS += ../MoltenVK/MoltenVK/static/MoltenVK.xcframework/macos-arm64_x86_64/libMoltenVK.a
LDFLAGS += -framework IOSurface
LDFLAGS += ../MoltenVK-1.4.0/libMoltenVK.a-x86_64-master.o
endif

#	src/collada/scene/vulkan.o \
#	src/collada/scene/reload.o \
#	src/collada/scene.o \
#	src/collada/node_state.o \
#	src/collada/animate.o \
#	src/minecraft/world.o \
#	src/minecraft/entry_table.o \
#	src/minecraft/vulkan.o \
#	src/minecraft/vulkan/per_world.o \

OBJS = \
	src/main.o \
	src/file.o \
	src/pack.o \
	src/dds/validate.o \
	src/vulkan_helper.o \
	src/tga/tga.o \
	src/font/outline.o \
	src/renpy/vulkan.o \
	src/renpy/script.o \
	src/renpy/interpreter.o \
	src/renpy/interact.o \
	src/audio.o

ZLIB = ../zlib-1.3.2
CFLAGS += -I$(ZLIB)
OBJS += \
	$(ZLIB)/uncompr.o \
	$(ZLIB)/inflate.o \
	$(ZLIB)/inffast.o \
	$(ZLIB)/inftrees.o \
	$(ZLIB)/trees.o \
	$(ZLIB)/zutil.o \
	$(ZLIB)/crc32.o \
	$(ZLIB)/adler32.o

ifneq ($(UNAME),Darwin)
OBJS += src/volk/volk.o
endif

ifeq ($(UNAME),Darwin)
LIBS = \
	../SDL3-dist/lib/libSDL3.a \
	../opus-dist/lib/libopus.a
else
LIBS = \
	../SDL3-dist/lib64/libSDL3.a \
	../opus-dist/lib/libopus.a
endif

all: main

%.o: %.c
	$(CC) $(ARCH) $(CSTD) $(CFLAGS) $(FLAGS) $(OPT) $(DEBUG) -c $< -o $@

%.o: %.cpp
	$(CXX) $(ARCH) $(CXXSTD) $(CFLAGS) $(FLAGS) $(OPT) $(DEBUG) -c $< -o $@

%.o: %.s
	$(AS) $< -o $@

#%.dds: %.png
#	WINEDEBUG=-all wine $(HOME)/Texconv.exe -y -nogpu -nowic -dx10 --format BC7_UNORM_SRGB -m 1 $< -o $(dir $@)

%.pcm: %.wav
	ffmpeg -loglevel quiet -y -i $< -c:a pcm_s16le -ar 48000 -ac 2 -f s16le $@

%.pcm: %.ogg
	ffmpeg -loglevel quiet -y -i $< -c:a pcm_s16le -ar 48000 -ac 2 -f s16le $@

%.pcm: %.mp3
	ffmpeg -loglevel quiet -y -i $< -c:a pcm_s16le -ar 48000 -ac 2 -f s16le $@

%.opus.bin: %.pcm
	./tools/opus_encode $< $@

main: $(OBJS) $(LIBS)
	$(CC) $(ARCH) $(LDFLAGS) $(FLAGS) $(OPT) $(DEBUG) $^ -o $@

#%.spv: %.hlsl
#	../dxc/bin/dxc -spirv -T lib_6_3 -fspv-target-env=vulkan1.3 $< -Fo $@

tool/pack_file: tool/pack_file.cpp
	make -C tool pack_file

%.pack.zlib: %.pack
	./tools/compress $< $@

src/pack.o: files.pack.zlib

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
