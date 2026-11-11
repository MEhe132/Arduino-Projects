#include <Servo.h>  
// Create a Servo object  
Servo myservo;  
// Pin connections from the supplied Proteus schematic  
const byte trigPin = 3; // SONAR1 TRIG -> Arduino D3  
const byte echoPin = 2; // SONAR1 ECHO -> Arduino D2  
const byte servoPin = 6; // Servo signal -> Arduino D6  
// Distance measurement variables  
unsigned long duration;  
float distanceCm;  
// Dustbin movement settings  
const byte openAngle = 90;  
const byte closeAngle = 0;  
const float detectionDistanceCm = 20.0; 

// Automatic closing timer  
unsigned long lastDetectionTime = 0;  
const unsigned long closeDelayMs = 1500;  
// Current lid state  
bool isOpen = false;  
void setup()  
{  
pinMode(trigPin, OUTPUT);  
pinMode(echoPin, INPUT);  
myservo.attach(servoPin);  
myservo.write(closeAngle); // Start with the lid closed  
Serial.begin(9600);  
delay(500);  
}  
void loop()  
{  
// Send a clean 10 microsecond trigger pulse  
digitalWrite(trigPin, LOW);  

delayMicroseconds(2);  
digitalWrite(trigPin, HIGH);  
delayMicroseconds(10);  
digitalWrite(trigPin, LOW);  
// Measure the HIGH pulse on ECHO; timeout = 30 ms  
duration = pulseIn(echoPin, HIGH, 30000UL);  
// Convert round-trip time to one-way distance  
if (duration == 0)  
{  
distanceCm = -1.0; // No valid echo before timeout
}  
else  
{  
distanceCm = (duration * 0.0343) / 2.0;  
}  
// Print the measurement for debugging  
Serial.print("Distance: ");  
if (distanceCm < 0)  
{  
Serial.println("No echo");  
}  
else 
{  
Serial.print(distanceCm);  
Serial.println(" cm");  
}  

// If an object is within the detection range, open/keep open  
if (distanceCm > 0 && distanceCm <= detectionDistanceCm)  
{  
myservo.write(openAngle);  
lastDetectionTime = millis();  
isOpen = true;  
Serial.println("DUSTBIN OPEN");  
}  
// Close only after the last valid detection has expired  
if (isOpen && (millis() - lastDetectionTime >= closeDelayMs))  
{  
myservo.write(closeAngle);  
isOpen = false;  
Serial.println("DUSTBIN CLOSED");  
}  

delay(100);  
} 