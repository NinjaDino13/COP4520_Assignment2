# COP4520_Assignment2
## Problem 1: Minotaur's Birthday Party
### Winning Strategy
The strategy chosen to complete the Minotaur's request of knowing when all guest have experience the labyrinth is as follows:

Since the guest know that there is a cupcake at the end of labyrinth at the start of the party, they can use that information to determine whether or not another guest has come into the labyrinth before them. If a guest goes in and see no cupcake there, that guest knows for a fact that another guest has been through the labyrinth already, as that is the only reason the cupcake would be missing. Using that, we can designate one guest as the counter, for this strategy that will always be guest 0, and they will be the only guest allowed to call the servants and bring back the cupcake. Whenever guest 0 enters the labyrinth, they will move to the end of the maze and check the status of the cupcake. If there is not a cupcake there, they will add one to the count of guests who have entered the labyrinth and tell the servants to bring back another cupcake. If there is still a cupcake there, guest 0 wil simply leave the labyrinth without doing anything. As for the other guests, whenever they enter the labyrinth, they will also check the status of the cupcake. If the cupcake is there and they have not eaten a cupcake yet, they will eat the cupcake and leave. Otherwise if the guest finds no cupcake or they have already eaten a cupcake, the guest will simply leave the labyrinth without doing anything. Once guest 0 has counted *n* guests, he will notify the Minotaur that everyone has experienced the labyrinth.

### Running the Program
To run the program, open up a command prompt window. From there enter:
```
g++ Assignment2_1.cpp -o Assignment2_1.exe
```
This will compile the code and create the .exe file for it, named Assignment2_1.exe. Once this has been created, enter the following in to the command line:
```
./Assignment2_1.exe
```
This will run the code within the command prompt.

## Problem 2: Minotaur's Crystal Vase
### Winning Strategy

### Running the Program
To run the program, open up a command prompt window. From there enter:
```
g++ Assignment2_2.cpp -o Assignment2_2.exe
```
This will compile the code and create the .exe file for it, named Assignment2_2.exe. Once this has been created, enter the following in to the command line:
```
./Assignment2_2.exe
```
This will run the code within the command prompt.