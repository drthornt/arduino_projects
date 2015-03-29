#include <Wire.h>
#define address 0x57

int val = 100;
int letter = 0x41;

byte data;
void setup()
{ 
 Wire.begin();
 Serial.begin(9600);
 delay(1000); 

}

void loop()
{

  
 letter++;
 
 //WRITE!!!!*******************************
 Wire.beginTransmission(address);
 Wire.write(0x00);      //First Word Address
 Wire.write(0x00);      //Second Word Address

 Wire.write(letter);      //Write an 'A'

 delay(10);

 Wire.endTransmission();
 delay(10);

 //READ!!!!*********************************
 Wire.beginTransmission(address);
 Wire.write(0x00);      //First Word Address
 Wire.write(0x00);      //Second Word Address
 Wire.endTransmission();
 delay(10);

 Wire.requestFrom(address, 1);
 delay(10);
 data = Wire.read();
 Serial.write(data);      //Read the data and print to Serial port
 Serial.println();
 delay(10);

}
