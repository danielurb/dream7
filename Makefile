CPPFLAGS=-Wall

check : test_compress
	./test_compress
	cmp fisheye.k fixtures/fisheye.dr7
  
all : test_compress
