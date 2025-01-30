
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

// global variables
int counter = 0;
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

  // read the initial state of the rotary encoder's CLK pin and the SW pin
  prev_CLK_state = digitalRead(CLK_PIN);
  prev_SW_state = digitalRead(SW_PIN);
}

void loop() {
  // button.loop();  // MUST call the loop() function first
  
  // read the current state of the rotary encoder's CLK pin and SW pin
  CLK_state = digitalRead(CLK_PIN);
  SW_state = digitalRead(SW_PIN);

  // If the state of CLK is changed, then pulse occurred
  // React to only the rising edge (from LOW to HIGH) to avoid double count
  if (CLK_state != prev_CLK_state && CLK_state == HIGH) {
    // if the DT state is HIGH
    // the encoder is rotating in counter-clockwise direction => decrease the counter
    if (digitalRead(DT_PIN) == HIGH) {
      counter--;
    } else {
      // the encoder is rotating in clockwise direction => increase the counter
      counter++;
    }

    // display counter and value to serial
    Serial.print(" | COUNTER: ");
    Serial.println(counter);
  }

    // check if button is pressed and reset counter
  if (SW_state != prev_SW_state && SW_state == LOW) {
     Serial.println("The button has been pressed");
     counter = 0;
     Serial.println(" | COUNTER: ");
     Serial.println(counter);
  }

  // save state
  prev_CLK_state = CLK_state;
  prev_SW_state = SW_state;
}
