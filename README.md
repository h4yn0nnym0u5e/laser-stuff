# laser-stuff
Examples and library code for using Teensy Audio library to drive XYRGB laser projectors

For now this is just a workspace with a bunch of work-in-progress stuff. Eventually it may become properly organised.

## tests
Folder for the following test sketches
### AudioTestShapes
Generate a static shape
### AudioTestRotation
Rotate the shape using standard audio library objects. There are some issues with reversing the direction of rotation, due to AudioSynthWaveform not having enough exposed functionality to allow the rotation angle to be preserved when changes are made to the waveform. It's also a complex design, and will get worse if we try to modulate the rotation rate.
### AudioTestRotatorObject
Create and test a specific object that takes X and Y coordinates on two inputs, and a rotation angle on the third, and emits rotated X and Y outputs. Rotation input maps -1.0 .. 1.0 to -180° .. +180°. `AudioEffectRotator::reverse(bool)` sets the rotation direction - if true, then -1.0 maps to +180°, and _vice versa_. There is also a new `AudioMixerSummer` object which is similar to the existing `AudioMixer4`, but allows over / underflow on the summed inputs, and does not provide a `gain()` function. 

As initially written, the `AudioEffectRotator` consumes about 0.3% of a Teensy 4.1's CPU time.

### ILDAfilePlayer
Plays back a .ILD file. Only outputs XY data on channels 7+8 of a CS42448 audio board, so it's not DC, there's no laser modulation, it assumes Format 0 records, etc etc. But it does work...

### ILDAfilePlayer3
Plays back a .ILD file using the AudioPlayILDA object. Outputs XYZRGBs data on channels 1-7 of a PCM3168 audio board.

### ILDAfilePlayer4
Plays back a .ILD file using the AudioPlayILDA object. Outputs XYZRGBs data on channels 1-7 of a PCM3168 audio board. Includes ability to 
send commands from the serial monitor to vary the playback rate and switch to playback of a named file from a RAM buffer.

### ILDAinfo
Use of utility methods to get information on ILDA files, and load to memory

### LaserTestStallProtection
### LaserTestStallProtectionV2
Demonstrate the use of the `AudioEffectProtectStall` object. V2 adds overall rotation, which actually defeats the protection because even when playback stops, the spot is still being rotated.

### LaserTestPalette
Demonstrate the use of the palette - at time of writing, still seeking an ILDA file with a built-in palette.

### LaserTestRAMplay
Test of buffering a whole ILDA file in RAM (EXTMEM in this case) and playing it from there.

### StructTester
Demo of using structs to package up repeated elements in the otherwise flat structure provided by the native Design Tool. In an ideal world one would use classes, but let's not get ahead of ourselves...

### StructTester02
Demonstrate more stuff, including use of a streamed or in-memory ILDA file to give a rotating triangular repeat. Needs `/ilda/triangle.ild` on the SD card.

## ilda
Some useful ILDA-format files

## python
Playing about with using spreadsheets and Python to create our own simple ILDA files
