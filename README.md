# Leap Frog Puzzle
## About the Puzzle
The objective of the puzzle is to switch the positions of the frogs on the left side with the frogs on the right side.

## Game rules
### Start state
![Start](https://github.com/luntropy/leap-frog-puzzle/blob/main/images/start-state.png)

- The movement of the frogs is in only one direction, they can not turn back
- The left set of frogs are allowed to move only to the right
- The right set of frogs are allowed to move only to the left
- The frogs are allowed to jump only on empty lily
- Movement can be one or two lilies forward
- Jumping over another frog is allowed

### Goal
The puzzle is solved when the two sets of frogs switch their positions.

### Goal state
![Goal](https://github.com/luntropy/leap-frog-puzzle/blob/main/images/goal-state.png)

### Play the game (by Shaun Carter) [Play](https://primefactorisation.com/frogpuzzle/)

## About the program
The program creates a space of all possible movements of the frogs based of the given rules and then using the algorithm Depth-first search to find the solution.
The current lake finds the solution for a lake with 4 frogs and 5 lilies.

### To run the program
- Build it using `make`
- Run `./main`

### Output
- On the first line is the Start state
- On the last line in the Goal state
- The states in between them are the movements that lead to the given Goal

### Frogs representation in the program
- The number 2 represents the left set of frogs
- The number 1 represents the right set of frogs
