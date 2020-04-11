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
example. draw 4s and wildcards are listed as D4 and WC. Once you have one card in your hand you can call uno. if you are too slow in
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
