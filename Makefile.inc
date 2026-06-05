CXX = g++
CXXFLAGS = -std=c++17 -Werror -Wpedantic -Wall -Wextra -I/usr/include/eigen3 $(CXX_EXTRA_FLAGS)
CXXFLAGS_R = $(CXXFLAGS) -O3 -DNDEBUG
CXXFLAGS_D = $(CXXFLAGS) -g -DDEBUG
GTEST_LIBS = -lgtest -lgtest_main -lpthread
LD=$(CXX)

.PHONY: all release debug utest run_utest run_itest depends clean cleanall mrproper astyle tidy

%.d.o : %.cpp
	$(CXX) -c $(CXXFLAGS_D) -o $@ $<

%.r.o : %.cpp
	$(CXX) -c $(CXXFLAGS_R) -o $@ $<

clean :
	- rm *.o
	- rm *.hdrdep.bak

cleanall : clean
	- rm release debug debug_test utest base85 gauss random.bin random.b85 random.b85.test random.bin.test AB.actual.csv
	- echo > Makefile.hdrdep

mrproper : cleanall

astyle:
	astyle --options=../astyle.ini *.h *.cpp

tidy:
	../tidy.sh

depends :
	makedepend -I/usr/include/eigen3 $(CXX_EXTRA_FLAGS) -f Makefile.hdrdep *.c*
