OPT = -O2
CFLAGS = -I../../opus-dist/include
CFLAGS = -I../include

opus_encode: opus_encode.c ../../opus-dist/lib/libopus.a
	gcc -o $@ $(OPT) $(CFLAGS) -lm $^

pack_file: pack_file.cpp
	g++ -o $@ $(OPT) $(CFLAGS) $^
