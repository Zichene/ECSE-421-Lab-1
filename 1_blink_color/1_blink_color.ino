// define pin numbers
int RED_LED_PIN = 7;
int GREEN_LED_PIN = 4;
int BLUE_LED_PIN = 2;

// define total time
int TOTAL_TIME_MS = 500;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize pins
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // red 
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);   
  delay(TOTAL_TIME_MS/6);  

  // yellow
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, LOW);   
  delay(TOTAL_TIME_MS/6);  

  // green
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, LOW);   
  delay(TOTAL_TIME_MS/6);  

  // blue 
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, HIGH);   
  delay(TOTAL_TIME_MS/6);

  // teal
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);   
  delay(TOTAL_TIME_MS/6);

  // purple 
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, HIGH);   
  delay(TOTAL_TIME_MS/6);
}
