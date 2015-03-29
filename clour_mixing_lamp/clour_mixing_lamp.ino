const int greenLEDPin = 9;
const int  blueLEDPin = 10;
const int   redLEDPin = 11;

const int  greenSensorPin = A0;
const int   blueSensorPin = A1;
const int    redSensorPin = A2;

int greenValue = 0;
int  blueValue = 0;
int   redValue = 0;

int greenSensorValue = 0;
int  blueSensorValue = 150;
int   redSensorValue = 250;

void setup(){


  Serial.begin(9600);

  pinMode(greenLEDPin,OUTPUT);
  pinMode(blueLEDPin ,OUTPUT);
  pinMode(redLEDPin  ,OUTPUT);

  
}

void loop() {
  //greenSensorValue = analogRead(greenSensorPin);
  //delay(5);
  //blueSensorValue  = analogRead(blueSensorPin);
  //delay(5);
  //redSensorValue   = analogRead(redSensorPin);
  //delay(5);

  if ( greenSensorValue > 254 ) {
    greenSensorValue = 0 ;
  } else {
    greenSensorValue = greenSensorValue + 10;
  }

  if ( blueSensorValue > 254 ) {
    blueSensorValue = 0;
  } else {
    blueSensorValue  = blueSensorValue + 10;
  };
  
  if ( redSensorValue > 254 ) {
    redSensorValue = 0;
  } else {
    redSensorValue   = redSensorValue + 10;
  }
  
  Serial.print("Green:");
  Serial.print(greenSensorValue);
  Serial.print("Blue:");
  Serial.print(blueSensorValue);
  Serial.print("Red:");
  Serial.print(redSensorValue);
  Serial.print("\n");
  
  //greenValue = greenSensorValue/4;
  //blueValue  = blueSensorValue/4;
  //redValue   = redSensorValue/4;
  
  analogWrite(greenLEDPin, greenSensorValue);
  analogWrite(blueLEDPin,  blueSensorValue);
  analogWrite(redLEDPin,   redSensorValue);
  
  delay (50);
}



