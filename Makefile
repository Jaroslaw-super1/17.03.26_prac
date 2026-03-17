CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14 -MMD

top-vect: main.o
	g++ -o $@ $^

-include main.d

clean:
	rm -rf *.d *.o top-vect