#include <LiquidCrystal.h>
#include <dht_nonblocking.h>

/* pin setup for LCD */
LiquidCrystal lcd(7, 8, 9, 10, 11,12);

/* pin setup for DHT */
#define DHT_SENSOR_TYPE DHT_TYPE_11
static const int DHT_SENSOR_PIN = 4;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

void setup() {
  Serial.begin( 9600);
	lcd.begin(16, 2);	// Set up the LCD's number of columns and rows:
}

void loop() {
  float temperature;
  float humidity;

  if(dht_sensor.measure(&temperature, &humidity)){
    lcd.setCursor(0, 0);
    lcd.print( "T = " );
    lcd.print( temperature, 1 );
    lcd.print( "C" );
    lcd.setCursor(0, 1);
    lcd.print("H = ");
    lcd.print( humidity, 1 );
    lcd.print( "%" );
  }

	//lcd.setCursor(0, 1);	// Set the position of the cursor
	//lcd.print(millis() / 1000);	// print the number of seconds since reset:
}
