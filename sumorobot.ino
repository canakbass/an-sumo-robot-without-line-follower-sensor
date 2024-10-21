// Motor pins
const int ena = 11;         // Left motor PWM (ENA)
const int in1 = 10;         // Left motor IN1
const int in2 = 9;          // Left motor IN2
const int enb = 6;          // Right motor PWM (ENB)
const int in3 = 8;          // Right motor IN3
const int in4 = 7;          // Right motor IN4

// Ultrasonic distance sensor pins
const int trigPin = 2;      // Ultrasonic sensor Trig pin
const int echoPin = 3;      // Ultrasonic sensor Echo pin

void setup() {
  // Set motor pins as outputs
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Get distance from ultrasonic sensor
  long distance = measureDistance();
  
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If distance is less than 50 cm, move forward
  if (distance < 50) {
    moveBothMotorsForward(); // Move forward if distance is sufficient
  } 
  else {
    turnRight(); // Otherwise, turn right
  }

  delay(10); // Short delay to slow down the loop
}

// Distance measurement function
long measureDistance() {
  // Send a 10 microsecond HIGH signal to the Trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration from the Echo pin
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance (in cm)
  long distance = duration * 0.034 / 2;

  return distance;
}

// Move the left motor forward
void moveLeftMotorForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 255); // Set speed to maximum
}

// Move the right motor forward
void moveRightMotorForward() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 255); // Set speed to maximum
}

// Move both motors forward
void moveBothMotorsForward() {
  moveLeftMotorForward();
  moveRightMotorForward();
}

// Move the left motor backward
void moveLeftMotorBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 255); // Set speed to maximum
}

// Move the right motor backward
void moveRightMotorBackward() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 255); // Set speed to maximum
}

// Move both motors backward
void moveBothMotorsBackward() {
  moveLeftMotorBackward();
  moveRightMotorBackward();
}

// Turn right: left motor forward, right motor backward
void turnRight() {
  moveLeftMotorForward();
  moveRightMotorBackward();
}

// Turn left: right motor forward, left motor backward
void turnLeft() {
  moveRightMotorForward();
  moveLeftMotorBackward();
}
