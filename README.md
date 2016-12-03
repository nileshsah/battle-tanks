# Battle Tanks

BATTLE TANKS is an aerial view third person shooter game. An option to customize the Tank has been provided.  Next, the Tank is put into a unique randomized 2 - dimensional topology wherein it has to shoot at the enemy Tanks and doge their shots to score points and stay in the game. 
 
The ARROW KEYS are used to navigate the 2-D map and SPACE to shoot. However, the Tank has limited ammunition and the chamber has to be reloaded after every four shots (‘R’ for Reload). 
A HEALTH bar (green) and an AMMO bar (yellow) at the bottom left of the screen show the instantaneous health and ammunition status of the Tank.

The randomized topology consists of three elements – Walls, Water and Grass. Tanks can tread on empty space and on Grass.  Walls can be broken with a single shot but a Tank can never tread on Water.
An ingenious SCORE Algorithm has been devised which incorporates the shooting ‘accuracy’ into the final score i.e. lesser the number of bullets used to kill each computer controlled ‘bot’ – higher the score. 
The game ends when the health of the player becomes ‘zero’ i.e. the player has taken 5 shots by the enemy tanks.

The motive of the game is to score maximum points in the minimum time and consequently feature in the top ten high score list.

# Dependency

Borland C++ Compiler (Turbo C) will be needed. Easily obtained for MacOSX or Windows. Once set up, run this file in the compiler after including the Graphics library (Options -> Linker -> Libraries). Also make sure that the initgraph function in the CPP file points to the right BGI directory.
