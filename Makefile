CXX = g++
CXXFLAGS = -g -O2 -Wall -fPIC
LD = g++
LDFLAGS =
DEFINES = -DNDEBUG

all: libagsshell.so

clean:
	rm -f libagsshell.so *.o test

runtest: test
	LD_LIBRARY_PATH=. ./$<

libagsshell.so: agsshell.o
	$(LD) $(LDFLAGS) -shared -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEFINES) -o $@ -c $^
