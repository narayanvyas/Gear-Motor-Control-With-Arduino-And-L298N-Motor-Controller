/*  Gear Motor Control With L298N Motor Controller And IR Remote
 * 
 *  GitHub URL - https://github.com/narayanvyas/Gear-Motor-Control-With-Arduino-And-L298N-Motor-Controller
 * 
 *  Developed By Web Dev Fusion
 *  URL - https://www.webdevfusion.com  
 *  
 * Components
 * ----------
 *  - Arduino Uno
 *  - L298N Motor Controller
 *  - IR Remote
 *  - Jumper Wires
 *  - 2 x Gear Motors
 *  - Battery Pack
 *  
 *  Libraries
 *  ---------
 *  - IRRemote - https://github.com/z3t0/Arduino-IRremote (Search In Library Manager)
 *  
 */

#include "IRremote.h"

int receiver = 11;           // Signal Pin of IR receiver to Arduino Digital Pin 11
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;

void setup()
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }
}

void translateIR() // takes action based on IR code received
// describing Remote IR codes 

{
  switch(results.value)
  {
    case 16724175:
      Serial.println("1 Pressed");
      analogWrite(enA, 0);
      break;
    case 16718055:
      Serial.println("2 Pressed");
      analogWrite(enA, 255);
      break;
    case 16743045:
      Serial.println("3 Pressed");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH); 
      break;
    case 16716015:
      Serial.println("4 Pressed");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW); 
      break;
    case 16726215:
      Serial.println("5 Pressed");
      analogWrite(enB, 0);
      break;
    case 16734885:
    case 71952287:
      Serial.println("6 Pressed");
      analogWrite(enB, 255);
      digitalWrite(in3, HIGH);
      break;
    case 16728765:
      Serial.println("7 Pressed");
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      break;
    case 16730805:
      Serial.println("8 Pressed");
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      break;
    case 16732845:
    case 1053031451:
      Serial.println("9 Pressed");
      break;
    case 16738455:
      Serial.println("0 Pressed");
      break;
    default: 
      Serial.println("Wrong Button");
      break;
  }
  delay(500);
} 
