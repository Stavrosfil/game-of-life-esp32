# Conway's Game of Life on ESP32

> The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine. [Wikipedia article](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

## Rules

The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

- Any live cell with fewer than two live neighbours dies, as if by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

- Any live cell with two or three live neighbours survives.
- Any dead cell with three live neighbours becomes a live cell.
- All other live cells die in the next generation. Similarly, all other dead cells stay dead.

The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules simultaneously to every cell in the seed; births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations. 

## Implementation

In this code, the initial seed is just random values in an 64x128 sized array, same number of cells as the OLED screen we display it into. Each cell has either the value `1` or `0` denoting alive or dead.

The game evolves on a [toroidal surface](https://en.wikipedia.org/wiki/Torus), and an 8-neighbor sum is computed for each cell.

### Functions

- `createRandomMatrix` Initializes a given matrix randomly, given an uninitialized array of the correct size.
- `gameOfLife` Is called on every new generation, takes the current plane as argument and iterates forward according to game rules.
- `addGlider` adds a glider, a special kind of initialized cell group that "glides" to the side in every iteration, given `x` and `y` coordinates on the plane.

## Photos and wiring

![ESP32](.github/photo.jpg)
![wiring](.github/wiring.png)
