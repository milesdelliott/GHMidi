 
#include <Control_Surface.h> // Include the Control Surface library
 
// Select the serial port to use.
auto &serial = Serial;
// Instantiate a Serial MIDI interface at the default MIDI baud rate.
SerialMIDI_Interface<decltype(serial)> midi = {serial, MIDI_BAUD};
// Instantiate a CCButton object

CCButton button { 5, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},};

CCButton buttons[10] {
  { 23, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  { 22, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  { 21, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  { 20, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  { 19, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  { 18, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  { 17, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  { 15, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  { 14, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  { 13, {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},},
  
}
 
void setup() {
  Control_Surface.begin(); // Initialize Control Surface
}
 
void loop() {
  Control_Surface.loop(); // Update the Control Surface
}
