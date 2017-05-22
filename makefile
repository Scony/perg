all:
	g++ -std=c++11 *.cpp -lncurses -o perg

clean:
	find -name '*~' | xargs rm -f
	rm -f perg
