/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-rotary-encoder
 */
// NOTE: code below is modifed from the above link 

// pins
#define CLK_PIN 2
#define DT_PIN 4
#define SW_PIN 3
#define MIC_D0_PIN 7
#define MIC_A0_PIN A0
#define BUZZ_S_PIN 8

// global variables
int counter = 0;
float currentFreq = 1000; // in Hz
float microPhoneVal = 0;
int CLK_state;
int prev_CLK_state;
int SW_state;
int prev_SW_state;

void setup() {
  Serial.begin(9600);

  // configure encoder pins as inputs
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);

  // configure buzzer pin as output
  pinMode(BUZZ_S_PIN, OUTPUT);

  // configure mic digital pin and analog pin
  pinMode(MIC_D0_PIN, INPUT);
  pinMode(MIC_A0_PIN, INPUT);

  // read the initial state of the rotary encoder's CLK pin and the SW pin
  prev_CLK_state = digitalRead(CLK_PIN);
  prev_SW_state = digitalRead(SW_PIN);
}

void loop() { 
  // read the current state of the rotary encoder's CLK pin and SW pin
  CLK_state = digitalRead(CLK_PIN);
  SW_state = digitalRead(SW_PIN);

  // read mic pins
  microPhoneVal = analogRead(MIC_A0_PIN);
  int microPhoneActive = digitalRead(MIC_D0_PIN);

  // If the state of CLK is changed, then pulse occurred
  // React to only the rising edge (from LOW to HIGH) to avoid double count
  if (CLK_state != prev_CLK_state && CLK_state == HIGH) {
    // if the DT state is HIGH
    // the encoder is rotating in counter-clockwise direction => decrease frequency
    if (digitalRead(DT_PIN) == HIGH) {
      if (currentFreq > 1000) {
        currentFreq -= 1000;
       }
    } else {
      // the encoder is rotating in clockwise direction => increase frequency
      currentFreq += 1000;
    }

    // display frequency and value to serial
    Serial.print(" | Current Frequency ");
    Serial.println(currentFreq);
  }

    // check if button is pressed and reset freq to default of 2000 Hz
   if (SW_state != prev_SW_state && SW_state == LOW) {
    //Serial.println("The button is pressed");
    if (currentFreq != 0) {
      currentFreq = 0;
    } else {
      currentFreq = 1000;
    }
   
    Serial.print(" | Current Frequency ");
    Serial.println(currentFreq);
  }

  // save state
  prev_CLK_state = CLK_state;
  prev_SW_state = SW_state;


  Serial.println(microPhoneVal, 4);
  
  if (currentFreq == 0) {
    noTone(BUZZ_S_PIN);
  } else {
    tone(BUZZ_S_PIN, currentFreq);
  }
  // if (currentFreq != 0) {
  //     int periodUS = (int)(1000000/currentFreq);
  //     digitalWrite (BUZZ_S_PIN, HIGH) ; //send tone
  //     delayMicroseconds(periodUS/2);
  //     digitalWrite (BUZZ_S_PIN, LOW) ; //no tone
  //     delayMicroseconds(periodUS/2);
  // }

}
