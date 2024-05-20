//-------------------------
// C Code for Blinking LED
//-------------------------
extern "C"
{
  void start();
  void writeValue(int val);
  unsigned int readOC();
  void sampleHold();
  unsigned int converter();
  void startConv();
  void endConv();
}

//  PIN 8 - OC
//  PIN 9 - SH
//  PIN 10 - EOC
//  PIN 11 - START

const int samples = 1; 
float resolution = 0.01960784313; // 5/255

int valuesDEC[samples];
float valuesVOLTS[samples];
//----------------------------------------------------
void setup()
{
  start();
  DDRD = 0xFF;
}
//----------------------------------------------------

void loop()
{
  startConv();

  for(int strikes = 0; strikes < samples; strikes++){
    sampleHold();
  
    unsigned int value = converter();
    
    valuesDEC[strikes] = value;
    valuesVOLTS[strikes] = value * resolution;
  }
  endConv();

  Serial.begin(19200);
  while (!Serial) {;}

  for(int i=0; i < samples; i++){
      Serial.print(String(valuesDEC[i]) + ";");
      //Serial.println(String(valuesVOLTS[i]) + ";");  
  }
  
  Serial.print("\n");
  Serial.end(); 
  delay(500);

}
