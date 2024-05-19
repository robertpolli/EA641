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
}
//----------------------------------------------------

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
  delay(500);

}
