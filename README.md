# Arduino-RubikSolver

### Solving Method

To solve the cube I use the [CFOP method](https://jperm.net/3x3/cfop), it is one of the methods I know and does not require too much memory or processing power that the arduino could not handle.   

I created a 3x3x6 array to hold the colors of each sticker for all the 6 faces, when a face turns, it changes the colors (represented by integers values) for that face and the stickers surronding.  
Based on the colors at specific positions at a given moment, I can decide what algorithm to apply.

### Run

Grab to arduino folder, open it with Arduino IDE and plug it to the board

For the android App, download it to your smartphone and it will work, hopefully.

