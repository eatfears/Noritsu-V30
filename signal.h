#pragma once

#include "elements.h"
#include "pitches.h"

unsigned long previousMillis = 0;
boolean outputTone = false;                // Records current state

#define MELODY

/*
  #ifdef MELODY2
  int melody[] =
  {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
  };

  int noteDurations[] =
  {
  4, 8, 8, 4, 4, 4, 4, 2
  };
  #endif
*/

#ifdef MELODY
int melody[] =
{
  NOTE_E6, NOTE_E6, 0, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_E6, 0,
  NOTE_D6, NOTE_C6, 0, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_A5, 0,
};

int noteDurations[] =
{
  4, 4, 4, 8, 8, 4, 4, 2, 4, 4, 4, 8, 8, 4, 4, 2
};
#endif

template<size_t N>
size_t num_notes(int(&arr)[N])
{
  return N;
}

class Signal
{
  public:
    static void beep()
    {
      m_Start = millis();
      noteIndex = 0;
    }

    static void check()
    {
      unsigned long currentMillis = millis();

#ifndef MELODY
      if (currentMillis - m_Start < 200)
      {
        digitalWrite(BUZZ_OUT_PIN, HIGH);
      }
      else if (currentMillis - m_Start < 500)
      {
        digitalWrite(BUZZ_OUT_PIN, LOW);
      }
      else if (currentMillis - m_Start < 1000)
      {
        digitalWrite(BUZZ_OUT_PIN, HIGH);
      }
      else if (currentMillis - m_Start > 1000)
      {
        digitalWrite(BUZZ_OUT_PIN, LOW);
      }
#else
      if (noteIndex < num_notes(melody))
      {
        int noteDuration = 700 / noteDurations[noteIndex];

        if (outputTone)
        {
          if (currentMillis - previousMillis >= noteDuration)
          {
            previousMillis = currentMillis;
            noTone(BUZZ_OUT_PIN);
            outputTone = false;

            noteIndex++;
          }
        }
        else
        {
          if (currentMillis - previousMillis >= noteDuration * 0.2)
          {
            previousMillis = currentMillis;
            if (melody[noteIndex])
            {
              tone(BUZZ_OUT_PIN, 0.6*melody[noteIndex]);
            }
            outputTone = true;
          }
        }
      }
#endif
    }

  private:
    static unsigned long m_Start;
    static int noteIndex;
};

unsigned long Signal::m_Start = -1000;
int Signal::noteIndex = num_notes(melody);
