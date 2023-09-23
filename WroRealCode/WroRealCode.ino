#include <Servo.h>
int servoangle;
int threshold;
int normal = 48;
int counter = 0;
int id;
unsigned long previousMillis = 0;
const long interval = 1500;

unsigned long previousMilliservo = 0;
const int intervalservo = 2500;

bool turning;
bool goingforward;
bool everything;
bool Stop;
bool red;
bool green;
bool turningright = true;
bool secondroundredd;
bool r;
bool stop;

int turnn;
int errorr;

Servo turn;


#include <SparkFun_TB6612.h>
#define AIN1 4
#define AIN2 3
#define PWMA 6
#define STBY 9
const int offsetA = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

const int trigPin2 = 8;
const int echoPin2 = 7;

const int trigPin = 12;
const int echoPin = 13;

const int trigPin3 = 5;
const int echoPin3 = 2;



long duration;
int distance;

long duration2;
int distance2;


long duration3;
int distance3;




#include "HUSKYLENS.h"

HUSKYLENS hl;
 



void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);   // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);    // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT);   // Sets the echoPin as an Input
  pinMode(trigPin3, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT);   // Sets the echoPin as an Input


  turn.attach(11);




  Serial.begin(115200);
  servomain(70);


  delay(1000);
}

void loop() {
  
secondroundcenter(-120, -150);
  
}



void sonar1() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
}
void sonar2() {


  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;
}

void sonar3() {
  // Clears the trigPin
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echoPin3, HIGH);
  // Calculating the distance
  distance3 = duration3 * 0.034 / 2;
}







void motor(int Speed) {
  motor1.drive(Speed);
}

void servomain(int angle) {
  turn.write(angle);
}



void condition() {

  sonar3();



  if (distance3 < 45) {

    turning = false;
    goingforward = true;

  }

  else if (distance3 > 45) {
    goingforward = false;
    turning = true;
  }


  if (counter >= 12) {
    Stop = true;

    motor(0);
    everything = false;
  }
}


void condition2() {

  sonar1();
  sonar2();



  if (distance > 55) {

    turning = false;
    goingforward = true;

  }

  else if (distance < 55) {
    goingforward = false;
    turning = true;
  }


  if (counter >= 12) {
    Stop = true;

    motor(0);
    everything = false;
  }
}

void counterr() {
  unsigned long currentMillis = millis();

  if (distance3 > 45 or distance < 40) {
    // Check if the time interval has elapsed
    if (currentMillis - previousMillis >= interval) {
      // Increment the counter and update the previousMillis
      counter++;
      previousMillis = currentMillis;
    }
  }

  // You can perform other non-blocking tasks here

  // Print the counter value for debugging
  Serial.print("Counter: ");
  Serial.println(counter);
}


void secondroundcenter(int Speedfor1stround, int Turningspeed) {
  if (counter < 12) {
    everything = true;
    Stop = false;
  }

  else if (counter >= 12) {
    Stop = true;
    motor(0);
    everything = false;
    turning = false;
    Stop = true;
  }

  while (Stop == true) {
    servomain(46);
  }



  while (everything == true) {
    sonar2();


    condition2();

    while (goingforward == true) {

      sonar2();




      motor(Speedfor1stround);
      condition2();



      errorr = 40 - distance2;
      turnn = 48 - errorr * 1.5;


      if (turnn >= 80) {
        turnn = 80;
      }

      if (turnn <= 20) {
        turnn = 20;
      }

      Serial.println(turnn);
      servomain(turnn);
    }

    while (turning == true) {

      sonar3();

      condition2();
      counterr();
      motor(Turningspeed);

      int error = 40 - distance3;
      int turnn = (48 + 2.5 * error);

      if (turnn < 30) {
        turnn = 30;
      }

      if (turnn > 30) {
        turnn = 30;
      }
      Serial.println(turnn);

      servomain(turnn);
    }
  }
}





void firstround(int Speedfor2ndroundgreen, int Turningspeedgreen) {
  if (counter < 12) {
    everything = true;
    Stop = false;
  }

  else if (counter >= 12) {
    Stop = true;
    everything = false;
    turning = false;
    Stop = true;
  }

  while (Stop == true) {
    sonar3();
    Serial.println(distance3);
    motor(-100);
    servomain(42);
     delay(1000);
    servomain(48);
    motor(0);
    if(distance3 > 10){
      motor(0);
      stop = true;
      Stop = false;
    }
  }

  while(stop == true){
    
      motor(0);
  }



  while (everything == true) {
    sonar3();


    condition();

    while (goingforward == true) {
      sonar3();



      motor(Speedfor2ndroundgreen);
      condition();



      int error = 10 - distance3;
      int turnn = (48 + 2.5 * error);

      if (turnn < 35) {
        turnn = 35;
      }

      Serial.println(distance3);
      servomain(turnn);
    }

    while (turning == true) {
      sonar3();

      condition();
      counterr();
      motor(Turningspeedgreen);

      int error = 7 - distance3;
      int turnn = (48 + 2.5 * error);

      if (turnn < 24) {
        turnn = 24;
      }
      Serial.println(turnn);

      servomain(turnn);
    }
  }
}




