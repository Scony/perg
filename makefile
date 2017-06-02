all: build

test: build
	./build/test/perg-test

build:
	mkdir -p build && cd build && cmake .. && make -j

clean:
	find -name '*~' | xargs rm -f
	rm -rf build

.PHONY: clean test build
