/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int led1 = 9;           // the pin that the LED is attached to
int led2 = 10;           // the pin that the LED is attached to
int led3 = 6;           // the pin that the LED is attached to
long  randNumber1 = 0;
long  randNumber2 = 0;
long  randNumber3 = 0;
int brightness1 = 0;    // how bright the LED is
int brightness2 = 0;    // how bright the LED is
int brightness3 = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
  
// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  randomSeed(analogRead(0));
  randNumber1 = random(255);
  randNumber2 = random(255);
  randNumber3 = random(255);

  brightness1 = (int) randNumber1;
  brightness2 = (int) randNumber2;
  brightness3 = (int) randNumber3;
} 

// the loop routine runs over and over again forever:
void loop()  { 
  // set the brightness of pin 9:

  analogWrite(led1, brightness1);
  analogWrite(led2, brightness2);
  analogWrite(led2, brightness3);

  // change the brightness for next time through the loop:
  //brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness1 == 0 || brightness1 == 255) {
    fadeAmount = -fadeAmount ; 
  }
  if (brightness2 == 0 || brightness2 == 255) {
    fadeAmount = -fadeAmount ; 
  }
  if (brightness3 == 0 || brightness3 == 255) {
    fadeAmount = -fadeAmount ; 
  }
  // wait for 30 milliseconds to see the dimming effect    
  delay(500);                          
}

