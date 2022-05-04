#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN1       3
#define PIN2       5
#define PIN3       6

#define NUMPIXELS  16

Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100

char receivedChar;
boolean newData=false;

int water;
int food;
int social;

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  Serial.begin(9600);

  water=3;
  food=3;
  social=3;
  
}

void loop() 
{
  recvInfo();
  lights();
}

void recvInfo()
{
  if (Serial.available()>0)
  {
    receivedChar=Serial.read();
    Serial.println(receivedChar);
  }
}

void lights()
{
  //light switches
  
  if (water==1)
  {
    pixels1.clear();
    pixels1.show();
  }
  

  if (water==2)
  {
    pixels1.setPixelColor(4, pixels1.Color(0, 0, 20));
    pixels1.show();
  }
  
  if (water==3)
  {
    pixels1.clear();
    pixels1.setPixelColor(0, pixels1.Color(0, 0, 1));
    pixels1.setPixelColor(2, pixels1.Color(0, 0, 1));
    pixels1.setPixelColor(4, pixels1.Color(0, 0, 1));
    pixels1.setPixelColor(6, pixels1.Color(0, 0, 1));
    pixels1.show();
    delay(DELAYVAL);
    pixels1.clear();
    pixels1.setPixelColor(1, pixels1.Color(0, 0, 1));
    pixels1.setPixelColor(3, pixels1.Color(0, 0, 1));
    pixels1.setPixelColor(5, pixels1.Color(0, 0, 5));
    pixels1.setPixelColor(7, pixels1.Color(0, 0, 1));
    pixels1.show();
    delay(DELAYVAL);
  }

  if (food==1)
  {
    pixels2.clear();
    pixels2.show();
  }
  

  if (food==2)
  {
    pixels2.setPixelColor(4, pixels2.Color(0, 0, 20));
    pixels2.show();
  }
  
  if (food==3)
  {
    pixels2.clear();
    pixels2.setPixelColor(0, pixels2.Color(0, 0, 1));
    pixels2.setPixelColor(2, pixels2.Color(0, 0, 1));
    pixels2.setPixelColor(4, pixels2.Color(0, 0, 1));
    pixels2.setPixelColor(6, pixels2.Color(0, 0, 1));
    pixels2.show();
    delay(DELAYVAL);
    pixels2.clear();
    pixels2.setPixelColor(1, pixels2.Color(0, 0, 1));
    pixels2.setPixelColor(3, pixels2.Color(0, 0, 1));
    pixels2.setPixelColor(5, pixels2.Color(0, 0, 5));
    pixels2.setPixelColor(7, pixels2.Color(0, 0, 1));
    pixels2.show();
    delay(DELAYVAL);
  }


    if (social==1)
  {
    pixels3.clear();
    pixels3.show();
  }
  
  if (social==2)
  {
    pixels3.setPixelColor(4, pixels3.Color(0, 0, 20));
    pixels3.show();
  }
  
  if (social==3)
  {
    pixels3.clear();
    pixels3.setPixelColor(0, pixels3.Color(0, 0, 1));
    pixels3.setPixelColor(2, pixels3.Color(0, 0, 1));
    pixels3.setPixelColor(4, pixels3.Color(0, 0, 1));
    pixels3.setPixelColor(6, pixels3.Color(0, 0, 1));
    pixels3.show();
    delay(DELAYVAL);
    pixels3.clear();
    pixels3.setPixelColor(1, pixels3.Color(0, 0, 1));
    pixels3.setPixelColor(3, pixels3.Color(0, 0, 1));
    pixels3.setPixelColor(5, pixels3.Color(0, 0, 5));
    pixels3.setPixelColor(7, pixels3.Color(0, 0, 1));
    pixels3.show();
    delay(DELAYVAL);
  }
  
//serial comms in
  if (receivedChar=='a')
  {
    water=2;
    food=1;
    social=2;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='b')
  {
    water=2;
    food=2;
    social=2;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='c')
  {
    water=2;
    food=3;
    social=2;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='d')
  {
    water=2;
    food=1;
    social=3;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='e')
  {
    water=3;
    food=1;
    social=2;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='f')
  {
    water=1;
    food=2;
    social=3;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }

  if (receivedChar=='g')
  {
    water=3;
    food=2;
    social=1;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }

  if (receivedChar=='h')
  {
    water=1;
    food=3;
    social=2;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }

  if (receivedChar=='i')
  {
    water=2;
    food=3;
    social=1;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
}
