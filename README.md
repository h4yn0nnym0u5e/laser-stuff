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
Create and test a specific object that takes X and Y conrdinates on two inputs, and a rotation angle on the third, and emits rotated X and Y outputs. Rotation input maps -1.0 .. 1.0 to -180° .. +180°. `AudioEffectRotator::reverse(bool)` sets the rotation direction - if true, then -1.0 maps to +180°, and _vice versa_. There is also a new `AudioMixerSummer` object which is similar to the existing `AudioMixer4`, but allows over / underflow on the summed inputs, and does not provide a `gain()` function. 

As initially written, the `AudioEffectRotator` consumes about 0.3% of a Teensy 4.1's CPU time.
