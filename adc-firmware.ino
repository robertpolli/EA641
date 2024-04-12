void setup() {

  int OC = 1;
  int SH = 2;
  int EOC = 3;
  int START = 4; 

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
  digitalWrite(START, HIGH); //Start of conversion
  digitalWrite(EOC, LOW);

  int bitLocation = 6;
  int valueTry = 0b10000000;

  while(bitLocation >= 0){

    writeValue(valueTry);
    
    if(digitalRead(OC)){valueTry |= 1 << bitLocation;}
    else{
      valueTry &= ~(1 << bitLocation+1);
      valueTry |= 1 << (bitLocation);
    }
    bitLocation -= 1; 
  }
  
  digitalWrite(EOC, HIGH);  //End of conversion
  digitalWrite(START, LOW);
  delayMicroseconds(100); 
}
