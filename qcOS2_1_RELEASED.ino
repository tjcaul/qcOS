/*Description
  Welcome to the aPhone 2 (parody of iPhone)(a is for Arduino)(does not have phone capabilities), a device slightly larger than a real touchscreen phone, with many apps:
  Utilities: Calculator, thermometer, Clock, Settings, Flashlight
  Entertainment: Space Invaders
  Other: Magic 8 Ball
*/

//App Order: Calculator, Thermometer, Magic 8 Ball, Clock, Space Invaders, Hyperdash Xtreme, Settings

/*Changelog
 * Added Hyperdash
 * Added Flashlight
*/

/*Build Device
  Right Input to 9
  Left Input to 8
  Enter Input to 7
  Home Input to 13
  Temperature to A0
  Peizo to 6
  Potentiometer to +, -, and LCD 3
  Use the following chart to connect the LCD:
   LCD   Pin
   1     -
   2     +
   3     Potentiometer Center
   4     12
   5     -
   6     11
   11    5
   12    4
   13    3
   14    2
   15    A1 Through 220 Ohms
   16    -
*/

#include <LiquidCrystal.h> //import the LCD library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //set up the LCD

//APPLICATION
int application = 0; //application key: 1 = calculator; 2 = Thermometer; 3 = Magic 8 Ball; 4 = Clock; 5 = Flashlight; 6 = Space Invaders; 7 = Hyperdash Xtreme; 8 = Settings
int selectedApp = 0; //used for the startup application selection
const int numberofapps = 8; //change to the number of applications in existence, not counting the home screen

//PINS
const int ledpin = A1; //the pin which the lcd LED is connected to
const int peizopin = 6;
const int rightpin = 9; //the pin which the up button is connected to
const int leftpin = 8; //the pin which the left button is connected to
const int enterpin = 7;
const int homepin = 13;
const int flashlightpin = A2; //the pin which the flashlight is connected to

//BUTTON-INGS
bool lefting = false; //used to prevent repeated operation on one button press
bool righting = false; //used to prevent repeated operation on one button press
bool entering = false; //used to prevent repeated operation on one button press

//BUTTON VALUES
int right = digitalRead(rightpin); //setting variables to pins
int left = digitalRead(leftpin);
int enter = digitalRead(enterpin);
int homescreen = digitalRead(homepin);

//SCREEN INFORMATION
bool sleeping = false;
int brightness = 255;

//OTHER INFORMATION
int times = 00;
int timem = 00;
int timeh = 0;



