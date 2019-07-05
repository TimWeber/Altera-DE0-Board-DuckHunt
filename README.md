# Altera-DE0-Board
This was a project assigned to me in one of my modules while at university

## Aim
The aim of this project was to learn how to use the Quartus II IDE to program lights, button, and seven-segment displays on an Altra DE0 development board. This was done by creating a small "Duck Hunt" game. 

### This Project involved working with/using:
* Button states
* Switch states
* 7-segment displays
* Bit shifting

#### The Duck Hunt game operates as follows:
Ducks  are  represented  as  lit  LEDs  and  the  ducks  either  travel  from  left  to  right  or right to left. The pattern of the ducks is determined randomly when the game starts. Button  2  from  the  DE0  board  is  used  to  kill  the  ducks  (turn  the  lit  LEDs  off).  The game ends when all the ducks are killed (all LEDs are turned OFF). There are difficulty and speed settings and these are determined by the position of a series of switches. The difficulty settings change the number of missed shots allowed before losing the game, while the speed settings change how fast the speed of the ducks move. Both the number of shots used and the number of ducks hit are displayed on the seven-segment displays.

If the user kills ducks before running out of shots, WIN is displayed on the displays while if the user runs out of shots the word LOSE is displayed.

Button0 would be used to reset the game at any time.

### Below are some images of the game working
![GameStart](https://user-images.githubusercontent.com/43787505/60716394-2e380c00-9f17-11e9-823c-1e17004f42bd.png)
<br>This is the game at start. 5 ducks are alive, starting in a random location. 0 shots have been fired and 0 ducks hit. Note the 2 left most (switches 8 and 9) switches to control the speed and the two to the right of them (switches 6 and 7) control the difficulty.</br> 

![Showing2hits9shots](https://user-images.githubusercontent.com/43787505/60716528-8bcc5880-9f17-11e9-8e96-637f89dadf6c.png)
<br>This image it taken mid-game and shows 2 ducks hit and 9 shots fired.</br>

![showingLOSEfunction](https://user-images.githubusercontent.com/43787505/60716819-3c3a5c80-9f18-11e9-8896-15e0ed5479a3.png)
<br>This is demonstrating the end game function, in this example the shot limit has been reached and ducks are alive, therefore the player has lost.</br>
