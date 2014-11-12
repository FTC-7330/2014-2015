#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*   HiTechnic Experimenter's Kit for the SuperPro

Experiment - 7 Magnetic Switch Sensor

This program measures reads the status of the magnetic sensor and outputs the status.

*/

#include "..\include\hitechnic-superpro.h"

task main() {
  // The data to be written: 0x10 = 010000 binary,
  // makes B4 digital port an output.
  HTSPBsetupIO(HTSPB, 0x10);

  while(true) {
    if(HTSPBreadIO(HTSPB, 0x01) == 0) {
      eraseDisplay();
      displayTextLine(1, "Magnet present");
      HTSPBwriteIO(HTSPB, 0x10);
    } else {
      eraseDisplay();
      displayTextLine(1, "Magnet absent");
      HTSPBwriteIO(HTSPB, 0x00);
    }
    sleep(50);
  }
}
