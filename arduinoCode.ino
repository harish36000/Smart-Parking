int tDelay = 1000;

//Shift Register 1 Pins - Control LEDs
int latchPin1 = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin1 = 10;      // (9) SH_CP [SCK] on 74HC595
int dataPin1 = 12;     // (12) DS [S1] on 74HC595


int latchPin2 = 2; // green to 74HC595 pin 12
int clockPin2 = 3; // yellow to 74HC595 pin 11
int dataPin2 = 4;  // blue wire to 74HC595 pin 14

//IR Sensors
int IR8 = 8;
int IR7 = 7;
int IR6 = 6;
int IR5 = 5;

byte leds = 0;
void updateShiftRegister()
{
   digitalWrite(latchPin1, LOW);
   shiftOut(dataPin1, clockPin1, LSBFIRST, leds); 
   digitalWrite(latchPin1, HIGH);
}

void setup() 
{
  pinMode(latchPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);  
  pinMode(clockPin1, OUTPUT);

  pinMode(latchPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  
  pinMode(IR8,INPUT);
  pinMode(IR7,INPUT);
  pinMode(IR6,INPUT);
  pinMode(IR5,INPUT);

  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
}

const char common = 'c';    // common cathode

void myfnUpdateDisplay(byte eightBits) {
  if (common == 'a') {                  // using a common anonde display?
    eightBits = eightBits ^ B11111111;  // then flip all bits using XOR 
  }
  digitalWrite(latchPin2, LOW);  // prepare shift register for data
  shiftOut(dataPin2, clockPin2, LSBFIRST, eightBits); // send data
  digitalWrite(latchPin2, HIGH); // update display
}

byte myfnNumToBits(int someNumber) {
  switch (someNumber) {
    case 0:
      return B11111100;
      break;
    case 1:
      return B01100000;
      break;
    case 2:
      return B11011010;
      break;
    case 3:
      return B11110010;
      break;
    case 4:
      return B01100110;
      break;
    default:
      return B10010010; // Error condition, displays three vertical bars
      break;   
  }
}

void loop() 
{
  leds = 0;
  updateShiftRegister();

  //Detecting whether Car Present or NOT in each Slot
  int detect8=digitalRead(IR8);
  int detect7=digitalRead(IR7);
  int detect6=digitalRead(IR6);
  int detect5=digitalRead(IR5);

// Declare countHigh -> number of occupied slots -> count++ when detectI = HIGH
// SR2 Displays (4 - countHigh)

  int countHigh = 0;
  
  if(detect8 == HIGH)
    { bitSet(leds,0); countHigh++; }
  if(detect7 == HIGH)
    { bitSet(leds,1); countHigh++; }
  if(detect6 == HIGH)
    { bitSet(leds,2); countHigh ++; digitalWrite(9, LOW);}
  else 
    digitalWrite(9, HIGH);
  if(detect5 == HIGH)
    { bitSet(leds,3); countHigh ++; digitalWrite(13, LOW);}
  else 
    digitalWrite(13, HIGH);


    //Updating Counter Display
    byte SevenSegmentLEDs = myfnNumToBits(countHigh) ;
    myfnUpdateDisplay(SevenSegmentLEDs); 
    //delay(tDelay);

    //Turning LEDs on for Available Slots
    updateShiftRegister();

    int BitValInt;

    BitValInt = bitRead(leds, 3); //pin 5
    if(BitValInt == 0)
    {
      BitValInt = 41;
      Serial.println(BitValInt, DEC);
      delay(tDelay); 
    }
    else
    {
      BitValInt = 42;
      Serial.println(BitValInt, DEC);
      delay(tDelay);
    }

    BitValInt = bitRead(leds, 2); //pin 6
    if(BitValInt == 0)
    {
      BitValInt = 21;
      Serial.println(BitValInt, DEC);
      delay(tDelay); 
    }
    else
    {
      BitValInt = 22;
      Serial.println(BitValInt, DEC);
      delay(tDelay);
    }
    
    BitValInt = bitRead(leds, 1); //pin 7
    if(BitValInt == 0)
    {
      BitValInt = 31;
      Serial.println(BitValInt, DEC);
      delay(tDelay); 
    }
    else
    {
      BitValInt = 32;
      Serial.println(BitValInt, DEC);
      delay(tDelay);
    }   
    

    BitValInt = bitRead(leds, 0); //pin 8
    if(BitValInt == 0)
    {
      BitValInt = 11;
      Serial.println(BitValInt, DEC);
      delay(tDelay); 
    }
    else
    {
      BitValInt = 12;
      Serial.println(BitValInt, DEC);
      delay(tDelay);
    } 

 }