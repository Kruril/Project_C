# SOURCES=$(find . -name "*.c")
INCLUDES=$(wildcard *.h)

proj.out:  $(INCLUDES) 
	 gcc $(find . -name "*.c") -o proj.out 

test: proj.out
	./proj.out

clean:
	rm ./proj.out

.PHONY: test