# UNO_Game_Mini_Project
This repository contains the code for uno game in C++.This game can be played in terminal.

## Game Rules

* A dealer shuffles and distributes each player 7 cards. 
* The top card from the DRAW pile is turned over to begin a DISCARD pile. 
* The person to the left of the dealer starts to play. The next player must match a card from his HAND to the card on top of the DISCARD pile either by the number or by the color.
* If the player doesn't have a card that matches the one on the DISCARD pile then the player must take a card from the DRAW pile. If the DRAW pile is depleted then the DISCARD pile is reshuffled and play continues.
* The first player to play all the cards in their HAND wins the game. A player must tell “UNO” to indicate that they have only one card left in HAND. If they don’t tell “UNO” and the other player catches before the next player begins their turn, the player must draw two cards.

#### A total of 4 classes/objects are used, they are:
### Card

Member Variables: 

Color,
Number,
Is Plus 4,
Is plus 2,
Is Reverse,
Is Skip,
Is Wild,
Is PowerCard,

Methods:

Setters: 
Functions which sets card color,number,power.

Getters: 
Functions which provide data about a card.

### Player

Member Variables: 

`Set Of Cards`
To store all card sthat are there with him.

`Id`
To call him by a  unique name.

Methods:

`Put card`
To Select a card and put it.

`Take Card`
To take and keep the card in his cards set.

`Uno`
Function to decide whether he is going to say UNO.

`Challenge`
Function to decide whether he is going to challenge on a wild draw four  card.	

### Card Deck

Member Variables:

`Discard Pile`
To store all cards that are discarded.

`Draw Pile`
To store all the cards that are yet to be given to a player.

Methods:

`Get top card of draw pile`
To get the top card stored in draw Pile.

`Get top card of discard pile`
To get top card of discard pile.

`Put  card in a  pile`
Function to put a card in a pile.

`Shuffle`
Which shuffles all cards present in the deck(discard and draw pile).

### Simulator

Member Variables:

`Players`
To store all Players.

`Card Deck`
To store all the cards.

Methods:

`Simulate manually`
To simulate the game manually by taking inputs from user.

`Simulate automatically`
To simulate the game by taking random choices.

## `How to run this game`

### `make`
run the command make to makefile which generates executables.

### `./project`
the make command generates project executable run ./project to execute the code.
