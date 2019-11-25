SOURCES=$(wildcard *.c)
INCLUDES=$(wildcard *.h)

proj.out: $(SOURCES) $(INCLUDES)
	gcc -g -flto -Wall -Werror -Wextra -fsanitize=address -fsanitize=undefined $(SOURCES) -o proj.out  

test: proj.out
	./proj.out

clean:
	rm ./proj.out

.PHONY: test