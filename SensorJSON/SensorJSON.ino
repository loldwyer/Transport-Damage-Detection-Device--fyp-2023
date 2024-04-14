 /*
  SensorJSON modified by MGill 2023

  Responds with a JSON string  when "readSensor\n" message is
  received on the Serial port

  It can be tested using Serial Monitor 9600 baud and newline

  Based on Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and
  clears it.

*/

//check if it is a launchpad
#if defined __msp430
#define LED_BUILTIN GREEN_LED
#endif
#include <Arduino.h> 

//Gravity Acceleration 
#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
#include "LIS3DHTR.h" 

#ifdef SOFTWAREWIRE 

    #include <SoftwareWire.h> 

    SoftwareWire myWire(3, 2); 

    LIS3DHTR<SoftwareWire> LIS;       //Software I2C 

    #define WIRE myWire 

#else 

    #include <Wire.h> 

    LIS3DHTR<TwoWire> LIS;           //Hardware I2C 

    #define WIRE Wire 

#endif 

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

float accel;  // To generate fake temperature value

//led 
int ledPin = 4; 
bool ledTriggered = false;

//buzzerx 
int buzzerPin = 5; // buzzer connected to pin 5

//initialize the button
int buttonPin=6;

String serialData = "";

void setup() {
	// initialize the OLED display 
    u8x8.begin(); 
    u8x8.setFlipMode(1); 

    // set the initial display message 
    u8x8.setFont(u8x8_font_chroma48medium8_r); 
	
	// initialize serial:
	Serial.begin(9600);
	// reserve 200 bytes for the inputString:
	inputString.reserve(200);
	randomSeed(0);  //generate same sequence each time for temp
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);  //led is off
	
	// initialize the accelerometer 
	LIS.begin(WIRE, 0x19); 
	delay(100); 
	LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
 
    // initialize the LED and buzzer 
    pinMode(ledPin, OUTPUT); 
    pinMode(buzzerPin, OUTPUT); 

    //initialize the button
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  
    if (!LIS) { 
        Serial.println("LIS3DHTR didn't connect."); 
        while (1); 
        return; 
    } 
    // Read accelerometer values 
    float x = LIS.getAccelerationX(); 
    float y = LIS.getAccelerationY(); 
    float z = LIS.getAccelerationZ(); 
    float accel=sqrt(x*x+y*y+z*z);
  Serial.print("Sensors={\"accel\":");Serial.print(accel);Serial.println("}");

    if (accel>= 1.5 && !ledTriggered) { //makes it so the led stays on until button is pressed
      Serial.println("ERROR: excessive acceleration detected");
	  tone(buzzerPin,2000,100);
	  ledTriggered = true; 
	  digitalWrite(ledPin, LOW);
  }

  // if the LED has been triggered and the button is pressed...
  if (ledTriggered && digitalRead(buttonPin) == HIGH) {
    
    ledTriggered = false;
    digitalWrite(ledPin, LOW); //turn off the LED
    
    // Clear OLED display
    u8x8.clearDisplay();
	
	//print message to the LED
    u8x8.setCursor(0,0);
    u8x8.print("button pressed");
	Serial.println("Button pressed");
    u8x8.setCursor(0,2);
    u8x8.print("Hardware");
    u8x8.setCursor(0,3);
    u8x8.print("resetting...");
    delay(2000);
    
    // Print welcome message
    u8x8.clearDisplay();
    u8x8.setCursor(0,0);
    u8x8.print("Welcome!");
    delay(500);
  }

  // if the LED has been triggered, display a different message on the OLED display
  if (ledTriggered) {
    u8x8.clearLine(0); // clear the first line of the OLED display
	
	//print message to the OLED
    u8x8.setCursor(0, 0);
    u8x8.print("Excessive Accel!");
    digitalWrite(ledPin, HIGH); //on
    u8x8.setCursor(0, 1);

    u8x8.print("Accel:");
    u8x8.print(accel);

    Serial.print("Sensors={\"accel\":");Serial.print(accel);Serial.println("}");
    delay(2000);
	
	u8x8.setCursor(0, 3);
	u8x8.print("Press button for");
	u8x8.setCursor(0,4);
	u8x8.print(" three seconds");


  } else {
	  //if accel<1.5
    u8x8.setFont(u8x8_font_chroma48medium8_r);

    u8x8.setCursor(0, 0);

    u8x8.print("Accel: ");
    u8x8.print(accel);
    delay(1000);

  }

  // clear the string:
  inputString = "";
  stringComplete = false;

}

  //SerialEvent occurs whenever a new data comes in the
  //hardware serial RX. This routine is run between each
  //time loop() runs, so using delay inside loop can delay
  //response. Multiple bytes of data may be available.

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