void secondroundgreen(int Speedfor2ndroundgreen, int Turningspeedgreen) {
  if (counter < 12) {
    everything = true;
    Stop = false;
  }

  else if (counter >= 12) {
    Stop = true;
    motor(0);
    everything = false;
    turning = false;
    Stop = true;
  }

  while (Stop == true) {
    servomain(46);
  }



  while (everything == true) {
    sonar3();


    condition();

    while (goingforward == true) {
      sonar3();



      motor(Speedfor2ndroundgreen);
      condition();



      int error = 11 - distance3;
      int turnn = (48 + 2.5 * error);

      if (turnn < 20) {
        turnn = 20;
      }

      Serial.println(id);
      servomain(turnn);
    }

    while (turning == true) {
      sonar3();

      condition();
      counterr();
      motor(Turningspeedgreen);

      int error = 7 - distance3;
      int turnn = (48 + 2.5 * error);

      if (turnn < 20) {
        turnn = 20;
      }
      Serial.println(turnn);

      servomain(turnn);
    }
  }
}






void secondroundred(int Speedfor2ndroundred, int Turningspeedred) {

  if (counter < 12) {
    everything = true;
    Stop = false;
  }

  else if (counter >= 12) {
    Stop = true;
    motor(0);
    everything = false;
    turning = false;
    Stop = true;
  }

  while (Stop == true) {
    servomain(46);
  }



  while (everything == true) {
    sonar1();
    sonar2();


    condition2();

    while (goingforward == true) {
      Serial.println("-22222222222222222222222222222222");
      id = ID();
      if (id == 1) {
        secondroundgreen(-140, -160);
      } else if (id == -1) {
        secondroundcenter(-140, -160);
      }
      sonar1();
      sonar2();



      motor(Speedfor2ndroundred);
      condition2();



      int error = 9 - distance2;
      int turnn = (48 - 2 * error);

      if (turnn < 20) {
        turnn = 20;
      }
      if (turnn > 53) {
        turnn = 53;
      }

      Serial.println(id);
      servomain(turnn);
    }

    while (turning == true) {
      sonar2();
      sonar1();

      condition2();
      counterr();
      motor(Turningspeedred);

      int error = 5 - distance2;
      int turnn = (48 - 2 * error);

      if (turnn < 30) {
        turnn = 30;
      }

      if (turnn > 30) {
        turnn = 30;
      }
      Serial.println(distance);

      servomain(turnn);
    }
  }
}


void secondround() {
  id = ID();
  Serial.println(id);

  while (id == -1) {
    secondroundcenter(-140, -160);
  }
  while (id == 2) {
    secondroundred(-140, -160);
  }
  while (id == 1) {
    secondroundgreen(-140, -160);
  }
}






void huskeysetup() {
  Wire.begin();
  hl.begin(Wire);
}

void turntest() {
  servomain(58);
}


void red1() {
  sonar2();
  Serial.println(distance2);
}




void servowithdelay(int position, int d1, int d11, int position2, int d2, int s) {
  unsigned long currentMilliservo = millis();

  if (currentMilliservo - previousMilliservo >= intervalservo) {
    previousMilliservo = currentMilliservo;

    motor(s);

    servomain(position);
    delay(d1);
    motor((s + 20));
    servomain(48);
    delay(d11);
    motor(s);
    servomain(position2);
    delay(d2);
    servomain(48);
    motor(0);
    delay(9000);
  }
}


int ID2() {
  if (hl.begin(Wire)) {  // Try to connect to HuskyLens using I2C
    if (hl.request()) {
      HUSKYLENSResult closestBlock;
      int closestDistance = 9999;  // Initialize to a large value

      for (int i = 0; i < hl.available(); i++) {
        HUSKYLENSResult blocks = hl.get(i);
        int distance = (blocks.xCenter - 160) * (blocks.xCenter - 160) + (blocks.yCenter - 120) * (blocks.yCenter - 120);

        if (distance < closestDistance) {
          closestDistance = distance;
          closestBlock = hl.get(i);
        }
      }

      if (closestDistance < 9999) {
        return closestBlock.xCenter;
      }
    }
  }
  return -1;
}

int ID() {
  if (hl.begin(Wire)) {  // Try to connect to HuskyLens using I2C
    if (hl.request()) {
      HUSKYLENSResult closestBlock;
      int closestDistance = 9999;  // Initialize to a large value

      for (int i = 0; i < hl.available(); i++) {
        HUSKYLENSResult blocks = hl.get(i);
        int distance = (blocks.xCenter - 160) * (blocks.xCenter - 160) + (blocks.yCenter - 120) * (blocks.yCenter - 120);

        if (distance < closestDistance) {
          closestDistance = distance;
          closestBlock = hl.get(i);
        }
      }

      if (closestDistance < 9999) {
        return closestBlock.ID;
      }
    }
  }
  return -1;
}
