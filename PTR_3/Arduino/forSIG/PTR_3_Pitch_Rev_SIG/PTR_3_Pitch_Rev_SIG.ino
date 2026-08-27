#include <MIDI.h>
#include "note.h"
#include "pitchshifter.h"
#include "tank.h"

MIDI_CREATE_DEFAULT_INSTANCE();

#define IF_Master_ch 0
#define Master_Slave_ch 4
Note note;
P_shifter p_shifter;
Tank tank;
int count=0;

void NoteOn_from_Master(byte channel, byte pitch, byte velocity){
  int _pitch = pitch;
  int _velocity = map(velocity, 0, 127, 20, 147);
  // if(63<_pitch<84){
  //   p_shifter.on(_pitch);
  // }

  switch(pitch){

    case 64 ... 84:
//      ms[4] = analogRead(A4);
      p_shifter.on(_pitch,_velocity);
    break;
  }
  // note.on(_pitch);
}

void NoteOff_from_Master(byte channel, byte pitch, byte velocity){
//  int _pitch = pitch;
//  note.off(_pitch);
//  p_shifter.off(_pitch);
}

void setup(){
  
  MIDI.setHandleNoteOn(NoteOn_from_Master);
  MIDI.setHandleNoteOff(NoteOff_from_Master);
  MIDI.begin(MIDI_CHANNEL_OMNI);
//  MIDI.begin(Master_Slave_ch);
  
  // note.setup();
  p_shifter.setup();
  // tank.setup();
//  pinMode(13,OUTPUT);//Lチカデバック用
}

void loop(){
  // リアルタイム性の確保のため、MIDI.readをできるだけ早く呼ぶように
  MIDI.read();
  // note.update();
  p_shifter.update();
  // tank.update();
  
}
