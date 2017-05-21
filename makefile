all:
	g++ -std=c++11 *.cpp -lncurses

clean:
	find -name '*~' | xargs rm -f
	rm *.out
