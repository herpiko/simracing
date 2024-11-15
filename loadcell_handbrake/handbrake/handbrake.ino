#include <HX711.h>
#include <Joystick.h>
#define calibration_factor 10000 // Change this value to give accurate reading with your known mass.
#define DOUT  A0
#define CLK  A1
HX711 scale;


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_MULTI_AXIS, 4, 3,
  false, false, false, false, false, false,
  false, false, true, true, false);
 
 

int brake = 0;
int lastBrakeValue = 0;

void setup() {
  // Ranges are 1023 by default
   Joystick.setBrakeRange(0, 1023);
  
 
  Joystick.begin();
  Serial.begin(4800);
 
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();
}
void loop() {

//Displays reading in Serial Monitor

    //Serial.println (brake);
brake = scale.get_units(); // if the value is inverted put a - sign in front like -scale.get
 
   if (brake < 0 or brake < 1) {
    brake = 0;
  }
 
   if (lastBrakeValue != brake) {
     Joystick.setBrake(brake);
     lastBrakeValue = brake;
  }
}
