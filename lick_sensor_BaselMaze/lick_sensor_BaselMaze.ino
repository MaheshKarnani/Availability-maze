#include <CapacitiveSensor.h>
CapacitiveSensor   cs_10_11 = CapacitiveSensor(10,11);       // 10M resistor between pins 6 & 7, pin 7 is sensor pin
//Capacitive sensor
int cs_thresh;//look at serial monitor during testing to find a value
int var;
int cs1;
//outputs to Pi
const int ard_pi_lick = 12;//reports capacitive sensor to Pi
const int led = 13;//diagnostic led

void setup() 
{
    cs_10_11.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
    Serial.begin(9600);//setup serial
    pinMode(ard_pi_lick, OUTPUT);
    pinMode(led, OUTPUT);
    //collect lick sensor bsl
    delay(1000);
    var = 0;
    cs_thresh=0;
    while (var < 5) 
    {
      cs_thresh =  cs_thresh+cs_10_11.capacitiveSensor(1000);
      var++;
    }
    cs_thresh=(cs_thresh/5)+100;
    delay(1000);
    Serial.print("cs_threshold   ");  //show value for trouble shooting if serial monitor is on
    Serial.println(cs_thresh); 
}

void loop() 
{
    long cs1 = cs_10_11.capacitiveSensor(1000);
    var = 0;
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.println(cs1); 
    
    if (cs1<cs_thresh) //capacitive sensor
    {
        digitalWrite(ard_pi_lick, HIGH);
        digitalWrite(led, LOW);
    }  
    else
    {
        digitalWrite(ard_pi_lick, LOW); //on this old arduino low level is -5v and high is 0, so wired ground and pin reverse and coded high/low reverse.
        digitalWrite(led, HIGH);
    } 

    
}
