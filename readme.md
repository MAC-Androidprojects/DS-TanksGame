# Tanks-Game

This is the code for the `Data structure` project It's a game between you and the computer in which the computer tries to find your place and throw tanks on you and you have to avoid them

> **Warning**: This game is only for those who have brave hearts

## How to run the code

- **First** : install the code into your computer -you can use git clone-
- **Second** : Open DS-game.exe
- **Third** : Don't forget to enjoy :)

## Static configurations

**Note** : we have 2 static configurations you can change before starting the program

- `enhancment_Algorithm` : This is the enhancment we made in the code to make the computer finds your position faster instead of using the `linear search` we start searching from your last position so the complexity of the search changed from O(n) to O(1).
  If tou removed or commented the definition of this algorithm in the code you will deactivate the algorithm
- `enhancment_DS` : This is the enhancment we made in the code to make the hash table smaller (We made the `BUCKET` 17 instead of 51), so the computer can finds you faster but there would be collision in some places and of course we managed to handle it.
  If tou removed or commented the definition of this enhancment in the code you will deactivate the Ds enhancment and your `BUCKET` would be 51 instead of 17

  **Note** : You can find the time measurments in time branch
