#include <MIDI.h>
#include "note.h"

MIDI_CREATE_DEFAULT_INSTANCE();

#define IF_Master_ch 0
#define Master_Slave_ch 4
Note note[12];
int ms[5];


void NoteOn_from_Master(byte channel, byte pitch, byte velocity){
  int var = pitch % 12;
  int _velocity = int(velocity);
  int velo = map(_velocity,0,127,30,120);
  switch(var){
    case 0:
      note[0].on(0);
    break;
    case 1:
      note[1].on(1);
    break;
    case 2:
      note[2].on(2);
    break;
    case 3:
      note[3].on(3);
    break;
  }
}

void NoteOff_from_Master(byte channel, byte pitch, byte velocity){
  //ノートオフ時にすること
  int var = pitch % 12;
  switch(var){
    case 0:
      note[0].off(0);
    break;
    case 1:
      note[1].off(1);
    break;
    case 2:
      note[2].off(2);
    break;
    case 3:
      note[3].off(3);
    break;
  }
}

void setup(){
  
  MIDI.setHandleNoteOn(NoteOn_from_Master);
  MIDI.setHandleNoteOff(NoteOff_from_Master);
  MIDI.begin(MIDI_CHANNEL_OMNI);
//  MIDI.begin(Master_Slave_ch);

  for(int i=0;i<12;i++){
    note[i].setup();
  }
  pinMode(13,OUTPUT);
}

void loop(){
  // リアルタイム性の確保のため、MIDI.readをできるだけ早く呼ぶように
  MIDI.read();
//  for(int i=0;i<12;i++){
//    note[i].update();
//  }
}
