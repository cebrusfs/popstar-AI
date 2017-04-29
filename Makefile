#
#popstar_ai_debug: popstar_ai.cpp
#	g++-6 $< -g -Wall -Wextra -std=c++1z -lpthread -fopenmp -DFISH -o $@

popstar_ai_openmp: popstar_ai.cpp
	g++-6 $< -Ofast -Wall -Wextra -std=c++1z -lpthread -fopenmp -DFISH -o $@
popstar_ai: popstar_ai.cpp
	g++-6 $< -Ofast -Wall -Wextra -std=c++1z -DFISH -o $@
