//Task 1:System setup

//motor pins
const int motor1pin1 = 7;
const int motor1pin2 = 6;
const int motor2pin1 = 5;
const int motor2pin2 = 4;
const int motor3pin1 = 10;
const int motor3pin2 = 11;
const int motor4pin1 = 12;
const int motor4pin2 = 13;

//ultrasonic senor pins
const int trig = 9;
const int echo = 8;

//LED indicators
const int leftLed = 3;
const int rightLed = 2;

void setup(){
  //Initializing motor pins as output
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);
  
  //Initializing ultrasonic sensor pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  //Initializing LEDs
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  
  Serial.begin(9600);//For debugging
}

//task 3: Function to measure distance from ultrasonic sensor
long Distance(){
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  long distance = duration * 0.034/2;
  return distance;
}

//Function to move forward
void moveForward(){
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor3pin1, HIGH);
  digitalWrite(motor3pin2, LOW);
  digitalWrite(motor4pin1, HIGH);
  digitalWrite(motor4pin2, LOW);
  
  //Blinking of the LEDs
  blinkLeds();
}

//Function to reverse
void moveReverse(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  digitalWrite(motor3pin1, LOW);
  digitalWrite(motor3pin2, HIGH);
  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, HIGH);
  
  //Blinking of the LEds
  blinkLeds();
}

//Function to turn left
void turnLeft(){
  //To turn left, left motors stop and right motors move forward
  //1 and 2 are the left motors whereas 3 and 4 are the right motors
  //Hence we have to stop 1st and 2nd motors and move forward 3rd and 4th motors
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor3pin1, HIGH);
  digitalWrite(motor3pin2, LOW);
  digitalWrite(motor4pin1, HIGH);
  digitalWrite(motor4pin2, LOW);
  
  //Left LED will turn on as we have to turn left
  digitalWrite(leftLed, HIGH);
  digitalWrite(rightLed, LOW);
}

//Function to turn right
void turnRight(){
  //To turn right, right motors stop and left motors move forward
  //Hence we have to stop 3rd and 4th motors and move forward 1st and 2nd motors
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor3pin1, LOW);
  digitalWrite(motor3pin2, LOW);
  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, LOW);
  
  //Right LED will turn on as we have to turn right
  digitalWrite(leftLed, LOW);
  digitalWrite(rightLed, HIGH);
}

//Blinking both the LEDs
void blinkLeds(){
  digitalWrite(rightLed, HIGH);
  digitalWrite(leftLed, HIGH);
  delay(100);
  digitalWrite(rightLed, LOW);
  digitalWrite(leftLed, LOW);
  delay(100);
}

void loop(){
  long distance = Distance();
  if(distance<30){//if distance is less than 30cm
    Serial.println("Turn Right");
    moveReverse();//Initiate a reverse movement for 2 seconds
    delay(2000);
    turnRight();//turn right
    delay(1000);
  }
  else if(distance<60){//if distance is less than 60cm
    Serial.println("Turn Left");
    moveReverse();//Initiate a reverse movement for 2 seconds
    delay(2000);
    turnLeft();//turn left
    delay(1000);
  }
  else{
    Serial.println("Move Forward");
    moveForward();
  }
  delay(100);
}