CPPFLAGS=-Wall -Wextra -Werror -pedantic -Wshadow -Wcast-qual -Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wstrict-aliasing -fstrict-aliasing -Wstrict-overflow=5 -fstrict-overflow -Wfloat-equal -Wundef -Wshadow -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wsign-conversion -Wlogical-op -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Winline -Winvalid-pch -Wvolatile-register-var -Wdisabled-optimization -Wstack-protector -fstack-protector

CPPFLAGS+=-Weffc++ -Wabi -Wctor-dtor-privacy -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo




check : test_compress
	./test_compress
	cmp fisheye.k fixtures/fisheye.dr7
  
all : test_compress
