/* Simple Teensy DIY USB-MIDI controller.
  Created by Liam Lacey, based on the Teensy USB-MIDI Buttons example code.

   Contains 8 push buttons for sending MIDI messages,
   and a toggle switch for setting whether the buttons
   send note messages or CC messages.

   The toggle switch is connected to              input pin 0,
   and the push buttons are connected to input pins 1 - 8.

   You must select MIDI from the "Tools > USB Type" menu for this code to compile.

   To change the name of the USB-MIDI device, edit the STR_PRODUCT define
   in the /Applications/Arduino.app/Contents/Java/hardware/teensy/avr/cores/usb_midi/usb_private.h
   file. You may need to clear your computers cache of MIDI devices for the name change to be applied.

   See https://www.pjrc.com/teensy/td_midi.html for the Teensy MIDI library documentation.

*/
// include MIDI library
#include <MIDI.h>
#include <Bounce.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);
const int channel = 1;
//The number of push buttons
const int NUM_OF_BUTTONS = 9;

// the MIDI channel number to send messages
const int MIDI_CHAN = MIDI_CHANNEL_OMNI;

// Create Bounce objects for each button and switch. The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// 5 = 5 ms debounce time which is appropriate for good quality mechanical push buttons.
// If a button is too "sensitive" to rapid touch, you can increase this time.

//button debounce time
const int DEBOUNCE_TIME = 5;

Bounce buttons[NUM_OF_BUTTONS] =
{
  Bounce (12, DEBOUNCE_TIME),
  Bounce (11, DEBOUNCE_TIME),
  Bounce (10, DEBOUNCE_TIME),
  Bounce (9, DEBOUNCE_TIME),
  Bounce (8, DEBOUNCE_TIME),
  Bounce (14, DEBOUNCE_TIME),
  Bounce (15, DEBOUNCE_TIME),
  Bounce (16, DEBOUNCE_TIME),
  Bounce (17, DEBOUNCE_TIME),
};

const int MIDI_MODE_NOTES = 0;
const int MIDI_MODE_CCS = 1;

//Variable that stores the current MIDI mode of the device (what type of messages the push buttons send).
int midiMode = MIDI_MODE_NOTES;

//Arrays the store the exact note and CC messages each push button will send.
const int MIDI_NOTE_NUMS[NUM_OF_BUTTONS] = {60, 59, 55, 50, 45, 40, 39, 38, 37};
const int MIDI_NOTE_VELS[NUM_OF_BUTTONS] = {110, 110, 110, 110, 110, 110, 110, 110, 110};
const int MIDI_CC_NUMS[NUM_OF_BUTTONS] = {24, 25, 26, 27, 20, 21, 22, 23, 28};
const int MIDI_CC_VALS[NUM_OF_BUTTONS] = {127, 127, 127, 127, 127, 127, 127, 127, 127};
const int MIDI_CC_PINS[NUM_OF_BUTTONS] = {12, 11, 10, 9, 8, 14, 15, 16, 17};


//==============================================================================
//==============================================================================
//==============================================================================
//The setup function. Called once when the Teensy is turned on or restarted

void setup()
{
    Serial.begin(115200);
  MIDI1.begin(MIDI_CHAN);
  // Configure the pins for input mode with pullup resistors.
  // The buttons/switch connect from each pin to ground.  When
  // the button is pressed/on, the pin reads LOW because the button
  // shorts it to ground.  When released/off, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.   The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!
  pinMode (12, INPUT_PULLUP);
  pinMode (11, INPUT_PULLUP);
  pinMode (10, INPUT_PULLUP);
  pinMode (9, INPUT_PULLUP);
  pinMode (8, INPUT_PULLUP);
  pinMode (14, INPUT_PULLUP);
  pinMode (15, INPUT_PULLUP);
  pinMode (16, INPUT_PULLUP);
  pinMode (17, INPUT_PULLUP);
    // initialize the digital pin as an output.
  pinMode(13, OUTPUT);
  Serial.println("Begin");
}

//==============================================================================
//==============================================================================
//==============================================================================
//The loop function. Called over-and-over once the setup function has been called.

void loop()
{
  digitalWrite(13, HIGH);   // set the LED on
  //==============================================================================
  // Update all the buttons/switch. There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  for (int i = 0; i < NUM_OF_BUTTONS + 1; i++)
  {
    buttons[i].update();
  }

  //==============================================================================
  // Check the status of each push button

  for (int i = 0; i < NUM_OF_BUTTONS; i++)
  {
    //========================================
    // Check each button for "falling" edge.
    // Falling = high (not pressed - voltage from pullup resistor) to low (pressed - button connects pin to ground)

    if (buttons[i].fallingEdge())
    {
      //If in note mode send a MIDI note-on message.
      //Else send a CC message.
        
        noteOn (MIDI_NOTE_NUMS[i], MIDI_NOTE_VELS[i], MIDI_CHAN);
    }

    //========================================
    // Check each button for "rising" edge
    // Rising = low (pressed - button connects pin to ground) to high (not pressed - voltage from pullup resistor)

    else if (buttons[i].risingEdge())
    {
       Serial.println(i);
      //If in note mode send a MIDI note-off message.
      //Else send a CC message with a value of 0.
        
          noteOff (MIDI_NOTE_NUMS[i], MIDI_CHAN);
    }

  } //for (int i = 0; i < NUM_OF_BUTTONS; i++)

  //==============================================================================
  // Check the status of the toggle switch, and set the MIDI mode based on this.
  //==============================================================================
  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read())
  {
    // ignoring incoming messages, so don't do anything here.
  }
  
}

void noteOn( int noteNumber, int noteVelocity, int channel) {
  Serial.println("NOTE ON");
   Serial.println(noteNumber);
 MIDI1.sendNoteOn (noteNumber, noteVelocity, channel);
 usbMIDI.sendNoteOn (noteNumber, noteVelocity, channel);
}

void noteOff( int noteNumber, int channel) {
  Serial.println("NOTE OFF");
 MIDI1.sendNoteOff (noteNumber, 0, channel);
 usbMIDI.sendNoteOff (noteNumber, 0, channel);
}
