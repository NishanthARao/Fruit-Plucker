#include <Servo.h>
Servo bot;                                    //BOT IS THE SERVO OBJECT
int x, y, r;
int k = 0;
//X=300 AND R=70 ARE THE POINTS OF REFERENCE ON THE BASIS OF WHICH THE BOT MOVES FRONT/LEFT/RIGHT. (MORE LIKE THE ORIGIN)
void servo()
{
  bot.write(55);
  delay(1000);
  bot.write(0);
}

void backward()                                 //MOVES BOT BACK FOR 5 SECS AND STOPS FOR 5 SECS
{
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delay(3000);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  delay(3000);

}
void right()                                    //MOVES BOT RIGHT
{ analogWrite(6, 185);
  analogWrite(5, 185);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
}


void left()                                     //MOVES BOT LEFT
{
  analogWrite(6, 185);
  analogWrite(5, 185);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
}


void front()                                   //MOVES BOT FRONT
{
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
}

void stopb()                                    //STOPS THE BOT
{
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
}


void setup() {
  Serial.begin(9600);
  bot.attach(8);
  pinMode(12, OUTPUT);                         //RIGHT WHEEL INPUT, HIGH TO MOVE FRONT
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);                         //LEFT WHEEL INPUT, HIGH TO MOVE FRONT
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);                          //EN PINS
  pinMode(5, OUTPUT);
  analogWrite(6, 220);
  analogWrite(5, 220);
  bot.write(10);                               //SERVO PIN, SET INITIAL POSITION TO 10 DEGREES
  delay(3000);
}


void loop() {
  if (k == 1)                                                 //IT IS THE INDICATION THAT THE BOT HAS MOVED BACKWARD AND IS READY TO DETECT THE BALL
  {
    Serial.begin(9600);                                       //HENCE STARTS SENDING THE DATA INPUT OF THE NEXT BALL
    k = 0;
  }
  if (Serial.available() > 0)                                 //COLLECT ALL THE COORDINATES AND STORE THEM IN RESPECTIVE VARIABLES. x = X-COORDINATE. r = RADIUS
  {
    if (Serial.read() == 'X')
    {
      x = Serial.parseInt();
      if (Serial.read() == 'Y')
      {
        y = Serial.parseInt();
        if (Serial.read() == 'R')
        {
          r = Serial.parseInt();

        }
      }

      if (x < 250)                                            //CALL THE FUNCTION LEFT SO THAT BOT CAN MOVE LEFT TILL THE X-COORDINATE BECOMES 300.
      {
        left();
        analogWrite(6, 220);
        analogWrite(5, 220);
      }
      if (x > 350)                                            //CALL THE FUNCTION RIGHT SO THAT BOT CAN MOVE RIGHT TILL THE X-COORDINATE BECOMES 300.
      {
        right();
        analogWrite(6, 220);
        analogWrite(5, 220);
      }
      if (x > 250 && x < 350)
      {
        if (r > 30 && r < 80)
        {
          front();
        }
      }
      if (x < 350 && x > 250 && r > 80 && y < 40)             //THE BOT HAS REACHED THE BALL, READY TO HIT IT
      {
        stopb();
        servo();                                              //ACTIVATES THE ARM TO HIT BALL DOWN
        Serial.end();                                         //AFTER THE BALL IS COLLECTED, SERIAL LINE IS DISCONNECTED AND THE BOT MOVES BACKWARD.
        backward();
        k = 1;                                                //k==1 INDICATES THAT ONE TRANSACTION HAS COMPLETED. K IS REINITIALISED TO 0 IF THERE ARE ANY OTHER BALLS TO B COLLECTED.
      }
      if (r < 30)
      {
        stopb();
      }
    }

  }
  delay(10);                                                   //WILL NOT MAKE ANY DIFFERENCE, JUST A DUMMY STATEMENT.
}



























