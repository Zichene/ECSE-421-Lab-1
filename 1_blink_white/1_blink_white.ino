// define pin numbers
int RED_LED_PIN = 7;
int GREEN_LED_PIN = 4;
int BLUE_LED_PIN = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize pins
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // write high to all pins to produce white 
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);   
  delay(1000);                       // wait for a second
  // turn off all pins
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);     
  delay(1000);                       // wait for a second
}
