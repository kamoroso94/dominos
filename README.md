# `dominos`
A command line program to find the optimal starting domino chain using a brute force search algorithm with backtracking.

## About Dominos with Blank Sides
Dominos with a blank side on them should have that side be entered as `0`.
The sides of these dominos are considered to be wild cards that can match against any dot pattern.
The domino with two blank sides will have its sides treated independently.
If you want to treat the sides dependently, then don't include it in the program input
and simply insert it anywhere into the resulting chain displayed at the end of the program.

## How to Compile
```
gcc -o dominos dominos.c
```

## How to Run
Supply the number of dominos you start off with in your hand as a command line argument.
```
./dominos 15
```

## Sample Output
The program will prompt you for the starting double domino, and then for each domino in your hand.
Enter dominos as a space separated pair of integers.
The sides of the dominos are output in the same order as they were input.
For the dominos in the chain to connect, you may have to rotate some.
```
./dominos 5
Enter starting domino (%top %bottom): 4 4
From your hand...
Enter domino 1 (%top %bottom): 1 2
Enter domino 2 (%top %bottom): 2 3
Enter domino 3 (%top %bottom): 3 3
Enter domino 4 (%top %bottom): 3 1
Enter domino 5 (%top %bottom): 0 4
Best chain: [0 4], [1 2], [2 3], [3 3], [3 1].
```
