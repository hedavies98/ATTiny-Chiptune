# ATTiny-Chiptune
A small chiptune player/toy based around the ATTiny microcontroller

This is a very basic melody player with controls for pitch, BPM, a filter, and volume. It also has a toggle switch that allows for the looping of the melody, parameters for BPM and pitch are read on microcontroller start up so a reset switch is necessary to change these without power cycling. 

Below are the lines of code to edit to change the parameters of the player:

`const int steps = 16;` - Change this line to adjust how many steps (notes) are in the melody

`const int bpms[4] = {750, 500, 428, 250};` - Change this line to adjust the BPM options, BPM here is expressed in ms of one note


To adjust the melody you want to edit this array:

`const int tune_notes[steps] = {CN, RS, CS, RS, CN, RS, FS, CS, FN, EN, FS, EN, DS, DN, DN, CN};`

The syntax should be self explanatory, it's the note letter followed by the accidental. For example, C would be CN (C Natural) and F# would be FS, F Sharp. RS is a special symbol representing a rest
