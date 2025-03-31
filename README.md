# Description
This program was made to solve labyrinths provided by the user in .txt format. It comes with a simple menu to ease usage. The .txt file needs to be in the parent directory.

# Technical challenges
We had to implement the A* Algorithm from scratch which was initially difficult, and due to the way we subdivided the codebase in different modules, the debugger sometimes couldn't access private parts of memory for the dynamic "voisin" array for example which handled finding neighboring tiles to the one the algorithm was taking. This made the developpment of the program difficult, therefore, by utilizing Windows Terminal escape code knowledge we rendered the labyrinth and the path the algorithm took, which allowed us to find a critical bug that stopped the function of the program. Indeed, when the algorithm would search for a path, if the shortest path was blocked by some wall, it would go back and forth indefinitely, and fixing this bug in the calculationn of the "voisin" array sped up the execution of the program and allowed it to actually solve any labyrinth.
