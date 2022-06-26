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
  int channel_ = channel;
//  if(channel_==1){
//      count++;
//    if(count==1){
//      int pitch_ = pitch;
//    note.on(pitch_);
//    p_shifter.on(pitch_);
//      }
//    if(count==2){
//      count=0;
//      }
//    }
    note.on(pitch_);
    p_shifter.on(pitch_);
}

void NoteOff_from_Master(byte channel, byte pitch, byte velocity){
//  int pitch_ = pitch;
//  note.off(pitch_);
//  p_shifter.off(pitch_);
}

void setup(){
  
  MIDI.setHandleNoteOn(NoteOn_from_Master);
  MIDI.setHandleNoteOff(NoteOff_from_Master);
  MIDI.begin(MIDI_CHANNEL_OMNI);
//  MIDI.begin(Master_Slave_ch);
  
  note.setup();
  p_shifter.setup();
  tank.setup();
//  pinMode(13,OUTPUT);//Lチカデバック用
}

void loop(){
  // リアルタイム性の確保のため、MIDI.readをできるだけ早く呼ぶように
  MIDI.read();
  note.update();
  p_shifter.update();
  tank.update();
  
}
