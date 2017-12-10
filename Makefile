CXX=g++-7
#popstar_ai_debug: popstar_ai.cpp
#	$(CXX) $< -g -Wall -Wextra -std=c++1z -lpthread -fopenmp -DFISH -o $@

TARGET = popstar_ai_openmp simulator
#TARGET += popstar_ai

all: $(TARGET)

simulator: simulator.cpp Makefile
	$(CXX) $< -Ofast -Wall -Wextra -std=c++1z -DFISH -o $@

popstar_ai_openmp: popstar_ai.cpp Makefile
	$(CXX) $< -Ofast -Wall -Wextra -std=c++1z -lpthread -fopenmp -DFISH -o $@
popstar_ai: popstar_ai.cpp Makefile
	$(CXX) $< -Ofast -Wall -Wextra -std=c++1z -DFISH -o $@

clean:
	rm $(TARGET)
