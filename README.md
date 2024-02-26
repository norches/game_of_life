# game_of_life implement by your humble friend Norch

## Description
This program is an implementation of Conway's Game of Life, a cellular automaton devised by the British mathematician John Horton Conway in 1970. The game is a zero-player game, meaning its evolution is determined by its initial state, requiring no further input. It consists of a grid of cells which, based on a set of rules, can live, die, or multiply over iterations.

### Key features of this implementation include:

#### Dynamic Grid: 
Utilizes a grid of HEIGHT (25) by WIDTH (80) cells, where each cell can either be alive or dead. <br>
User Input: Allows users to input coordinates for initially alive cells through standard input (stdin) until a sentinel value (-1, -1) is entered. <br>
Simulation Rules: Follows the classic rules of Conway's Game of Life: <br>
- A live cell with fewer than two live neighbors dies (underpopulation). <br>
- A live cell with two or three live neighbors lives on to the next generation. <br>
- A live cell with more than three live neighbors dies (overpopulation). <br>
- A dead cell with exactly three live neighbors becomes a live cell (reproduction). <br>
#### Graphical Output: 
Uses ncurses for drawing the grid to the terminal, updating the display in real-time to show the progression of the cell population. <br>
#### Interactive Controls: Allows users to control the simulation in real-time:
h to pause/resume the simulation. <br>
q to quit the program. <br>
Space ( ) to manually advance to the next generation. <br>
Arrow keys to adjust the simulation speed. <br>
#### Memory Management: 
Dynamically allocates and deallocates memory for the cell grid, ensuring efficient use of resources. <br>
#### Safety and Cleanup: 
Includes cleanup routines to ensure the terminal settings are restored upon program exit, using atexit to register a cleanup function. <br>
Overall, this program is a complex and interactive implementation of Conway's Game of Life, showcasing dynamic data structures, user interaction, and graphical output in a console application. <br>

## Compiling and Running:
- Compile with `-lncurses` flag
- Simply run executable without arguments `gcc game_of_life.c -lncurses -o "bin/a.out" && bin/a.out`
- There is various initial configs in `configs` folder to use, you can use `|` (pipe) to simplify initial input like so: `cat configs/21school.conf | bin/a.out`

## How to play:
- Set up initial state by stdin, providing `x,y` coordinates of live cells, `-1,-1` means end of input
- The grid is 80x25
- `q` for `Quit`
- `h` for `Halt`
- `KEY_UP` for +Speed
- `KEY_DOWN` for -Speed
- `(space)` for Next step in Halted state


