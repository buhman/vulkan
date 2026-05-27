ZLIB=$HOME/zlib-1.3.2
set -eux
gcc -I$ZLIB compress.c $ZLIB/compress.o $ZLIB/deflate.o $ZLIB/trees.o $ZLIB/zutil.o $ZLIB/crc32.o $ZLIB/adler32.o -o compress
