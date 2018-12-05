.PHONY: all
all:
	g++ *.cpp -o scp

.PHONY: clean
clean:
	rm -rf scp
