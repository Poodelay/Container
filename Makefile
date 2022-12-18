folder = build

.PHONY: generate build clean

generate:
	mkdir -p $(folder); \
	cd $(folder); \
	cmake ..

build: generate
	cmake --build ./$(folder) -j 8

clean:
	rm -rf $(folder)
