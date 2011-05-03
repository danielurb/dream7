CXXFLAGS=-Wall -Wextra -Werror -pedantic -Wshadow -Wcast-qual -Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wstrict-aliasing -fstrict-aliasing -Wstrict-overflow=5 -fstrict-overflow -Wfloat-equal -Wundef -Wshadow -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wsign-conversion -Wlogical-op -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Winline -Winvalid-pch -Wvolatile-register-var -Wdisabled-optimization -fstack-protector
CXXFLAGS+=-Weffc++ -Wabi -Wctor-dtor-privacy -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo

CXXFLAGS+=-g

CPPFLAGS=
TARGET_ARCH=

VALGRIND_OPTIONS = --quiet --leak-check=full --error-exitcode=1

TARGET = test_compress
TARGET2 = test_decompress

OBJS = test_compress.o dream7.o
OBJS2 = test_decompress.o dream7.o

input = images/fisheye.mtv
output = fisheye.k
fixture = fixtures/fisheye.dr7
output2 = output.mtv

check : clean $(TARGET) $(TARGET2) 
	valgrind $(VALGRIND_OPTIONS) ./$(TARGET) < $(input) > $(output)
	cmp $(output) $(fixture)
	valgrind $(VALGRIND_OPTIONS) ./$(TARGET2) < $(output) > $(output2)
	cmp $(output2) $(input)

$(TARGET) : $(OBJS)
	g++ -o $@ $^

$(TARGET2) : $(OBJS2)
	g++ -o $@ $^


clean:
	rm -f $(output) $(TARGET) $(OBJS)

all : $(TARGET)