void setup() {
  // put your setup code here, to run once:

  lcd.begin(16, 2); //start using the LCD

  pinMode(enterpin, INPUT); //setting all pins to input
  pinMode(leftpin, INPUT);
  pinMode(rightpin, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(homepin, INPUT);
  pinMode(flashlightpin, OUTPUT);

  analogWrite(ledpin, 255);//turn on the LCD backlight

  lcd.print("    aPhone 2");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("  Arduino-made");
  delay(800);
  lcd.clear();


}

void loop() {
  right = digitalRead(rightpin); //setting variables to pins
  left = digitalRead(leftpin);
  enter = digitalRead(enterpin);

  delay(20); //to prevent freezing

  if (application == 0) { //if selection screen is displayed
    if (sleeping == false) {
      if (right == HIGH && righting == false) { //change selectedApp by 1 when right is pressed
        righting = true;
        delay(500);
        righting = false;
        selectedApp = (selectedApp + 1) % (numberofapps + 1);
      } //change selectedApp ends
      if (right == LOW) { //allow right to be used again
        righting == false;
      }
      if (left == HIGH && lefting == false) { //change selectedApp by -1 when left is pressed
        lefting = true;
        delay(500);
        lefting = false;
        selectedApp = selectedApp - 1;
        if (selectedApp < 0) { //if selectedApp becomes negative, set it to the highest number needed to reset the cycle
          selectedApp = numberofapps;
        }
      } //change selectedApp ends
      if (left == LOW) { //allow left to be used again
        lefting == false;
      }
      lcd.clear();
      switch (selectedApp) {
        case 0:
          lcd.print("    aPhone 2");
          lcd.setCursor(1, 1);
          lcd.print("Select an app!");
          break;
        case 1:
          lcd.print("   Calculator");
          lcd.setCursor(1, 1);
          lcd.print("+ - x / ^ v E !");
          break;
        case 2:
          lcd.print("  Thermometer");
          lcd.setCursor(1, 1);
          lcd.print("Degrees C & F");
          break;
        case 3:
          lcd.print(" Magic -8- Ball");
          lcd.setCursor(0, 1);
          lcd.print("Tell the Future!");
          break;
        case 4:
          lcd.print("     Clock");
          break;
        case 5:
          lcd.print("   Flashlight");
          lcd.setCursor(0, 1);
          lcd.print(" Fight the Dark");
          break;
        case 6:
          lcd.print(" Space Invaders");
          lcd.setCursor(1, 1);
          lcd.print("-Classic Game-");
          break;
        case 7:
          lcd.print("Hyperdash Xtreme");
          break;
        case 8:
          lcd.print("    Settings");
          break;
      } //switch ends
      if (enter == HIGH) {
        application = selectedApp;
      }
    }

    right = digitalRead(rightpin); //setting variables to pins, to prevent the Arduino thinking that a pin is activated when it is not
    left = digitalRead(leftpin);
    enter = digitalRead(enterpin);
    if (sleeping == true && right == HIGH && left == HIGH && enter == HIGH) { //wake up when right, left enter are all pressed
      analogWrite(ledpin, brightness);
      sleeping = false;
      delay(1000);
    }
    right = digitalRead(rightpin); //setting variables to pins, to prevent the Arduino thinking that a pin is activated when it is not
    left = digitalRead(leftpin);
    enter = digitalRead(enterpin);
    if (sleeping == false && right == HIGH && left == HIGH && enter == HIGH) { //sleep when right,left,and enter are all pressed
      analogWrite(ledpin, 0);
      lcd.clear();
      sleeping = true;
      delay(1000);
    }

  }
  if (application == 1) {//calculator

    //This calculator uses three buttons and does the following functions:
    //addition +, subtraction-, multiplicationx, division/, exponents^, rootsv, summationE, and  factorials!
    //Press the enter button to begin a new calculation
    //Press up or left to change number
    //Press enter once satisfied with the number
    //Press up or left to change operator
    //Press enter once satisfied with the operator
    //Press up or left to change number
    //Press enter once satisfied with the number, and to calculate the answer
    int progress = 1; //the step the input is on
    float num1 = 0; //the first number
    int op = 0; //the selected operation
    float num2 = 0; //the second number
    float ans; //the answer to the equation

    String tosay; //this is what the LCD will display
    int fact = 1;
    int summa = 0;
    homescreen = digitalRead(homepin);
    delay(500);
    while (homescreen == LOW)
    {
      delay(10);

      right = digitalRead(rightpin); //setting variables to pins, to prevent the Arduino thinking that a pin is activated when it is not
      left = digitalRead(leftpin);
      enter = digitalRead(enterpin);
      homescreen = digitalRead(homepin);

      tosay = String();
      tosay += num1;
      switch (op) {
        case 0:
          tosay += "+";
          break;
        case 1:
          tosay += "-";
          break;
        case 2:
          tosay += "x";
          break;
        case 3:
          tosay += "/";
          break;
        case 4:
          tosay += "^";
          break;
        case 5:
          tosay += "v";
          break;
        case 6:
          tosay += "E";
          break;
        case 7:
          tosay += "!";
          break;
      }
      tosay += num2;
      tosay += "=";


      lcd.clear();
      lcd.print(tosay);
      lcd.setCursor(0, 1);
      lcd.print(ans);


      if (right == LOW) { //if up is released, allows up to be used again, to stop repeated pressing
        righting = false;

      }
      if (left == LOW) { //if left is released, allows up to be used again, to stop repeated pressing
        lefting = false;
      }
      if (enter == LOW) { //if enter is released, allows up to be used again, to stop repeated pressing
        entering = false;
      }
      if (enter == HIGH && entering == false) { //changes step
        entering = true;
        progress = progress + 1;

      }
      if (right == HIGH && progress == 1 && righting == false) { //changes the first number
        righting = true;
        num1 = num1 + 1;
        delay(300);
        righting = false;
      }
      if (left == HIGH && progress == 1 && lefting == false) { //changes the first number
        lefting = true;
        num1 = num1 - 1;
        delay(300);
        lefting = false;
      }
      if (right == HIGH && progress == 2 && righting == false) {
        //changes the operator
        righting = true;
        op = (op + 1) % 8;
        delay(400);
        righting = false;
      }
      if (left == HIGH && progress == 2 && lefting == false) {
        //changes the operator
        lefting = true;
        op = (op - 1) % 8;
        if (op == -1) {
          op = 7;
        }
        delay(400);
        lefting = false;
      }
      if (right == HIGH && progress == 3 && righting == false) {
        //changes the second number
        righting = true;
        num2 = num2 + 1;
        delay(300);
        righting = false;
      }
      if (left == HIGH && progress == 3 && lefting == false) {
        //changes the second number
        lefting = true;
        num2 = num2 - 1;
        delay(300);
        lefting = false;
      }
      if (progress == 4 && op == 0) {
        ans = num1 + num2;
      }
      if (progress == 4 && op == 1) {
        ans = num1 - num2;
      }
      if (progress == 4 && op == 2) {
        ans = num1 * num2;
      }
      if (progress == 4 && op == 3) {
        ans = num1 / num2;
      }
      if (progress == 4 && op == 4) {
        ans = pow(num1, num2);
      }
      if (progress == 4 && op == 5) {
        ans = pow(num2, (1 / num1));
      }
      if (progress == 4 && op == 7) {
        fact = 1;
        for (int i = 1; i <= num1; i++)
        {
          fact = fact * i;
          delay(10);
        }
        ans = fact;
      }
      if (progress == 4 && op == 6) {
        summa = 0;
        for (int x = 1; x <= num1; x++)
        {
          summa = summa + x;
          delay(10);
        }
        ans = summa;
      }

      if (progress == 5) {//restart calculator
        progress = 1;
        lcd.clear();
        num1 = 0;
        op = 0;
        num2 = 0;
        ans = 0;
        fact = 1;
        summa = 0;
      } //restart calculator ends

    } //semi-infinite loop ends
    application = 0;
    selectedApp = 0;
    delay(500);
  } //application if statement ends
  if (application == 2) {//thermometer
    int tempSensorPin = 0;
    left = digitalRead(leftpin);
    enter = digitalRead(enterpin);
    homescreen = digitalRead(homepin);
    while (homescreen == LOW) {
      left = digitalRead(leftpin);
      enter = digitalRead(enterpin);
      homescreen = digitalRead(homepin);
      int tempSensorVal = analogRead(tempSensorPin);
      float tempVoltage = (tempSensorVal / 1024.0) * 5.0;
      float temperature = (tempVoltage - 0.5) * 100;
      if (enter == HIGH) {
        lcd.clear();
        lcd.print(temperature);
        lcd.print(" C");
        lcd.setCursor(0, 1);
        lcd.print((temperature * 1.8) + 32);
        lcd.print(" F");
        delay(10);
      }

    }//semi-infinite loop ends
    application = 0;
    selectedApp = 0;
    delay(500);
  }
  if (application == 3) {//magic 8 ball
    int logicReply; //this is what the screen will reply
    int numberReply; //this is what the screen will reply
    int letterReply;//this is what the screen will reply
    int logic = LOW;
    int number = LOW;
    int letter = LOW;
    lcd.clear();
    lcd.print("    Ask  the");
    lcd.setCursor(0, 1);
    lcd.print(" Magic -8- Ball");
    homescreen = digitalRead(homepin);
    delay(500);
    while (homescreen == LOW) { //semi-infinite loop begins
      logic = digitalRead(enterpin);
      number = digitalRead(rightpin);
      letter = digitalRead(leftpin);
      homescreen = digitalRead(homepin);

      delay(10);

      if ( logic == HIGH) {

        lcd.clear();
        logicReply = random(10);
        switch (logicReply) {

          case 0:
            lcd.print("Probably");
            break;
          case 1:
            lcd.print("Most Likely");
            break;
          case 2:
            lcd.print("Possibly");
            break;
          case 3:
            lcd.print("Ask again later");
            break;
          case 4:
            lcd.print("You don't want ");
            lcd.setCursor(0, 1);
            lcd.print("to know");
            break;
          case 5:
            lcd.print("Probably not");
            break;
          case 6:
            lcd.print("I don't think so");
            break;
          case 7:
            lcd.print("Maybe");
            break;
          case 8:
            lcd.print("Absolutely not");
            break;
          case 9:
            lcd.print("Absolutely");
            break;
        }
      } else if (number == HIGH) {
        lcd.clear();
        lcd.print(random(1000));
      } else if (letter == HIGH) {
        lcd.clear();
        letterReply = random(26);
        switch (letterReply) {

          case 0:
            lcd.print("A");
            break;
          case 1:
            lcd.print("B");
            break;
          case 2:
            lcd.print("C");
            break;
          case 3:
            lcd.print("D");
            break;
          case 4:
            lcd.print("E");
            break;
          case 5:
            lcd.print("F");
            break;
          case 6:
            lcd.print("G");
            break;
          case 7:
            lcd.print("H");
            break;
          case 8:
            lcd.print("I");
            break;
          case 9:
            lcd.print("J");
            break;
          case 10:
            lcd.print("K");
            break;
          case 11:
            lcd.print("L");
            break;
          case 12:
            lcd.print("M");
            break;
          case 13:
            lcd.print("N");
            break;
          case 14:
            lcd.print("O");
            break;
          case 15:
            lcd.print("P");
            break;
          case 16:
            lcd.print("Q");
            break;
          case 17:
            lcd.print("R");
            break;
          case 18:
            lcd.print("S");
            break;
          case 19:
            lcd.print("T");
            break;
          case 20:
            lcd.print("U");
            break;
          case 21:
            lcd.print("V");
            break;
          case 22:
            lcd.print("W");
            break;
          case 23:
            lcd.print("X");
            break;
          case 24:
            lcd.print("Y");
            break;
          case 25:
            lcd.print("Z");
            break;


        }
      }

    } //semi-infinite loop ends
    application = 0;
    selectedApp = 0;
    delay(500);
  } //magic 8 ball ends
  if (application == 4) { //clock app
    delay(500);
    int progress = 0;
    homescreen = digitalRead(homepin);

    //print time
    lcd.clear();
    lcd.print("    ");
    lcd.print(timeh);
    lcd.print(":");
    if (timem < 10) {
      lcd.print("0");
    }
    lcd.print(timem);
    lcd.print(".");
    if (times < 10) {
      lcd.print("0");
    }
    lcd.print(times);


    while (homescreen == LOW) {

      left = digitalRead(leftpin);
      right = digitalRead(rightpin);
      enter = digitalRead(enterpin);
      homescreen = digitalRead(homepin);

      if (right == LOW) { //if up is released, allows up to be used again, to stop repeated pressing
        righting = false;

      }
      if (left == LOW) { //if left is released, allows up to be used again, to stop repeated pressing
        lefting = false;
      }
      if (enter == LOW) { //if enter is released, allows up to be used again, to stop repeated pressing
        entering = false;
      }
      if (enter == HIGH && entering == false) { //changes step
        entering = true;
        if (progress < 3) {
          progress = progress + 1;
        } else {
          progress = 0;
        }
        lcd.clear();
        lcd.print("    ");
        lcd.print(timeh);
        lcd.print(":");
        if (timem < 10) {
          lcd.print("0");
        }
        lcd.print(timem);
        lcd.print(".");
        if (times < 10) {
          lcd.print("0");
        }
        lcd.print(times);
      }
      left = digitalRead(leftpin);
      right = digitalRead(rightpin);
      enter = digitalRead(enterpin);
      if (right == HIGH && progress == 1 && righting == false) { //changes the hr
        righting = true;
        if (timeh < 12) {
          timeh = timeh + 1;
        } else {
          timeh = 1;
        }
        lcd.clear();
        lcd.print("    ");
        lcd.print(timeh);
        lcd.print(":");
        if (timem < 10) {
          lcd.print("0");
        }
        lcd.print(timem);
        lcd.print(".");
        if (times < 10) {
          lcd.print("0");
        }
        lcd.print(times);
      }
      if (left == HIGH && progress == 1 && lefting == false) { //changes the hr
        lefting = true;
        if (timeh > 0) {
          timeh = timeh - 1;
        } else {
          timeh = 12;
        }
        lcd.clear();
        lcd.print("    ");
        lcd.print(timeh);
        lcd.print(":");
        if (timem < 10) {
          lcd.print("0");
        }
        lcd.print(timem);
        lcd.print(".");
        if (times < 10) {
          lcd.print("0");
        }
        lcd.print(times);
      }
      if (right == HIGH && progress == 2 && righting == false) {
        //changes the min
        righting = true;
        if (timem < 59) {
          timem = timem + 1;
        } else {
          timem = 0;
        }
        lcd.clear();
        lcd.print("    ");
        lcd.print(timeh);
        lcd.print(":");
        if (timem < 10) {
          lcd.print("0");
        }
        lcd.print(timem);
        lcd.print(".");
        if (times < 10) {
          lcd.print("0");
        }
        lcd.print(times);
      }
      if (left == HIGH && progress == 2 && lefting == false) {
        //changes the min
        lefting = true;
        if (timem > 0) {
          timem = timem - 1;
        } else {
          timem = 59;
        }
        lcd.clear();
        lcd.print("    ");
        lcd.print(timeh);
        lcd.print(":");
        if (timem < 10) {
          lcd.print("0");
        }
        lcd.print(timem);
        lcd.print(".");
        if (times < 10) {
          lcd.print("0");
        }
        lcd.print(times);
      }
      if (right == HIGH && progress == 3 && righting == false) {
        //changes the sec
        righting = true;
        if (times < 59) {
          times = times + 1;
        } else {
          times = 0;
        }
        lcd.clear();
        lcd.print("    ");
        lcd.print(timeh);
        lcd.print(":");
        if (timem < 10) {
          lcd.print("0");
        }
        lcd.print(timem);
        lcd.print(".");
        if (times < 10) {
          lcd.print("0");
        }
        lcd.print(times);
      }
      if (left == HIGH && progress == 3 && lefting == false) {
        //changes the sec
        lefting = true;
        if (times > 0) {
          times = times - 1;
        } else {
          times = 59;
        }
        lcd.clear();
        lcd.print("    ");
        lcd.print(timeh);
        lcd.print(":");
        if (timem < 10) {
          lcd.print("0");
        }
        lcd.print(timem);
        lcd.print(".");
        if (times < 10) {
          lcd.print("0");
        }
        lcd.print(times);
      }

      left = digitalRead(leftpin);
      right = digitalRead(rightpin);
      enter = digitalRead(enterpin);

      if (progress == 0) {
        delay(1000);

        times = times + 1;

        if (times > 59) {
          times = 0;
          timem = timem + 1;
        }
        if (timem > 59) {
          timem = 0;
          timeh = timeh + 1;
        }
        if (timeh > 12) {
          timeh = 1;

        }
        lcd.clear();
        lcd.print("    ");
        lcd.print(timeh);
        lcd.print(":");
        if (timem < 10) {
          lcd.print("0");
        }
        lcd.print(timem);
        lcd.print(".");
        if (times < 10) {
          lcd.print("0");
        }
        lcd.print(times);
      }


    }//semi-infinite loop ends
    application = 0;
    selectedApp = 0;
    delay(500);
  } //clock ends
  if (application == 5) {//flashlight

    int mode = 0; //modes are (in order): ON - 0, Flash - 1, Fast Flash - 2, Strobe - 3, SOS - 4
    bool on = true;
    int SOScycle = 0;

    left = digitalRead(leftpin);
    right = digitalRead(rightpin);
    enter = digitalRead(enterpin);
    homescreen = digitalRead(homepin);

    while (homescreen == LOW) {
      left = digitalRead(leftpin);
      right = digitalRead(rightpin);
      enter = digitalRead(enterpin);
      homescreen = digitalRead(homepin);

      delay(20);

      if (enter == HIGH) {
        if (on) {
          on = false;
          delay(500);
        } else if (on == false) {
          on = true;
          delay(200);
        }
      }

      left = digitalRead(leftpin);
      right = digitalRead(rightpin);
      enter = digitalRead(enterpin);
      homescreen = digitalRead(homepin);

      if (right == HIGH) {
        mode = (mode + 1) % 5;
        delay(200);
      }

      left = digitalRead(leftpin);
      right = digitalRead(rightpin);
      enter = digitalRead(enterpin);
      homescreen = digitalRead(homepin);

      if (left == HIGH) {
        mode = mode - 1;
        if (mode < 0) {
          mode = 4;
        }
        delay(200);
      }

      left = digitalRead(leftpin);
      right = digitalRead(rightpin);
      enter = digitalRead(enterpin);
      homescreen = digitalRead(homepin);

      lcd.clear();
      switch (mode) {
        case 0:
          lcd.print("      Lamp");
          break;
        case 1:
          lcd.print("     Flash");
          break;
        case 2:
          lcd.print("   Fast Flash");
          break;
        case 3:
          lcd.print("     Strobe");
          break;
        case 4:
          lcd.print("Morse Code S-O-S");
          break;
      }
      lcd.setCursor(0, 1);
      if (on == true) {
        lcd.print("       ON");
      } else {
        lcd.print("      OFF");
      }

      if (on) {
        switch (mode) {
          case 0:
            analogWrite(flashlightpin, 255);
            break;
          case 1:
            analogWrite(flashlightpin, 255);
            delay(1000);
            analogWrite(flashlightpin, 0);
            delay(1000);
            break;
          case 2:
            analogWrite(flashlightpin, 255);
            delay(200);
            analogWrite(flashlightpin, 0);
            delay(200);
            break;
          case 3:
            analogWrite(flashlightpin, 255);
            delay(20);
            analogWrite(flashlightpin, 0);
            delay(20);
            break;
          case 4:
            if (SOScycle == 0 || SOScycle == 1 || SOScycle == 2 || SOScycle == 6 || SOScycle == 7) {
              analogWrite(flashlightpin, 255);
              delay(300);
              analogWrite(flashlightpin, 0);
              delay(300);
              SOScycle = (SOScycle + 1) % 9;
            } else if (SOScycle == 8) {
              analogWrite(flashlightpin, 255);
              delay(300);
              analogWrite(flashlightpin, 0);
              delay(1500);
              SOScycle = (SOScycle + 1) % 9;
            } else {
              analogWrite(flashlightpin, 255);
              delay(600);
              analogWrite(flashlightpin, 0);
              delay(200);
              SOScycle = (SOScycle + 1) % 9;
            }
            break;

        }
      }

    } //semi-infinite loop ends
    application = 0;
    selectedApp = 0;
    delay(500);
  } //flashlight ends
  if (application == 6) { //Space invaders
    int level = 1;
    int points = 0;
    int alienPos = 0;
    int laserPos = 0;
    int firing;
    unsigned long oldTime = 0;
    unsigned long gameTime = 0;




    left = digitalRead(leftpin);
    right = digitalRead(rightpin);
    homescreen = digitalRead(homepin);
    bool tutorial = true;

    oldTime = millis();
    lcd.clear();
    while (homescreen == LOW) //Space Invaders semi-infinite code loop
    {
      if (tutorial) {
        lcd.clear();
        lcd.print("Use right & left");
        lcd.setCursor(0, 1);
        lcd.print("to move laser(|)");
        delay(3000);
        lcd.clear();
        lcd.print("Use enter");
        lcd.setCursor(0, 1);
        lcd.print("to fire laser");
        delay(3000);
        lcd.clear();
        lcd.print("Try to hit");
        lcd.setCursor(0, 1);
        lcd.print("the aliens (A)");
        delay(2000);
        lcd.clear();
        lcd.print("in the least");
        lcd.setCursor(0, 1);
        lcd.print("time possible");
        delay(2000);
        tutorial = false;
      }
      left = digitalRead(leftpin);
      right = digitalRead(rightpin);
      firing = digitalRead(enterpin);
      gameTime = millis() - oldTime;
      homescreen = digitalRead(homepin);

      delay(10);
      lcd.clear();
      firing = digitalRead(enterpin);
      for (int x = 0; x < alienPos; x++) {
        lcd.print(" ");
      }
      lcd.print("A ");
      lcd.print(level);

      lcd.setCursor(0, 1);
      for (int x = 0; x < laserPos; x++) {
        lcd.print(" ");
      }
      if (firing == HIGH) {
        lcd.print("Z ");
      } else {
        lcd.print("| ");
      }

      lcd.print(points);


      if (right == HIGH && laserPos < 11 && righting == false) { //moves laser right
        righting = true;
        laserPos = laserPos + 1;

      }
      if (right == LOW) {
        righting = false;
      }
      if (left == HIGH && laserPos > 0 && lefting == false) { //moves laser left
        lefting = true;
        laserPos = laserPos - 1;

      }
      if (left == LOW) {
        lefting = false;
      }
      if (firing == HIGH && alienPos == laserPos) { //checks if shot was successful
        lcd.clear();
        lcd.print("WIN!");
        level = level + 1;
        points = points + ((10000 - gameTime) / 1000);
        laserPos = 1;
        delay(1000);
        oldTime = millis();
      }
      switch (random(30 - level)) {
        case 0:
          if (alienPos < 13) {
            alienPos = alienPos + 1;
          }
          break;
        case 1:
          if (alienPos > 0) {
            alienPos = alienPos - 1;
          }
          break;
        case 2:
          alienPos = alienPos;
          break;
        case 3:
          alienPos = alienPos;
          break;
        case 4:
          alienPos = alienPos;
          break;
        case 5:
          alienPos = alienPos;
          break;
        case 6:
          alienPos = alienPos;
          break;
        case 7:
          alienPos = alienPos;
          break;
        case 8:
          alienPos = alienPos;
          break;
        case 9:
          alienPos = alienPos;
          break;
        case 10:
          alienPos = alienPos;
          break;
        case 11:
          alienPos = alienPos;
          break;
        case 12:
          alienPos = alienPos;
          break;
        case 13:
          alienPos = alienPos;
          break;
        case 14:
          alienPos = alienPos;
          break;
        case 15:
          alienPos = alienPos;
          break;
        case 16:
          alienPos = alienPos;
          break;
        case 17:
          alienPos = alienPos;
          break;
        case 18:
          alienPos = alienPos;
          break;
        case 19:
          alienPos = alienPos;
          break;
        case 20:
          alienPos = alienPos;
          break;
        case 21:
          alienPos = alienPos;
          break;
        case 22:
          alienPos = alienPos;
          break;
        case 23:
          alienPos = alienPos;
          break;
        case 24:
          alienPos = alienPos;
          break;
        case 25:
          alienPos = alienPos;
          break;
        case 26:
          alienPos = alienPos;
          break;
        case 27:
          alienPos = alienPos;
          break;
        case 28:
          alienPos = alienPos;
          break;
        case 29:
          alienPos = alienPos;
          break;
        case 30:
          alienPos = alienPos;
          break;
        case 31:
          alienPos = alienPos;
          break;
      }


    } //Space Invaders semi-infinite loop ends
    application = 0;
    selectedApp = 0;
    delay(500);
  } //Space Invaders app ends
  if (application == 7) {//hyperdash
    int PPos = 0; //position of the Player (vertical)
    int AAPos = 10; //position of the top left obstacle (horizontal)
    int ABPos = 15;//position of the top rightobstacle (horizontal)
    int BAPos = 7;//position of the bottom left obstacle (horizontal)
    int BBPos = 13;//position of the bottom right obstacle (horizontal)
    int distanceRun = 0; //the distance the player has run in the current life
    bool alive = false; //whether the player is currently alive or not
    unsigned long oldTime = millis(); //used for timing
    int waitTime = 800; //the time, in milliseconds, between movements of the obstacles
    int repeatsInLevel = 0; //the number of times the obstacles have moved since the waitTime changed

    homescreen = digitalRead(homepin);


    while (homescreen == LOW) {
      while (alive) {
        delay(10);
        lcd.clear();
        switch (PPos) {
          case 0:
            lcd.setCursor(1, 0);
            lcd.print("P");
            lcd.setCursor(2, 0);
            if (BAPos == 1) {
              lcd.setCursor(1, 1);
              lcd.print("O");
              lcd.setCursor(2, 0);
            }
            break;
          case 1:
            lcd.setCursor(1, 1);
            lcd.print("P");
            lcd.setCursor(2, 0);
            if (AAPos == 1) {
              lcd.setCursor(1, 0);
              lcd.print("O");
              lcd.setCursor(2, 0);
            }
            break;
        }
        for (int x = 0; x < (AAPos - 2); x++) {
          lcd.print(" ");
        }
       if (AAPos > 1) {
          lcd.print("O");
        } else {
          lcd.print(" ");
        }
        
        for (int x = 0; x < ((ABPos - AAPos) - 1); x++) {
          lcd.print(" ");
        }
          lcd.print("O");

        lcd.setCursor(2, 1);
        for (int x = 0; x < (BAPos - 2); x++) {
          lcd.print(" ");
        }
        if (BAPos > 1) {
          lcd.print("O");
        } else {
          lcd.print(" ");
        }
        for (int x = 0; x < ((BBPos - BAPos) - 1); x++) {
          lcd.print(" ");
        }
        lcd.print("O");

        if ((millis() - oldTime) > waitTime) {
          AAPos = AAPos - 1;
          ABPos = ABPos - 1;
          BAPos = BAPos - 1;
          BBPos = BBPos - 1;
          oldTime = millis();
          distanceRun = distanceRun + 1;
          repeatsInLevel = repeatsInLevel + 1;
        }

        if (AAPos == 1 && PPos == 0) {
          alive = false;
        }
        if (BAPos == 1 && PPos == 1) {
          alive = false;
        }

        if (AAPos < 1) {
          AAPos = ABPos;
          ABPos = (random(6) + 15);
          if (AAPos + 1 == ABPos) {
            ABPos = (random(6) + 15);
          }
        }
        if (BAPos < 1) {
          BAPos = BBPos;
          BBPos = (random(6) + 15);
          if (BAPos + 1 == BBPos) {
            BBPos = (random(6) + 15);
          }
        }

        if(AAPos + 1 == ABPos) {
          ABPos = ABPos + 1;
        }
        
         if(BAPos + 1 == BBPos) {
          BBPos = BBPos + 1;
        }
        
        for (int j = 0; j < 10000; j++) {
          if (BBPos - ABPos == 1 || BBPos - ABPos == 0 || BBPos - ABPos == -1 || BAPos - ABPos == 1 || BAPos - ABPos == 0 || BAPos - ABPos == -1 || BBPos - AAPos == 1 || BBPos - AAPos == 0 || BBPos - AAPos == -1 || BAPos - AAPos == 1 || BAPos - AAPos == 0 || BAPos - AAPos == -1) {
            ABPos = (random(6) + 15);
            BBPos = (random(6) + 15);
          }
        }

        left = digitalRead(leftpin);
        right = digitalRead(rightpin);
        enter = digitalRead(enterpin);
        homescreen = digitalRead(homepin);
        if (left == HIGH) {
          PPos = 0;
        }
        left = digitalRead(leftpin);
        right = digitalRead(rightpin);
        enter = digitalRead(enterpin);
        homescreen = digitalRead(homepin);
        if (right == HIGH) {
          PPos = 1;
        }


        if (repeatsInLevel > 30) {
          repeatsInLevel = 0;
          if (waitTime > 100) {
            waitTime = waitTime - 50;
          }

        }



      }//while (alive) loop ends

      lcd.clear();
      lcd.print(" Distance  Run:");
      lcd.setCursor(0, 1);
      lcd.print("     ");
      lcd.print(distanceRun);
      lcd.print(" m");
      while (enter == LOW) {
        delay(10);
        enter = digitalRead(enterpin);
      }

      homescreen = digitalRead(homepin);
      lcd.clear();
      lcd.print("       3");
      delay(1000);
      homescreen = digitalRead(homepin);
      lcd.clear();
      lcd.print("       2");
      delay(1000);
      homescreen = digitalRead(homepin);
      lcd.clear();
      lcd.print("       1");
      delay(1000);
      homescreen = digitalRead(homepin);
      lcd.clear();
      lcd.print("      RUN!");
      delay(1000);
      homescreen = digitalRead(homepin);
      lcd.clear();

      alive = true;
      distanceRun = 0; //the distance the player has run in the current life
      oldTime = millis(); //used for timing
      waitTime = 800; //the time, in milliseconds, between movements of the obstacles
      repeatsInLevel = 0; //the number of times the obstacles have moved since the waitTime changed
      PPos = 0; //position of the Player (vertical)
      AAPos = 10; //position of the top left obstacle (horizontal)
      ABPos = 15;//position of the top rightobstacle (horizontal)
      BAPos = 7;//position of the bottom left obstacle (horizontal)
      BBPos = 13;//position of the bottom right obstacle (horizontal)
      



    }//semi-infinite loop ends
    application = 0;
    selectedApp = 0;
    delay(500);
  }//hyperdash ends
  if (application == 8) {//settings

    //Setting Map:
    /* Options
        Brightness
         Set Brightness
       Info
        aphOS
         Version
         Release Date
         Changelog
         # of Applications
         Storage Used
         Lines of Code

        Device
         Controls
         Actuators
         Sensors
         Storage
         Made With Arduino Uno
    */

    int aSection = 1;
    int bSection = 1;
    int cSection = 1;
    int level = 1;
    homescreen = digitalRead(homepin);
    delay(1000);

    while (homescreen == LOW) {
      enter = digitalRead(enterpin);
      right = digitalRead(rightpin);
      left = digitalRead(leftpin);
      homescreen = digitalRead(homepin);

      delay(30);
      if (level == 1) {
        lcd.clear();
        switch (aSection) {
          case 1:
            lcd.print("    Options");
            break;
          case 2:
            lcd.print("      Info");
            break;
        }
      }
      if (level == 2) {
        lcd.clear();
        switch (aSection) {
          case 1://Options
            switch (bSection) {
              case 1:
                lcd.print("Brightness: ");
                lcd.print(brightness);
                break;
            }
            break;
          case 2://Info
            switch (bSection) {
              case 1:
                lcd.print("     aphOS");
                break;
              case 2:
                lcd.print("     Device");
                break;
            }
            break;
        }
      }
      if (level == 3) {
        lcd.clear();
        switch (aSection) {
          case 1://Options
            switch (bSection) {
              case 1://Brightness
                switch (cSection) {
                  case 1:
                    lcd.print(" Set Brightness");
                    lcd.setCursor(0, 1);
                    lcd.print(brightness);
                    break;
                }
                break;
            }
            break;
          case 2://Info
            switch (bSection) {
              case 1://aphOS
                switch (cSection) {
                  case 1:
                    lcd.print("  Version 2.1");
                    break;
                  case 2:
                    lcd.print("   Changelog:");
                    lcd.setCursor(0, 1);
                    lcd.print("Added  Hyperdash");
                    break;
                  case 3:
                    lcd.print("   Changelog:");
                    lcd.setCursor(0, 1);
                    lcd.print("Added Flashlight");
                    break;
                  case 4:
                    lcd.print(" 8 Applications");
                    break;
                  case 5:
                    lcd.print(" aphOS Uses 59%");
                    lcd.setCursor(0, 1);
                    lcd.print(" (19096  Bytes)");
                    break;
                  case 6:
                    lcd.print("      1567");
                    lcd.setCursor(0, 1);
                    lcd.print(" Lines of Code!");
                    break;
                }
                break;
              case 2://Device
                switch (cSection) {
                  case 1:
                    lcd.print("    aPhone 2");
                    break;
                  case 2:
                    lcd.print("  Controls:  4");
                    lcd.setCursor(0, 1);
                    lcd.print("Buttons and Dial");
                    break;
                  case 3:
                    lcd.print("Actuators: 16x2");
                    lcd.setCursor(0, 1);
                    lcd.print("LCD and a Piezo");
                    break;
                  case 4:
                    lcd.print("    Sensors:");
                    lcd.setCursor(0, 1);
                    lcd.print("  Temperature");
                    break;
                  case 5:
                    lcd.print("  Device Holds");
                    lcd.setCursor(0, 1);
                    lcd.print("34.304 Kilobytes");
                    break;
                  case 6:
                    lcd.print("   Made  With");
                    lcd.setCursor(0, 1);
                    lcd.print("  Arduino  Uno");
                    break;
                }
                break;
            }


        }
      }

      enter = digitalRead(enterpin);
      right = digitalRead(rightpin);
      left = digitalRead(leftpin);
      homescreen = digitalRead(homepin);

      if (enter == HIGH) {
        if (level < 3) {
          level = level + 1;
          delay(500);
        } else if (level > 2) {
          level = 1;
          aSection = 1;
          bSection = 1;
          cSection = 1;
          delay(500);
        }
      }

      enter = digitalRead(enterpin);
      right = digitalRead(rightpin);
      left = digitalRead(leftpin);
      homescreen = digitalRead(homepin);

      if (right == HIGH) {
        switch (level) {
          case 1:
            aSection = aSection + 1;
            delay(500);
            break;
          case 2:
            bSection = bSection + 1;
            delay(500);
            break;
          case 3:
            if (aSection == 1 && bSection == 1 && cSection == 1) {
              if (brightness < 250) {
                brightness = brightness + 5;
                analogWrite(ledpin, brightness);
                delay(100);
              }
            } else {
              cSection = cSection + 1;
              delay(500);
              break;
            }
            break;
        }
      }
      enter = digitalRead(enterpin);
      right = digitalRead(rightpin);
      left = digitalRead(leftpin);
      homescreen = digitalRead(homepin);

      if (left == HIGH) {
        switch (level) {
          case 1:
            aSection = aSection - 1;
            delay(500);
            break;
          case 2:
            bSection = bSection - 1;
            delay(500);
            break;
          case 3:
            if (aSection == 1 && bSection == 1 && cSection == 1) {
              if (brightness > 5) {
                brightness = brightness - 5;
                analogWrite(ledpin, brightness);
                delay(100);
              }
            } else {
              cSection = cSection - 1;
              delay(500);
              break;
            }
        }
      }
    }//semi-infinite settings loop ends
    application = 0;
    selectedApp = 0;
    delay(500);
  }//settings app ends
} //void loop() ends

