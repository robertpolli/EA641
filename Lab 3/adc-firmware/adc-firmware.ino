
int OC = 8;
int SH = 9;
int EOC = 10;
int START = 11;

int samples = 100; 
float resolution = 5/255;
  
void setup() { 

  pinMode(OC, INPUT);  // Output Control - OC

  pinMode(SH, OUTPUT); // Sample and Hold - SH
  pinMode(EOC, OUTPUT); // End Of Conversion - EOC
  pinMode(START, OUTPUT); // Start of conversion

  DDRD = 0xFF;       // Config PORT D as output

}

void writeValue(int value){

  PORTD = value; // Writes value on PORT D
  
}


void loop() {

  char valuesDEC[samples];
  char valuesVOLTS[samples];

  digitalWrite(SH, HIGH);    //Sample
  delayMicroseconds(10);
  digitalWrite(SH, LOW);     //Hold
  
  digitalWrite(START, HIGH); //Start of conversion
  digitalWrite(EOC, LOW);

  for(int strikes = 0; strikes < samples; strikes++){

    int bitLocation = 6;
    int valueCompare = 0b10000000;

    while(bitLocation >= 0){

      writeValue(valueCompare);
    
      if(digitalRead(OC)){valueCompare |= 1 << bitLocation;}
      else{
        valueCompare &= ~(1 << bitLocation+1);
        valueCompare |= 1 << (bitLocation);
      }
      bitLocation -= 1; 
    }
    valuesDEC[strikes] = valueCompare;
    valuesVOLTS[strikes] = valueCompare * resolution;
  }
    
  digitalWrite(EOC, HIGH);  //End of conversion
  digitalWrite(START, LOW);


  if(samples == 100){

    Serial.begin(9600);
    while (!Serial) {;}    
    
    Serial.println(valuesDEC);
    Serial.println(valuesVOLTS);
    Serial.end();
    
    while (Serial) {;}
    DDRD = 0xFF;       // Config PORT D as output
    delay(500);
  }
}
