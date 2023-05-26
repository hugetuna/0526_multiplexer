#include "pitches.h"
#include "shape.h"
// notes in the melody:
int star[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A5, NOTE_A5, NOTE_G4, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2, 4
};
int deepdeepblue[]={
NOTE_F4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D5, NOTE_C5, NOTE_D4, NOTE_C4
};
int noteDurationsD[] = {
  4, 4, 4, 8, 8, 8, 4, 4
};

 void showPattern(byte matrix[8][8]){
  for(byte i = 0;i < 8; i++){
    for(byte j = 0;j < 8; j++){
      digitalWrite(row[j], 1 - scan[i][j]);
      digitalWrite(col[j], 1 - matrix[i][j]);
    }
    for(byte j = 0;j < 8; j++){
      digitalWrite(row[j], HIGH);
      digitalWrite(col[j], LOW);
    }
  }
}
int songnum=0;
bool butbefore=1,butnow=1;
unsigned long int tb=0,tn=0;

void setup() {
  // iterate over the notes of the melody:
  pinMode(A5,INPUT_PULLUP);
  for(byte i = 0; i <= sizeof(row); i++){
    pinMode(row[i], OUTPUT);
  }
  for(byte i = 0; i <= sizeof(col); i++){
    pinMode(col[i], OUTPUT);
  }
  //attachInterrupt(digitalPinToInterrupt(A5), blinking, FALLING );
  Serial.begin(9600);
}

void loop()
{
  // no need to repeat the melody.
  if(songnum==0)
  {
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {
      // to calculate the note duration, take one second divided by the note type.
     //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(2, star[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      //delay(pauseBetweenNotes);
      while(tn-tb<pauseBetweenNotes)
      {
        tn=millis();
        showPattern(circle);
      }
      tb=tn;
      // stop the tone playing:
      noTone(2);
      //if(songnum != 0) break;
      butnow=digitalRead(A5);
      if(butnow==0&&butbefore==1)
      {
        songnum=songnum+1;
        thisNote=8;
      }
      butbefore==butnow;
  }
  }
  if(songnum==1)
  {
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {
      // to calculate the note duration, take one second divided by the note type.
     //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurationsD[thisNote];
      tone(2, deepdeepblue[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      //delay(pauseBetweenNotes);
      while(tn-tb<pauseBetweenNotes)
      {
        tn=millis();
        showPattern(heart);
      }
      tb=tn;
      // stop the tone playing:
      noTone(2);
       butnow=digitalRead(A5);
      if(butnow==0&&butbefore==1)
      {
        songnum=songnum-1;
        thisNote=8;
      }
      butbefore==butnow;
  }
}
}
