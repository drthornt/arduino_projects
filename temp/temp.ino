const int sensorPin = A0;
const int sensorPin2 = A1;
const float baselineTemp = 20.0;

void setup(){
  Serial.begin(9600);
  for(int pinNumber = 3; pinNumber<6 ; pinNumber++){
    pinMode(pinNumber,OUTPUT);
    digitalWrite(pinNumber,LOW);
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  int sensorVal2 = analogRead(sensorPin2);
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  Serial.print(" ");
  Serial.print(sensorVal2);
  
  float voltage  = (sensorVal/1024.0) * 5.0 ;

  Serial.print(", Volts: ");
  Serial.print(voltage);
  
  Serial.print(", degrees C: ");
  float temperature = ( voltage - 0.5 ) * 100;
  // supply voltage * ( 1000 / 1024)  / 10 = 0.48...
  float temperature2 = sensorVal2 * 0.48828125 ;
  Serial.print(temperature);
  Serial.print(" ");
  Serial.print(temperature2);
  Serial.print("\n");
  if(temperature < baselineTemp ){
   digitalWrite(3,LOW); 
   digitalWrite(4,LOW);
   digitalWrite(5,LOW);
  } else if ( temperature >= baselineTemp+2 &&
     temperature < baselineTemp+4){
   digitalWrite(3,HIGH); 
   digitalWrite(4,HIGH);
   digitalWrite(5,LOW);
  } else if ( temperature >= baselineTemp+4 &&
     temperature < baselineTemp+6){
   digitalWrite(3,HIGH); 
   digitalWrite(4,HIGH);
   digitalWrite(5,HIGH);
  }
  delay(1000);
}
