#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10 megohm between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
 */

//help from: https://www.youtube.com/watch?v=zq-TQv6WHOE

//CapacitiveSensor(a,b) pin a (resistor) is emitter and pin b is the receiving pin
CapacitiveSensor   sensor1 = CapacitiveSensor(3,2);        // 10 megohm resistor between pins a & b, pin b is sensor pin, add wire, foil
long elapsed = 0;
int state = HIGH;
bool threshold;
bool previous = false;
int debounce = 1000;
int counter = 0;
unsigned long StartTime = millis();

int led_pin = 11;

void setup()                    
{
   sensor1.set_CS_AutocaL_Millis(0xFFFFFFFF);
   pinMode(led_pin, OUTPUT);

   digitalWrite(led_pin,HIGH);
   delay(40);
   digitalWrite(led_pin,LOW);
   
   Serial.begin(9600);

}

void loop()                    
{
   unsigned long CurrentTime = millis();
   //Serial.print(CurrentTime);
   //Serial.print('\n');
   if (((CurrentTime - StartTime) >= 8000) && ((counter == 1) || (counter == 2))){
    //Serial.print("yes!");
    StartTime = millis();
    counter = 0;
    analogWrite(led_pin, 0);
   }
   long sensorValue = sensor1.capacitiveSensor(30);  
   Serial.println(counter);
   //Serial.println(sensorValue);
   if (sensorValue <= 30){
    threshold = true;
    //digitalWrite(led_pin,HIGH);
    //delay(1000);
    //digitalWrite(led_pin,LOW);
   }
   else{
    threshold = false;
   }
   if (threshold == true && previous == false && (millis() - elapsed) > debounce){
    counter++;
//    if (state == LOW){
//      state = HIGH;
//    }
//    else{
//      state = LOW;
//    }
    elapsed = millis();
   }

   if (counter == 1){
    analogWrite(led_pin, 63);
    //StartTime = millis();
    
   }
   if (counter == 2){
    analogWrite(led_pin, 150);
    //StartTime = millis();
   }
   if (counter == 3){
    analogWrite(led_pin, 255);
    delay(8000);
    counter = 0;
    analogWrite(led_pin, 0);
   }
//   if (counter > 3){
//    counter = 0;
//    analogWrite(led_pin, 0);
//   }
   previous = threshold;
   delay(10);
                    
}
