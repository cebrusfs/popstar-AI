#
#popstar_ai_debug: popstar_ai.cpp
#	g++-7 $< -g -Wall -Wextra -std=c++1z -lpthread -fopenmp -DFISH -o $@

TARGET = popstar_ai_openmp simulator
all: $(TARGET)

simulator: simulator.cpp Makefile
	g++-7 $< -Ofast -Wall -Wextra -std=c++1z -DFISH -o $@

popstar_ai_openmp: popstar_ai.cpp Makefile
	g++-7 $< -Ofast -Wall -Wextra -std=c++1z -lpthread -fopenmp -DFISH -o $@
popstar_ai: popstar_ai.cpp Makefile
	g++-7 $< -Ofast -Wall -Wextra -std=c++1z -DFISH -o $@

clean:
	rm $(TARGET)
