#                            GameOfLife

[1] https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

# THE PROGRAM:
I intended to create my own version of the game of life.
In a few words, this program simulates a cellular automaton, in which the cells can be alive or dead.
Each generation of alive or dead cells is determined by specific rules [1]

# INITIAL STATE:
The evolution is determined by the initial state, and in my version of the program the initial configuration
is determined randomly, as the grid is filled with cells which are initially either alive or dead.

# DISPLAY:
The result is displayed with graphics, the attached module gol_display.c and header file gol_display.h
are based on the module from the sketch program, but extended for the needs of the program.
The alive cells are denoted with dark blue color and the dead with light grey color.

# RUNNING GOL:
> The program runs infinetely in order for the user to watch and observe how the specific random initial 
configuration of cells evolves in time. Of course, the program can be terminated with CNTR+C

> Also the program can enter a testing mode as follows:    ./gol test

> Finally, there is a capability to observe the game of life more carefully step by step. 
I have commented a key(d) function into the int main(), so if you want to inspect the simulation generation by generation 
you could include the key(d) function.

# NOTES:
I have hard coded some of the dimensions to the program that I found ideal, but note that I just wrote these 
values as constants at the beginning of the program, and all the rest, like the dimensions of the display window etc. 
is dynamic according to whatever initial dimensions.


Compile line:	clang -std=c11 -Wall -pedantic -g gol.c gol_display.c -lSDL2 -o gol \
	    -fsanitize=undefined -fsanitize=address
Run line:	./gol
