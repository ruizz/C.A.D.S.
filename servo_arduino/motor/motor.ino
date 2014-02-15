#include <Servo.h> 

unsigned const char DEGREE_DEFAULT_CHANGE = 45;

unsigned const char PIN_DETECTED = 8;
unsigned const char PIN_TOP_SERVO = 10;
unsigned const char PIN_BOTTOM_SERVO = 9;
unsigned const char PIN_ANALOG_DEGREE = A0;

unsigned const long TIME_DELAY_MS = 1000;

Servo bottomServo;
Servo topServo;

unsigned int globalDegree;
unsigned int detectedSoundDegree;
unsigned char bottomServoDegree;
unsigned char topServoDegree;

boolean isClockwise;
boolean isSoundDetected = false;

void setup() 
{ 
	Serial.begin(9600);   // for debugging

	pinMode(PIN_DETECTED, INPUT);

	// Set up the initial global degree.
	globalDegree = 0;
	isClockwise = true;

        // Attach each servo.
	bottomServo.attach(PIN_BOTTOM_SERVO);
	topServo.attach(PIN_TOP_SERVO);	

        // Set the degrees for each servo.
	bottomServoDegree = 180;
	topServoDegree = 0;
	bottomServo.write(bottomServoDegree);
	topServo.write(topServoDegree);

	// 2-second delay after set-up.
	delay(TIME_DELAY_MS);
} 


void loop() 
{  
	isSoundDetected = digitalRead(PIN_DETECTED);

	// If sound is detected, set servo to that position.
	if(isSoundDetected) {
                
                detectedSoundDegree = analogRead(PIN_ANALOG_DEGREE);
                detectedSoundDegree = detectedSoundDegree /  2.321066667;
                
                // If newly detected sound has over 30 degrees difference.
                if ((detectedSoundDegree > globalDegree
                && detectedSoundDegree - globalDegree > 30)
                ||(globalDegree > detectedSoundDegree
                && globalDegree - detectedSoundDegree > 30)) {
                  
		  Serial.println(detectedSoundDegree); // for debugging
		  setServoPosition(detectedSoundDegree);

                  globalDegree = detectedSoundDegree;
		  delay(TIME_DELAY_MS);
                }
	}
}

void setServoPosition(int degree) {
	if(degree < 180) {
  
		topServo.write(degree);
		bottomServo.write(180);		

	} else {
  
		topServo.write(degree - 180);
		bottomServo.write(0);
	}
}


