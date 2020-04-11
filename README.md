Mason Leidal 200310442

# topic
The topic I picked was sockets, mostly because I wanted to make a game the could be played over the internet. I went through a couple
Ideas of what would be the most interesting/feasable idea, I started with chess, but I don't exactly know the rules to chess, then went
to checkers, Then I went to UNO after briefly considering how I would implement a card game.

# challenges
The first challenge was to manage 4 players in a socket environment, with the lab's original setup it would have been a lot more difficult to balance who was playing and what should be sent where, thankfully Nova told me about FD_SET, because it would have been nuts trying to manage everything, the challenge then was to translate code for a FD_SET in a windows program to LINUX which isn't so complecated, but there were enough differences to confuse me a tad at the beginning. For the most part the rest of my problems came from junk data getting written to the socket, I honestly forget how I solved this because I've been working for six days straight here, but in short I was trying to use a secondary buffer to store the status of each player's hand, mostly there was a problem converting an integer to a character or a string because that's a C++ 11 thing and g++ uses c++98 and I was REALLY holding off using sstream because I wanted the program to be as C as possible, but eventually I caved. 



# 330Uno

This is a pretty basic UNO game that will connect to 4 people clients via a socket. This is an edit of lab 7 in the CS330 lab, using a 
FD_SET setup rather than using forks. 

# house rules

Because I didn't really want to overcomplicate the program, The game runs on basically the basic house rules for UNO, you can't stack +2
cards and the 7-0 rule is not in place. There is one house rule that I'm just going to call a house rule because It's a bug that's so
minor that I don't really care about fixing it, if you have 2 of the same card the game will play both cards at once, I've played UNO with
a house rule like this so I'm just calling it a house rule and being done with it (it's not a bug it's a feature!!!) Another house rule
that is that you can only uno AFTER playing your second to last card, I'm just going to be frank, the UNO system was the last thing I
tested, everything else ran like a charm, I kinda forgot that you could call UNO before playing the card so that's just how it works

# Starting the game

When starting the server there is going to be a bit of lag between when the process starts and when the socket is opened, this is to
randomize the cards given to each player. the process starts pretty much exactly like it did in the lab, it gives the port number and the
client enters the name and port number in their client process. once all four clients have entered player one presses enter and the game
starts

#turn flow

At the start of each turn the server will state how many cards each player has, what the top card on the pile is and if the player is able
to make a move. If the player's turn is skipped or if the player has to draw cards the game will say so and any input will just draw
those cards. If the player is able to make a move the cards will be listed by the initial of the color then the number. for example a
hand with red 2, green 5 and a green draw 2 card will be listed as R2 G5 G+ to the player. for reference skip cards, reverse order (or
as i had called them turn cards) and draw 2 cards are listed as XS, XT, and X+ respectively with X being a stand in for the color in this
example(note that when playing a card the letters MUST BE CAPITALS). draw 4s and wildcards are listed as D4 and WC. Once you have one card in your hand you can call uno. if you are too slow in
calling uno or you forget, the other players can challenge you at which point you will have to draw 2 cards

# note about drawing cards

because srand() is slow at picking a number, there is usually a slight bit of lag when drawing cards, this doesn't really show up
when drawing one card, but 2 or 4 will cause a lag of about a second or two

# minor turn start bug

Occasionally there will be a bug where the player is currently set to play won't get the messages that are typically sent after the
last player has finished a turn. to fix this just press enter once and the messages should pop up. I'm not sure why this happens, but
it's not something that really ruins the game.

# winning the game

once a player has played the last card in their hand that player has won and the game is over. a message will be sent to all players and
then the server will close.


# the program itself

Managing the turn order is pretty much as simple as incrementing  numbers for 4-7 representing the sockets in the file descriptor table. setting up the FD_SET really isn't as complicated as I though it was when I first started, like I going over the code the Nova and the video Nova sent me like 4 times, but really the process is mostly the same, you just don't need to be using forks. It actually provides an advantage because I can pretty easily lock out any interaction with the main game by checking if the FD_SET for file descriptor 7 exists. the main game first outputs the status of each player then the status of the player's hand depending on various bool states that would be set on the previous player's turn. While the entire turn runs the game checks if any player has entered a C or a U standing for Challenge and Uno respectively. For playing a card, if non of the bool variables are true, the program checks the first two letters of in the buffer, If the first character is a color, it first checks if it is a number, if it's not a number it moves on to special cases like a +2, reverse(turn in my case) or skip card, the process is similar across the board, the card's array index is set to 1 for being in the hand of the current play and for being drawn (taken), an extra check is set in the case that the player is in uno range, or if they player has won. In the case of special cards the bool value of that card is set to true to be used in intializing the next player's move. There are two more special cases, WC for wild card and D4 for Draw 4; in those cases there is an extra input required by the player to select the color, there is a bit of an oversight in that the input overwrites the first character but not the second so if player 1 played B9 and player 2 played D4 and selected R the card at the top of the pile would be R9, but let's just call that a house rule (We don't make mistakes, we make happy accidents). If nothing is input or if there is no available card to play then the player draws, in which case, again, we make sure to put a 1 in the hand and taken array's for the card's index. One thing I forgot to mention. Whenever a card is drawn it checks that there is at least one card still in the draw pile, that is that there is a 0 in the taken array. if there is not and every entry is a 1 then the taken array is reset and there are 1's placed in the index of cards that are in player's hands. This comparison is done every time a card is drawn. Once a player's turn has ended the turn count is incremented (decremented if a reverse(turn) card has been played) and wraps back around if the turn is > 7 or < 4.

