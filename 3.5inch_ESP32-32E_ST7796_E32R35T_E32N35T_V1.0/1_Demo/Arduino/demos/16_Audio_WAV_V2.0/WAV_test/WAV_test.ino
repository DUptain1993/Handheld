// Playing a digital WAV recording repeatadly using the XTronical DAC Audio library
// prints out to the serial monitor numbers counting up showing that the sound plays 
// independently of the main loop
// See www.xtronical.com for write ups on sound, the hardware required and how to make
// the wav files and include them in your code

#include "Audio_data.h"
#include "XT_DAC_Audio.h"

#define AUDIO_EN_PIN  4

XT_Wav_Class ForceWithYou(Force);     // create an object of type XT_Wav_Class that is used by 
                                      // the dac audio class (below), passing wav data as parameter.
                                      
XT_DAC_Audio_Class DacAudio(26,0);    // Create the main player class object. 
                                      // Use GPIO 26, one of the 2 DAC pins and timer 0

uint32_t DemoCounter=0;               // Just a counter to use in the serial monitor
                                      // not essential to playing the sound

void setup() {
  
  Serial.begin(115200);               // Not needed for sound, just to demo printing to the serial
                                      // Monitor whilst the sound plays, ensure your serial monitor
                                      // speed is set to this speed also.
  pinMode(AUDIO_EN_PIN, OUTPUT);
  digitalWrite(AUDIO_EN_PIN, LOW);
}


void loop() {
  DacAudio.FillBuffer();                // Fill the sound buffer with data
  if(ForceWithYou.Playing==false)       // if not playing,
    DacAudio.Play(&ForceWithYou);       // play it, this will cause it to repeat and repeat...
  Serial.println(DemoCounter++);        // Showing that the sound will play as well as your code running here.
}
