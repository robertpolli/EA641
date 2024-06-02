//-------------------------
// C Code for Blinking LED
//-------------------------
extern "C"
{
  void start();
  void writeValue(int val);
  unsigned int readOC();
  void sampleHold();
  void startConv();
  void endConv();
}

int OC = 8;
int SH = 9;
int EOC = 10;
int START = 11;

const int samples = 600; 
float resolution = 0.01960784313; // 5/255

int valuesDEC[samples];
float valuesVOLTS[samples];

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

int conv(void){
    
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
    return(valueCompare);
}
//----------------------------------------------------

void printVal(void){   

    for(int i=0; i < samples; i++){
      writeValue(valuesDEC[i]);
      delayMicroseconds(535);
    }
    
    DDRD = 0xFF;       // Config PORT D as output
}

void loop()
{
  
  startConv();

  for(int strikes = 0; strikes < samples; strikes++){
    sampleHold();
    int value = conv();
    
    valuesDEC[strikes] = value;
  }
  endConv();
  
  printVal();

  delay(500);
}
