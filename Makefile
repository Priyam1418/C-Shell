all: build

build:
	@echo "Building"
	gcc -o shell comet.c

clean:
	@echo "Cleaning"
	rm shell
