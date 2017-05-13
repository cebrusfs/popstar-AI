#
#popstar_ai_debug: popstar_ai.cpp
#	g++-7 $< -g -Wall -Wextra -std=c++1z -lpthread -fopenmp -DFISH -o $@

all: popstar_ai_openmp simulator

simulator: simulator.cpp Makefile
	g++-7 $< -Ofast -Wall -Wextra -std=c++1z -DFISH -o $@

popstar_ai_openmp: popstar_ai.cpp Makefile
	g++-7 $< -Ofast -Wall -Wextra -std=c++1z -lpthread -fopenmp -DFISH -o $@
popstar_ai: popstar_ai.cpp Makefile
	g++-7 $< -Ofast -Wall -Wextra -std=c++1z -DFISH -o $@
