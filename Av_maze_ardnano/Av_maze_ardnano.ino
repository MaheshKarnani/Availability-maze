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
unsigned long time_now1 = 0;
int flag_pix1=1;
unsigned long time_now2 = 0;
int flag_pix2=1;
unsigned long time_now3 = 0;
int flag_pix3=1;

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  Serial.begin(9600);

  water=2;
  food=2;
  social=2;
}

void loop() 
{
  recvInfo();
  lights1();
  lights2();
  lights3();
  lut();
}

void recvInfo()
{
  if (Serial.available()>0)
  {
    receivedChar=Serial.read();
    Serial.println(receivedChar);
  }
}

void lights1()
{
  //light1 switches
  
  if (water==0)
  {
    pixels1.clear();
    pixels1.show();
  }
  

  if (water==1)
  {
    pixels1.setPixelColor(4, pixels1.Color(0, 0, 5));
    pixels1.show();
  }
  
  if (water==2)
  { 
    if (flag_pix1==1)
    {
      if (millis() > time_now1 + DELAYVAL)
      {
        pixels1.clear();
        pixels1.setPixelColor(0, pixels1.Color(0, 0, 1));
        pixels1.setPixelColor(2, pixels1.Color(0, 0, 1));
        pixels1.setPixelColor(4, pixels1.Color(0, 0, 1));
        pixels1.setPixelColor(6, pixels1.Color(0, 0, 1));
        pixels1.show();
        time_now1 = millis();
        flag_pix1=2;
      }
    }    
    if (flag_pix1==2)
    {
      if (millis() > time_now1 + DELAYVAL)
      {
        pixels1.clear();
        pixels1.setPixelColor(1, pixels1.Color(0, 0, 1));
        pixels1.setPixelColor(3, pixels1.Color(0, 0, 1));
        pixels1.setPixelColor(5, pixels1.Color(0, 0, 1));
        pixels1.setPixelColor(7, pixels1.Color(0, 0, 1));
        pixels1.show();
        time_now1 = millis();
        flag_pix1=1;
      }
    }
  }
}
void lights2()
{
  //light2 switches
  
  if (food==0)
  {
    pixels2.clear();
    pixels2.show();
  }
  

  if (food==1)
  {
    pixels2.setPixelColor(4, pixels2.Color(0, 0, 5));
    pixels2.show();
  }
  
  if (food==2)
  { 
    if (flag_pix2==1)
    {
      if (millis() > time_now2 + DELAYVAL)
      {
        pixels2.clear();
        pixels2.setPixelColor(0, pixels2.Color(0, 0, 1));
        pixels2.setPixelColor(2, pixels2.Color(0, 0, 1));
        pixels2.setPixelColor(4, pixels2.Color(0, 0, 1));
        pixels2.setPixelColor(6, pixels2.Color(0, 0, 1));
        pixels2.show();
        time_now2 = millis();
        flag_pix2=2;
      }
    }    
    if (flag_pix2==2)
    {
      if (millis() > time_now2 + DELAYVAL)
      {
        pixels2.clear();
        pixels2.setPixelColor(1, pixels2.Color(0, 0, 1));
        pixels2.setPixelColor(3, pixels2.Color(0, 0, 1));
        pixels2.setPixelColor(5, pixels2.Color(0, 0, 1));
        pixels2.setPixelColor(7, pixels2.Color(0, 0, 1));
        pixels2.show();
        time_now2 = millis();
        flag_pix2=1;
      }
    }
  }
}

void lights3()
{
  //light3 switches
  
  if (social==0)
  {
    pixels3.clear();
    pixels3.show();
  }
  
  if (social==1)
  {
    pixels3.setPixelColor(4, pixels3.Color(0, 0, 5));
    pixels3.show();
  }
  
  if (social==2)
  { 
    if (flag_pix3==1)
    {
      if (millis() > time_now3 + DELAYVAL)
      {
        pixels3.clear();
        pixels3.setPixelColor(0, pixels3.Color(0, 0, 1));
        pixels3.setPixelColor(2, pixels3.Color(0, 0, 1));
        pixels3.setPixelColor(4, pixels3.Color(0, 0, 1));
        pixels3.setPixelColor(6, pixels3.Color(0, 0, 1));
        pixels3.show();
        time_now3 = millis();
        flag_pix3=2;
      }
    }    
    if (flag_pix3==2)
    {
      if (millis() > time_now3 + DELAYVAL)
      {
        pixels3.clear();
        pixels3.setPixelColor(1, pixels3.Color(0, 0, 1));
        pixels3.setPixelColor(3, pixels3.Color(0, 0, 1));
        pixels3.setPixelColor(5, pixels3.Color(0, 0, 1));
        pixels3.setPixelColor(7, pixels3.Color(0, 0, 1));
        pixels3.show();
        time_now3 = millis();
        flag_pix3=1;
      }
    }
  }
}

void lut()
{  
//serial comms in look up table
  if (receivedChar=='a')
  {
    water=1;
    food=1;
    social=1;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='b')
  {
    water=0;
    food=1;
    social=1;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='c')
  {
    water=2;
    food=1;
    social=1;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='d')
  {
    water=1;
    food=0;
    social=1;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='e')
  {
    water=1;
    food=2;
    social=1;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='f')
  {
    water=1;
    food=1;
    social=0;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }

  if (receivedChar=='g')
  {
    water=1;
    food=1;
    social=2;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }

  if (receivedChar=='h')
  {
    water=0;
    food=0;
    social=0;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }

  if (receivedChar=='i')
  {
    water=2;
    food=2;
    social=2;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='j')
  {
    water=1;
    food=2;
    social=0;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='k')
  {
    water=1;
    food=0;
    social=2;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='l')
  {
    water=2;
    food=1;
    social=0;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='m')
  {
    water=2;
    food=0;
    social=1;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='n')
  {
    water=0;
    food=1;
    social=2;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
  if (receivedChar=='o')
  {
    water=0;
    food=2;
    social=1;
    pixels1.clear();pixels1.show();pixels2.clear();pixels2.show();pixels3.clear();pixels3.show();
  }
  
}
