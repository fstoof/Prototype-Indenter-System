#include <Wire.h>
#include "rgb_lcd.h"
#include "MMA7660.h"

rgb_lcd lcd;
MMA7660 accelemeter;

const int ledPin = 3;
const int accPin = 2;
const int buttonPin = 3;
//make some basic colors for when warning are present, or for "all clears"
const int red[3] = {255, 0, 0};
const int green[3] = {0, 255, 0};
const int black[3] = {0, 0, 0};
const int white[3] = {255, 255, 255};

void setup() {
    //initialize the digital pin 3 as an output, location the green LED is connected
    pinMode(ledPin, OUTPUT);
    //set button as input
    pinMode(buttonPin, INPUT);
    //setup accelemeter
    accelemeter.init();
    //set up the vibration sensor
    Serial.begin(9600);//in set color lcd example is 115200
    //set up LCD screen's number of columns and rows
    lcd.begin(16, 2);
    //turn screen background white to show it's 'alive'
    lcd.setRGB(white[0], white[1], white[2]);
}

//making different functions to do calculations, perform tasks

//prompt user if ready for next question
bool UserReady()
{
  bool ready;
  lcd.print("Press button for next question"); 
  //if the button is pressed, ask next question
  if (digitalRead(buttonPin) == HIGH)
  {
    ready =true;
  }
  else
  {
    ready = false;
  }
}

//ask for information needed
double getPoisson()
{
  double poisson;
  //poisson's ratio
  
  Serial.println("What do you estimate the poisson's ratio to be?");
  while(Serial.available() == 0) //returns zero if input is written
  {
  }
  poisson = Serial.parseFloat(); //read input from user, for int or float use parse
  if(poisson < 0 || poisson > 1)
  {
    Serial.println("Invalid ratio, poisson's ratio is 0-1\nRubber = 0.5\nPolymers = 0.44\nMetals = 0.3\nCork = 0.0");
    while(Serial.available() == 0) //returns zero if input is written
    {
    }
    poisson = Serial.parseFloat();
  }

  return poisson;
}

double getThickness()
{
  double thick;
  
  //dimensions of material
  Serial.println("How tall/thick is your speciman?");
  while(Serial.available() == 0) //returns zero if input is written
  {
  }
  thick = Serial.parseFloat(); //read input from user, for int or float use parse

  return thick;
}

double getWidth()
{
  double width;
  
  //dimensions of material
  Serial.println("How wide is your speciman?");
  while(Serial.available() == 0) //returns zero if input is written
  {
  }
  width = Serial.parseFloat(); //read input from user, for int or float use parse

  return width;
}

double getLength()
{
  double length;
  
  //dimensions of material
  Serial.println("How long is your speciman?");
  while(Serial.available() == 0) //returns zero if input is written
  {
  }
  length = Serial.parseFloat(); //read input from user, for int or float use parse

  return length;
}

double getIndentRadius()
{
  double radius;
  
  //dimensions of material
  Serial.println("What is the indenter radius?");
  while(Serial.available() == 0) //returns zero if input is written
  {
  }
  radius = Serial.parseFloat(); //read input from user, for int or float use parse

  return radius;
}

String getMaterial()
{
  String material;
  
  //dimensions of material
  Serial.println("What is the specimen's material?");
  while(Serial.available() == 0) //returns zero if input is written
  {
  }
  material = Serial.readString(); //read input from user, for int or float use parse

  return material;
}


void PrepExperiment()
{
  float poisson;
  float thickness;
  float length;
  float width;
  float radius;
  String material;

  
  const int delayTime = 1500;
  lcd.clear();
  lcd.print("Prepping");


  material = getMaterial();
  lcd.setCursor(0, 0);
  lcd.println("Material:");
  lcd.setCursor(0, 1);
  lcd.println(material);
  delay(delayTime);
  lcd.clear();

  poisson = getPoisson();
  lcd.setCursor(0, 0);
  lcd.println("Poisson's ratio:");
  lcd.setCursor(0, 1);
  lcd.println(poisson, 2);//round to two decimal places
  delay(delayTime);
  lcd.clear();

  thickness = 2;
  lcd.setCursor(0, 0);
  lcd.println("Thickness(cm):");
  lcd.setCursor(0, 1);
  lcd.println(thickness, 2);
  delay(delayTime);
  lcd.clear();

  width = 3.5;
  lcd.setCursor(0, 0);
  lcd.println("Width(cm):");
  lcd.setCursor(0, 1);
  lcd.println(width, 2);
  delay(delayTime);
  lcd.clear();

  length = 4.2;
  lcd.setCursor(0, 0);
  lcd.println("Length(cm):");
  lcd.setCursor(0, 1);
  lcd.println(length, 2);
  delay(delayTime);
  lcd.clear();

  radius = 20;
  lcd.setCursor(0, 0);
  lcd.println("Radius(mm):");
  lcd.setCursor(0, 1);
  lcd.println(radius, 2);
  delay(delayTime);
  lcd.clear();

  lcd.println("Ready to start");
}

int GetHeight()
{
  int8_t x;
	int8_t y;
	int8_t z;
	float ax,ay,az;
  accelemeter.getXYZ(&x,&y,&z);
  accelemeter.getAcceleration(&ax,&ay,&az);

  return z;
}

bool isStable()
{
  bool stable;
  int8_t x;
	int8_t y;
	int8_t z;
	float ax,ay,az;
  accelemeter.getXYZ(&x,&y,&z);
  accelemeter.getAcceleration(&ax,&ay,&az);
  if(x == 0 && y == 0)
  {
    lcd.println("Stable");
    stable = true;
  }
  else
  {
    stable = false;
  }
  return stable;
}

void ZeroHeight()
{
  if(isStable())//if the mechanism is stable
  {
    lcd.println("Height set to zero");
  }
  else
  {
    ZeroHeight(); //call this function again
  }

}


//calculate modulus of elasticity with the equation based off assumed 
double CalculateModulus(int indentDepth)
{
  indentDepth = GetHeight();
}

//loop is executed repeadetly forever
void loop() {

    lcd.setCursor(0, 0);
    lcd.println("Getting Height");
    lcd.setCursor(0, 1);
    lcd.println(GetHeight());
    delay(500);

    PrepExperiment();
    //print message 
    lcd.print("Begin Experiment");
    //change 5? parameters
    //1. angle of indenter is not changed
    //2. use touch sensor to verify the 
    //FINAL check if button is pushed to start everything again [idk if can do that in arduino :()]
    //5. no motion is noticed(change sensitivity with screw driver) 
    //for 5. the sensor(whole mechanism) will need to be in a polycarb box to prevent wind from interfering

}


