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

int OC = 8;
int SH = 9;
int EOC = 10;
int START = 11;

const int samples = 1; 
float resolution = 0.01960784313; // 5/255

int valuesDEC[samples];
//----------------------------------------------------
void setup()
{
  start();
  DDRD = 0xFF;

  pinMode(OC, INPUT);  // Output Control - OC
  pinMode(SH, OUTPUT); // Sample and Hold - SH
  pinMode(EOC, OUTPUT); // End Of Conversion - EOC
  pinMode(START, OUTPUT); // Start of conversion

}
//----------------------------------------------------

/*void conv(void){

  for(int strikes = 0; strikes < samples; strikes++){ //POR ENQUANTO NAO IMPLEMENTEI ISSO
    
    int valueCompare = 0b10000000;

    for(int bitLocation = 6; bitLocation >= 0; bitLocation --){

      writeValue(valueCompare);

      unsigned int outControl = readOC() & 0x01; 
    
      if(outControl){valueCompare |= 1 << bitLocation;}
      else{
        valueCompare &= ~(1 << bitLocation+1);
        valueCompare |= 1 << (bitLocation);
      }
    }
    valuesDEC[strikes] = valueCompare;
  }
}*/
//----------------------------------------------------

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
    delay(500);

}

void loop()
{
  startConv();
  
  sampleHold();
  unsigned int value = converter();
  endConv();

  Serial.begin(19200);
  while (!Serial) {;}

  Serial.print(String(value));

  Serial.print("\n");
  Serial.end(); 
  delay(5000);
  //printVal();

}
