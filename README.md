# ENGG1340-2122S2-Project


## Group members:
Ethan and Ray


## Brief description of our game

The project would be based on a game called 'Wordle', which allows players to guess a word each time, and see if you can guess the word correctly with limited chances.

To correctly guess the word, there would be hints on whether the characters your word are on the right position, wrong position, or don't exist at all. Players would then have to guess the word based on the results obtained from the last word.

Unlike Wordle, the program would not check if the word is a valid word, since the wordlist is too large for checking. Therefore the user is allowed to type any character to guess the correct word.


## Features planned to be added from the original game

### 1. Variable word length
Variable word length (from 4 to 8) would be available for player.

### 2. Immediate start of the game
The game would allow the player to start a new round after finishing a game, which different from the original wordle that requires the user to wait for a day.

### 3. Quitting and saving of current game status
Players can quit the game during gameplay, and save the current game status to a file called 'round.save'. Players can continue their progress at anytime with their historical progress by saving his records to 'player.save'

### 4. Loading and exporting player statistics
Player's progress can be exported into a file called 'player.save', which the save file would include:
* Total time played
* Current win streaks
* Historical highest win streaks
* A list of the times for user to successfully guessed the word for each length of word

The current game's progress can be exported into a file called 'round.save', which saves the current game data, including:
* The choice of word in that round
* Words input by user at each trial

## How each coding element supports features we plan to implement

### 1. Generation of random game sets or events:
  * In every individual game, players will need to choose their desired word length before actual gameplay. Then, a random word will be chosen for each trial. If players want to play a 5-word game, a random 5 letter word will be chosen and the user has to guess so.

### 2. Data structures for storing game status:
  In the program, there would be 2 struct for storing game status, namely Player and Game.
  
  In the Player struct, record of previous game and data are stored as follows:
  * isPlaying, in the form of boolean.
  * streak, in the form of int.
  * highestWinStreak, in the form of int.
  * record, in the form of an array of vectors


  In the Game struct, game information will be saved as follows:
  * target, in the form of string.
  * trials, in the form of vector. 

### 3. Dynamic memory management:
  * In the game, the length of words that to be guessed is decided by players. Dynamic memory management will be used to allocate the array storing the word with the length that the player has chosen, as the information can be used to create a character array with variable length instead of having a character array with maximum length possible for user to input.

### 4. File input/output (e.g., for loading/saving game status):
  * As mentioned, we will save players' current game status into 'round.data', and brief record of players' game history into 'player.data'. We will allow players to continue their game at anytime, so their game process will be loaded when they choose to continue.

### 5. Program codes in multiple files:
  * The word lists we have chosen would be too annoying to fit in a single cpp file, instead the word lists and random word generator would be separated to different files for loading, with words of same length as its own file.

## Reference material

Link to the original Wordle: https://www.nytimes.com/games/wordle/index.html

## Compilation and execution instructions
First, run `make WORDLE_main` to compile the program, then run `./WORDLE_main` to start the game.
