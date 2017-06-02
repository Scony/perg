all:
	mkdir -p build && cd build && cmake .. && make -j

clean:
	find -name '*~' | xargs rm -f
	rm -rf build
