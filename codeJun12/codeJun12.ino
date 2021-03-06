#define frontRightMotor 2
#define frontLeftMotor 1
#define backRightMotor 3
#define backLeftMotor 4

#define frontRightMotorPinPWM  8
#define frontRightMotorPinDIR  9
#define frontLeftMotorPinPWM  6
#define frontLeftMotorPinDIR  7
#define backRightMotorPinPWM  10
#define backRightMotorPinDIR  11
#define backLeftMotorPinPWM  12
#define backLeftMotorPinDIR  13



#define leftTrigPin 52
#define leftEchoPin 53
#define rightTrigPin 22
#define rightEchoPin 23
#define frontTrigPin 48
#define frontEchoPin 49
#define backTrigPin 46
#define backEchoPin 47
#define rotationTrigPin 50
#define rotationEchoPin 51

#define leftDistanceArray 1
#define rightDistanceArray 2
#define backDistanceArray 3
#define frontDistanceArray 4
#define rotationDistanceArray 5
#define distanceFromWall (15*26)
enum directions {
  north, south, east, west
};
int robotDirection = east;
int robotFutureDirection = east;
int lastChangeInDirection;
/* quick reference
 *
 *  robot moving speed = 100 PWM
 *  X is the long axis on the field
 *  Y is the short axis on the field
 *  the robot always faces east
 *
 *
 *
 *
 *
 *
 */
 //int SPEED = 50; //Speed constant for testing
//boolean[][] mazeMap = new boolean[25][9]; //[x][y]

//Walls: North, East, South, West

