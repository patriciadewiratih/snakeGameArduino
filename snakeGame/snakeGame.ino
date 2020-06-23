#include "display.h"
#include "JC_Button.h"
#include "TimerOne.h"
#include "CapacitiveSensor.h"

#define onesecond 1000000

int buttonPin = 13;
int ledPinRed = 9;
int ledPinYellow = 8;
int ledPinGreen = 7;
int sensorValue = 0;
int sensorPin = A1;

int ledIntensity = 5;
int messageSpeed = 5;
int prevSensLeft = 0;
int prevSensRight = 0;

//snake parameters
int snakeLength = 1;              //1 is initial snake length 
int snakeSpeed = 1;

//cooridnates
struct Point{
  int row = -1;
  int col = -1;
//  Point(int row = -1, int col = -1): row(row), col(col) {}
};

Point snake[64];
Point food;

//directions
typedef enum {
  up      = 1,
  right   = 2,
  down    = 3,
  left    = 4
}directions;

directions dir = left;

typedef enum {
  intro = 0,
  play,
  gameOver,
  wait,
  win
} states;

states state;

//defining my button
Button button(buttonPin);
CapacitiveSensor leftControl = CapacitiveSensor(6,5);
CapacitiveSensor rightControl = CapacitiveSensor(4,3);

void setup(){
  Serial.begin(115200);
  button.begin();
  initialise();
  Timer1.initialize();
  Timer1.attachInterrupt(showGame, onesecond);
  Timer1.stop();
  

//  showSnakeMessage();           //intro screen
  state = intro;
}

void loop(){
  button.read();          //read the button
  
  switch (state){
    case intro:
      printToMatrix('-');

      sensorValue = analogRead(sensorPin);
//      sensorValue = map(sensorValue, 0, 1023, 0, 1);
//      Serial.println(sensorValue);
      
      snake[0].row = -1;
      snake[0].col = -1;
      snakeLength = 1;
      
      if (button.wasReleased()) {
        clearMatrix();
        state = play;
      }
    break;

    case play:
    //move everything inside here to a new state called wait
    //start timer and move to state wait
      Timer1.start();
      state = wait;
      generateFood();
    break;

    case wait:
      //controls
      controls();

      Serial.print("snakerow:");
      Serial.println(snake[0].row);
      Serial.print("snakecol:");
      Serial.println(snake[0].col);

      //checks if snake eats food
      if (snake[0].row == food.row && snake[0].col == food.col) {
        Serial.println("eaten");
        snakeLength++;
        generateFood();
      }

      //if snake eats its tail then gameover
        for (int f = 1; f < snakeLength; f++){
          if (snake[0].row == snake[f].row && snake[0].col == snake[f].col){
            state = gameOver;
          }
        }
      
      //turn on led and change the speed of the game
      if (snakeSpeed == 1){
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinGreen, HIGH);
        Timer1.setPeriod(onesecond);
      } else if (snakeSpeed == 2){
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinYellow, HIGH);
        Timer1.setPeriod(onesecond/2);
      } else {
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinRed, HIGH);
        Timer1.setPeriod(onesecond/4);
      }
      
      if (button.wasReleased()){
        if (snakeSpeed > 2){ 
          snakeSpeed = 1;
        } else {
          snakeSpeed++;
        }
      }
    break;

    case win:
      clearMatrix();
      Timer1.stop();
      printToMatrix('m');
      delay(750);
      digitalWrite(ledPinYellow, LOW);
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinGreen, LOW);
      state = intro;
    break;
      
    case gameOver:
    //stop timer and game over message
      Timer1.stop();
      printToMatrix(' ');
      delay(750);
      clearMatrix();
      digitalWrite(ledPinYellow, LOW);
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinGreen, LOW);
      state = intro;
    break;

    default:
      
    break;
  }
}

//functions

void initialise(){
  pinMode(buttonPin, INPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(sensorPin, INPUT);

  initialiseLED();

  //generate random numbers
  randomSeed(analogRead(A0));     //connected to unplugged pin just to read random noise
}

void showGame(){
  clearMatrix();

  for (int i = snakeLength; i > 0; i--){
    snake[i] = snake[i-1];
  }
  
  switch (dir){
    case up:
      snake[0].col--;
      fixEdge();
    break;

    case right:
      snake[0].row--;
      fixEdge();
    break;

    case down:
      snake[0].col++;
      fixEdge();
    break;

    case left:
      snake[0].row++;
      fixEdge();
    break;

    default:

    break;
  }
  
//  Serial.print("foodrow:");
//  Serial.println(food.row);
//  Serial.print("foodcol:");
//  Serial.println(food.col);
//  Serial.println(snakeLength);

  for (int c = 0; c < snakeLength; c++){
    printDot(snake[c].row, snake[c].col);
  }

  printDot(food.row, food.col);
  
}

void fixEdge(){
  snake[0].col < 0 ? snake[0].col += 8 : 0;
  snake[0].col > 7 ? snake[0].col -= 8 : 0;
  snake[0].row < 0 ? snake[0].row += 8 : 0;
  snake[0].row > 7 ? snake[0].row -= 8 : 0;
}

int controls(){
  //read controls
  long clockwise = leftControl.capacitiveSensor(100);
  clockwise = constrain(clockwise, 150, 3000);
  clockwise = map(clockwise, 150, 3000, 0, 1);
//  Serial.println(clockwise);

  long counterClockwise = rightControl.capacitiveSensor(100);
  counterClockwise = constrain(counterClockwise, 150, 3000);
  counterClockwise = map(counterClockwise, 150, 3000, 0, 1);
//  Serial.println(counterClockwise);

  if (prevSensLeft == 0){
    if (counterClockwise == 1){
    if (dir == up){
      dir = right;
    } else if (dir == right) {
      dir = down;
    } else if (dir == down){
      dir = left;
    } else if (dir == left){
      dir = up;
    }
    }
  }

  prevSensLeft = counterClockwise;

  if (prevSensRight == 0){
    if (clockwise == 1){
      if (dir == up){
        dir = left;
      } else if (dir == left) {
        dir = down;
      } else if (dir == down){
        dir = right;
      } else if (dir == right){
        dir = up;
      }
    }
  }

  prevSensRight = clockwise;
}

void generateFood(){
  if (snakeLength >= 5){
      state = win;
      return;
  }
  food.row = random(8);
  food.col = random(8);
}
