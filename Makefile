CXXFLAGS=-Wall -Wextra -Werror -pedantic -Wshadow -Wcast-qual -Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wstrict-aliasing -fstrict-aliasing -Wstrict-overflow=5 -fstrict-overflow -Wfloat-equal -Wundef -Wshadow -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wsign-conversion -Wlogical-op -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Winline -Winvalid-pch -Wvolatile-register-var -Wdisabled-optimization -fstack-protector

CXXFLAGS+=-Weffc++ -Wabi -Wctor-dtor-privacy -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo

CXXFLAGS+=-g

TARGET = test_compress

OBJS = test_compress.o dream7.o

input = images/fisheye.mtv
output = fisheye.k
fixture = fixtures/fisheye.dr7

check : clean $(TARGET)
	valgrind --quiet --leak-check=full --error-exitcode=1 ./$(TARGET) < $(input) > $(output)
	cmp $(output) $(fixture)

$(TARGET) : $(OBJS)
	g++ -o $@ $^


clean:
	rm -f $(output) $(TARGET) $(OBJS)

all : $(TARGET)
