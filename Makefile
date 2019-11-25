# INCORECTE

# SOURCES=$(wildcard *.c)
# INCLUDES=$(wildcard *.h)

proj.out: 
	gcc $(find . -name "*.c") -o proj.out  

test: proj.out
	./proj.out

clean:
	rm ./proj.out

.PHONY: test