int OC = 8;
int SH = 9;
int EOC = 10;
int START = 11;

const int samples = 5; 
float resolution = 0.01960784313; // 5/255

int valuesDEC[samples];
float valuesVOLTS[samples];

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

void conv(void){

  for(int strikes = 0; strikes < samples; strikes++){

    int bitLocation = 6;
    int valueCompare = 0b10000000;

    while(bitLocation >= 0){

      writeValue(valueCompare);
      delay(5);
    
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
}

void printVal(void){

    Serial.begin(19200);
    while (!Serial) {;}    

    for(int i=0; i < samples; i++){
      Serial.print(String(valuesDEC[i]) + ";");
      //Serial.println(String(valuesVOLTS[i]) + ";");  
    }
    Serial.print("\n");
    Serial.end();
    
    DDRD = 0xFF;       // Config PORT D as output
    //delay(500);

}

void loop() {

  digitalWrite(SH, HIGH);    //Sample
  delayMicroseconds(100);
  digitalWrite(SH, LOW);     //Hold
  delayMicroseconds(100);
  
  digitalWrite(START, HIGH); //Start of conversion
  digitalWrite(EOC, LOW);

  conv();  
    
  digitalWrite(EOC, HIGH);  //End of conversion
  digitalWrite(START, LOW);

  printVal();
}
