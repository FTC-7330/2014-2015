#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*   HiTechnic Experimenter's Kit for the SuperPro

Experiment - 9 Speaker

This program  first plays a sequence of three ascending
notes using just O0 and then three pairs of descending
notes using both O0 and O1.

*/

// One octive of note frequencies
#define  TONE_C4   262
#define  TONE_CS4   277
#define  TONE_D4   294
#define  TONE_DS4   311
#define  TONE_E4   330
#define  TONE_F4   349
#define  TONE_FS4   370
#define  TONE_G4   392
#define  TONE_GS4   415
#define  TONE_A4   440
#define  TONE_AS4   466
#define  TONE_B4   494
#define  TONE_C5   523

#include "hitechnic-superpro.h"

task main() {
  HTSPBsetupIO(HTSPB, 0x10);

  HTSPBwriteAnalog(HTSPB, HTSPB_DACO0, DAC_MODE_SQUAREWAVE, TONE_C4, 1023);
  sleep(200);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO0, DAC_MODE_SQUAREWAVE, TONE_DS4, 1023);
  sleep(400);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO0, DAC_MODE_SQUAREWAVE, TONE_E4, 1023);
  sleep(200);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO0, DAC_MODE_SQUAREWAVE, 1, 0);
  sleep(200);

  HTSPBwriteAnalog(HTSPB, HTSPB_DACO0, DAC_MODE_SQUAREWAVE, TONE_F4, 1023);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO1, DAC_MODE_SQUAREWAVE, TONE_A4, 1023);
  sleep(200);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO0, DAC_MODE_SQUAREWAVE, TONE_E4, 1023);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO1, DAC_MODE_SQUAREWAVE, TONE_G4, 1023);
  sleep(200);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO0, DAC_MODE_SQUAREWAVE, TONE_C4, 1023);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO1, DAC_MODE_SQUAREWAVE, TONE_E4, 1023);
  sleep(400);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO0, DAC_MODE_SQUAREWAVE, 1, 0);
  HTSPBwriteAnalog(HTSPB, HTSPB_DACO1, DAC_MODE_SQUAREWAVE, 1, 0);

}
