// Motor pinleri
const int ena = 11;         // Sol motor PWM (ENA)
const int in1 = 10;         // Sol motor IN1
const int in2 = 9;          // Sol motor IN2
const int enb = 6;          // Sağ motor PWM (ENB)
const int in3 = 8;          // Sağ motor IN3
const int in4 = 7;          // Sağ motor IN4

// Ultrasonik mesafe sensörü pinleri
const int trigPin = 2;      // Ultrasonik sensör Trig pini
const int echoPin = 3;      // Ultrasonik sensör Echo pini

void setup() {
  // Motor pinlerini çıkış olarak ayarla
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Ultrasonik sensör pinlerini ayarla
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Seri iletişim başlat
  Serial.begin(9600);
}

void loop() {
  // Ultrasonik sensörden mesafeyi al
  long distance = measureDistance();
  
  // Mesafeyi seri monitöre yaz
  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Eğer mesafe 20 cm'den azsa geriye git
  if (distance < 50) {
    moveBothMotorsForward(); // Eğer mesafe yeterliyse düz git

  } 
  else {
    turnRight(); // Daha sonra sağa dön
  }

    delay(10); // Döngüyü yavaşlatmak için kısa bir bekleme
}

// Mesafe ölçme fonksiyonu
long measureDistance() {
  // Trig pinine 10 mikro saniye HIGH sinyali gönder
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo pininden dönen süreyi oku
  long duration = pulseIn(echoPin, HIGH);
  
  // Mesafeyi hesapla (cm cinsinden)
  long distance = duration * 0.034 / 2;

  return distance;
}

// Sol motoru ileri hareket ettir
void moveLeftMotorForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 255); // Hızı maksimum yap
}

// Sağ motoru ileri hareket ettir
void moveRightMotorForward() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 255); // Hızı maksimum yap
}

// Her iki motoru da ileri hareket ettir
void moveBothMotorsForward() {
  moveLeftMotorForward();
  moveRightMotorForward();
}

// Sol motoru geri hareket ettir
void moveLeftMotorBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 255); // Hızı maksimum yap
}

// Sağ motoru geri hareket ettir
void moveRightMotorBackward() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 255); // Hızı maksimum yap
}

// Her iki motoru da geri hareket ettir
void moveBothMotorsBackward() {
  moveLeftMotorBackward();
  moveRightMotorBackward();
}

// Sağa dön: sol motor ileri, sağ motor geri
void turnRight() {
  moveLeftMotorForward();
  moveRightMotorBackward();
}

// Sola dön: sağ motor ileri, sol motor geri
void turnLeft() {
  moveRightMotorForward();
  moveLeftMotorBackward();
}
