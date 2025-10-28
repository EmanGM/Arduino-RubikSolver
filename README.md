# Arduino-RubikSolver


## Run

For the android App, download it to your smartphone and it will work, hopefully.

Grab to arduino folder, open it with Arduino IDE and plug it to the board.  
Parent directory must be named "a_constants", do not change it.  
You need to install Adafruit PWM servo driver and can easly do that in Arduino IDE library manager.  


## Solving Method

To solve the cube I use the [CFOP method](https://jperm.net/3x3/cfop), it is one of the methods I know and does not require too much memory or processing power that the arduino could not handle.   

I created a 3x3x6 array to hold the colors of each sticker for all the 6 faces, when a face turns, it changes the colors (represented by integers values) for that face and the stickers surronding.  
Based on the colors at specific positions at a given moment, I can decide what algorithm to apply.




