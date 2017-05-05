/*Copyright (c) 2017 Neetish Raj. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * for more details about the project refer the link
   https://github.com/NeetishRaj/Android-Xbee-3-nodes


 /*
      Emergency unit
      this xbee-arduino module is hooked with a JHD162A LCD and an HCSR-04 Ultrasonic sensor
      this modeule will be simulated as an Emergency Vehicle 
      1.Fire-Trucks
      2.Ambulance

      so the RSU must be able to identify it and broadcast it to other nodes in the network
      so for this project third module a normal vehicle must know the presence of emergency vehicle
      through RSU as soon as this unit enters the PAN range
      moreover ultrasonic sensor will help
      to provide warning from collision when in less than 2 meters from an object

      this modules consist of
      1. Arduino Uno board
      2. JHD162A LCD with 16x2 display(with 4-bit serial mode connection)
      3. HCSR-04 Ultra sonic Sensor
      4. Xbee S2C RF module (with Digimesh function set as an End-device) 
 */


/*   Pin Details   
     
     Arduino Digital 0 --> Tx of Xbee
     Arduino Digital 1 --> Rx of Xbee
     Arduino Digital 2 --> Pin 14 of LCD
     Arduino Digital 3 --> Pin 13 of LCD
     Arduino Digital 4 --> Pin 12 of LCD
     Arduino Digital 5 --> Pin 11 of LCD
     Arduino Digital 6 --> Pin 3 of LCD
     Arduino Digital 7 --> ---
     Arduino Digital 8 --> ---
     Arduino Digital 9 --> Pin 15 of LCD (for brightnes adjustment)
     Arduino Digital 10 --> Trig pin of Ultrasonic sensor
     Arduino Digital 11 --> Pin 6 of LCD(optional)
     Arduino Digital 12 --> Pin 4 of LCD(optional)
     Arduino Digital 13 --> Echo pin of Ultrasonic sensor
 
 */

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define trigPin 10
#define echoPin 13


char ch;
int Contrast=15;

SoftwareSerial xbee(0,1); // RX, TX


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//void serialEvent();

//void ultrasonic();

void setup() 
{ 
  //Ultrasonic SETUP
  
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);

   
 
  //TO LIGHT UP THE BACK LIGHT and set to brightness 288 upper limits can be 2000
  analogWrite(9,288);
 
  Serial.begin(9600);
 
  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Emergency");
  delay(1000);
  
  
  //xbee setup
  xbee.begin( 9600 );
  xbee.print('e');
  delay(1000);
}

void loop() 
{
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;

   if (!xbee.available())
   {
    lcd.setCursor(0,0);
    lcd.print("Not In  PAN");
    lcd.setCursor(12,0);
    lcd.print("E1");
    
   }
   else
   {
    lcd.setCursor(12,0);
    lcd.print("  ");
    
   }
  
 

 /* char a = xbee.read();
  if(a == 'e')
  {
    lcd.setCursor(0,0);
    lcd.print(" E In PAN");
    delay(1000);
  }*/

  if(!(distance >= 2 && distance <= 10))
  {

     char c = xbee.read();
     if(c=='s')
     {
        lcd.setCursor(0,0);
        lcd.print("SILENT ZONE");
        delay(1000);
     }

     if(c=='c')
     {
        lcd.setCursor(0,0);
        lcd.print("constrction");
        delay(1000);
     }

     if(c=='n')
     {
        lcd.setCursor(0,0);
        lcd.print("NO  PARKING");
        delay(1000);
     }
     if(c=='e')
     {
        lcd.setCursor(0,0);
        lcd.print("EMERGENCY  ");
        delay(1000);
     }
     if(c=='s')
     {
        lcd.setCursor(0,0);
        lcd.print("STATIONARY ");
        delay(1000);
     }
     
     
      lcd.setCursor(0,1);
      lcd.print("Distance = ");
      lcd.print(distance);
      delay(200);
  
    /* if (Serial.available())
     {
         // wait a bit for the entire message to arrive
         delay(100);
        
    
         // read all the available characters
          while (Serial.available() > 0)
        {
           // display each character to the LCD
           lcd.write(Serial.read());
           delay(1000); 
         }  
     } */ 
  }
  else
  {
     lcd.setCursor(0,1);
     lcd.print("Obstcle Detected");
     delay(200);
  }
 
}

/*void serialEvent()
{
    ch= Serial.read();
    if(ch=='E')
    {
     lcd.clear();
      lcd.print("emergency");
      delay(1000);
    }
    if(ch=='V')
    {
     lcd.clear();
      lcd.print("Vehicle");
      delay(1000);
    }
    if(ch=='P')
    {
     lcd.clear();
      lcd.print("parking");
      delay(1000);
    }
    
}*/






 