//************************PING SENSOR METHODS ***************************//
//Unified distance method
long getDistanceValue(int direction)
{
  long duration, distance;
  int trigPin, echoPin;
  switch(direction) {
    case east:
      trigPin = frontTrigPin;
      echoPin = frontEchoPin;
      break;
    case west:
      trigPin = backTrigPin;
      echoPin = backEchoPin;
      break;
    case north:
      trigPin = leftTrigPin;
      echoPin = leftEchoPin;
      break;
    case south:
      trigPin = rightTrigPin;
      echoPin = rightEchoPin;
      break;
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 5.59;

  return distance;
}

long getRightDistanceValue()
{
  long duration, distance;
  digitalWrite(rightTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightTrigPin, LOW);
  duration = pulseIn(rightEchoPin, HIGH);
  distance = duration / 5.59;

  return distance;
}
long getLeftDistanceValue()
{
  long duration, distance;
  digitalWrite(leftTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(leftTrigPin, LOW);
  duration = pulseIn(leftEchoPin, HIGH);
  distance = duration / 5.59;

  return distance;
}

long getFrontDistanceValue()
{
  long duration, distance;
  digitalWrite(frontTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(frontTrigPin, LOW);
  duration = pulseIn(frontEchoPin, HIGH);
  distance = duration / 5.59;

  return distance;
}
long getBackDistanceValue()
{
  long duration, distance;
  digitalWrite(backTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(backTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(backTrigPin, LOW);
  duration = pulseIn(backEchoPin, HIGH);
  distance = duration / 5.59;

  return distance;
}
long getRotationDistanceValue()
{
  long duration, distance;
  digitalWrite(rotationTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rotationTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(rotationTrigPin, LOW);
  duration = pulseIn(rotationEchoPin, HIGH);
  distance = duration / 5.59;

  return distance;
}

bool isWallOn(int direction) {
  return getDistanceValue(direction) < distanceFromWall;
}

bool isWallOnRight() {
  if (getRightDistanceValue() < distanceFromWall) {

    return true;
  }
  else {

    return false;
  }
}
bool isWallOnLeft() {
  if (getLeftDistanceValue() < distanceFromWall) {

    return true;
  }
  else {

    return false;
  }
}
bool isWallOnFront() {
  if (getFrontDistanceValue() < distanceFromWall) {

    return true;
  }
  else {

    return false;
  }
}
bool isWallOnBack() {
  if (getBackDistanceValue() < distanceFromWall) {

    return true;
  }
  else {

    return false;
  }
}
//************************MOVING METHODS ***************************//

void setMotorSpeed(char motor, int velocity) {
  int motorPWM = motor * 2 + 4;
  int motorDIR = motor * 2 + 5;
  analogWrite(motorPWM, abs(velocity));//0 =0% 255= 100%
  if (velocity > 0) {
    digitalWrite(motorDIR, HIGH);//current flow from A - TO - B
  }
  else {
    digitalWrite(motorDIR, LOW);//current flow from B - TO - A
  }
}

void setMotorSpeeds(int backLeft, int backRight, int frontLeft, int frontRight)
{
  setMotorSpeed(backLeftMotor, backLeft);
  setMotorSpeed(backRightMotor, -backRight);// this motor is inverted becuase of a wireing issue.
  setMotorSpeed(frontLeftMotor,  frontLeft);
  setMotorSpeed(frontRightMotor, frontRight);
}
void setRobotSpeed(int x, int y, int r)
{
  int frontLeft = x + y * PI / 2 - r;
  int frontRight = -x + y * PI / 2 + r;
  int backLeft = -x + y * PI / 2 - r;
  int backRight = x + y * PI / 2 + r;
  setMotorSpeeds(backLeft, backRight, frontLeft, frontRight);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int I = 5; I < 14; I++) {// go through ports 6-13 and set them to output
    pinMode(I, OUTPUT);//PWM is done through analog write
  }
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(backTrigPin, OUTPUT);
  pinMode(backEchoPin, INPUT);
  pinMode(rotationTrigPin, OUTPUT);
  pinMode(rotationEchoPin, INPUT);
}
void corectRotation() {

  int rotationOffset = getLeftDistanceValue() - getRotationDistanceValue();
  Serial.println(rotationOffset);
  setRobotSpeed(0, 0, rotationOffset * 3);
}




void allign() {
  int x = 0;
  int y = 0;
  int r = 0;
  //** X correction **//

  if (isWallOnRight()) {
    x = 5 - getRightDistanceValue();
  }
  else if (isWallOnLeft()) {
    x = getLeftDistanceValue() - 5 ;
  }
  else;


  /** Y correction * //
  if (isWallOnFront()) {
    y = 5 - getFrontDistanceValue();
  }
  else if (isWallOnBack()) {
    y = getBackDistanceValue() - 5 ;
  }
  else;*/

  setRobotSpeed(x,y,0);
}




















































































//*********************** LOOP METHOD ***************************//

void turnLeft() {
  switch(robotDirection) {
    case north:
      robotDirection = east;
      break;
    case east:
      robotDirection = south;
      break;
    case south:
      robotDirection = west;
      break;
    case west:
      robotDirection = north;
      break;
  }
}

void turnRight() {
  switch(robotDirection) {
    case north:
      robotDirection = west;
      break;
    case east:
      robotDirection = north;
      break;
    case south:
      robotDirection = east;
      break;
    case west:
      robotDirection = south;
      break;
  }
}

void loop() {

  turnLeft();

  while(isWallOn(robotDirection)) {
    turnRight();
  }


  /*if (millis() - lastChangeInDirection > 1910) {
    lastChangeInDirection = millis();
    Serial.print(isWallOnEast());
    Serial.print(isWallOnWest());
    Serial.print(isWallOnSouth());
    Serial.print(isWallOnNorth());
    //Serial.println(getEastDistanceValue());
    switch (robotDirection) {
      case north:
        Serial.println("north");
        setRobotSpeed(0, 50, 0);
        break;
      case south:
        Serial.println("south");
        setRobotSpeed(0, -50, 0);
        break;
      case east:
        Serial.println("east");
        setRobotSpeed(-50, 0, 0);
        break;
      case west:
        Serial.println("west");
        setRobotSpeed(50, 0, 0);
        break;
      default :
        Serial.println("ERROR");
        break;

    }
  }*/


  allign();
}
