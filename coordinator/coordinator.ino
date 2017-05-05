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
*/


 
 
 /*Coordinator unit
  
  Makes Arduino send 1 character or string via XBee wireless to another XBee connected arduino units
  It can be configured as
  1.No Parking Zone/Parking Zone
  2.Silent Zone
  3.Private Property
  4.Infrastructure or Road Side Unit
  5.Or any relevent application concerned with identification of mobile nodes in a range
  

  The circuit: 
  * RX is digital pin 0 (connect to TX of XBee)
  * TX is digital pin 1 (connect to RX of XBee)
 
 */

#include <SoftwareSerial.h>


SoftwareSerial xbee(2,3);// RX, TX


void setup()
{
  // set the data rate for the SoftwareSerial port
   Serial.begin(9600);
   
   Serial.println( "RSU started sending bytes via XBee" );
   Serial.println( "Silent Zone" );

  

   // set the data rate for the SoftwareSerial port
   xbee.begin( 9600 );
}

void loop() 
{
  /* send character or string whenever an active node appears in range
     via XBee to other XBee connected to Arduino*/ 
      int x=0;
      int t=0;
  
       xbee.print( 's' );
       delay(2000);
       t=t+1;

       xbee.print( 'c' );
        delay(2000);

        xbee.print( 'n' );
        delay(2000);

     /*  if(x==10)
       {
        xbee.print( 'c' );
        delay(2000);
       }

       if(x==20)
       {
        xbee.print( 'n' );
        delay(2000);
       }*/


       
       float i;
      //detect an emergency vehicle and broadcast to all nodes
       char c = xbee.read();
       
     
       if (t>=5 && t<=10)
       {
              for( i=0; i<10; i++)
              {
               //if(c=='e')
                 //{
                   xbee.print('e');
                   delay(2000);
                 //}
                //if(c=='s')
                //{
                 //xbee.print('s');
                 //delay(2000);
              }
       }
        
       
        t=0;
       if(t>=10 && t<=15)
       {
              for( i=0; i<10; i++)
              {
                 //if(c=='e')
                   //{
                  //xbee.print('e');
                  //delay(2000);
                  //}
                 //if(c=='s')
                  //{
                  xbee.print('s');
                  delay(2000);
              }
       }
     
       t=0;
       

       //detect any other vehicle and send it notifications or alerts
       /*if(c=='v')
       {
        xbee.print('v');
        delay(1000);
       }*/
       

 
}


