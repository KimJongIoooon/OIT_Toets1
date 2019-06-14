/*
  Toets OIT12
  Iain den Houting
  26/04/2018
  Fontys P01 S/T

  This program is a test for my technology class in the second period. It's a vault.
*/


// Pins
const int potPin = A0;    // select the input pin for the potentiometer
const int redLedPin = 13;      // pin for the red LED
const int greenLedPin = 11;    // pin for the Green LED
const int buttonPin = 12;

//Vault
bool codeSet = false; //true to hardcode the vaultcode
int vaultCode[] = {1, 1, 1, 1};
int inputCode[] = {0, 0, 0, 0};


bool lastButtonState;
  

int inputNumber;    //number seletected by user
int lastInputNumber = 50;

int numbersEntered; //amount of numbers guessed by user.



bool debounceButton(){
  
}
bool readButtonTrigger() {
  bool buttonState = digitalRead(buttonPin);
  bool trigger = false;
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      trigger = true;
    } 
    delay(50);//debounce delay
  }
  
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
  return trigger;  
}

int readInputNumber()
{
  int potValue = analogRead(potPin);
  return inputNumber =map(potValue, 0, 1023, 0, 25);
}

void displayVaultCode()
{
  if (numbersEntered >= 1)
  {
    Serial.print(vaultCode[0]);
    Serial.print("-");
  }
  if (numbersEntered >= 2)
  {
    Serial.print(vaultCode[1]);
    Serial.print("-");
  }
  if (numbersEntered >= 3)
  {
    Serial.print(vaultCode[2]);
    Serial.print("-");
  }

  Serial.println(inputNumber);
}

void displayInputCode()
{
  Serial.print("Enter Vault Code");

  if (numbersEntered >= 1)
  {
    Serial.print(inputCode[0]);
    Serial.print("-");
  }
  if (numbersEntered >= 2)
  {
    Serial.print(inputCode[1]);
    Serial.print("-");
  }
  if (numbersEntered >= 3)
  {
    Serial.print(inputCode[2]);
    Serial.print("-");
  }
  if (numbersEntered < 4) {
    Serial.println(inputNumber);
  }
}
bool checkCode() {

  Serial.print(inputCode[0]);
  Serial.print("-");
  bool wrong = true;
  
  for (int i = 0; i <= 2; i++) {
    if (!(inputCode[i] == vaultCode[i])) {
      wrong = false;
      break;
    }
  }
  return wrong;
}
void reset() {
  numbersEntered = 0;
  lastInputNumber = 50;//Out of range 0-25 so that is diffrent in next cyclus, so display will show at start
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}
void succes() {
  Serial.println("kluis Open");
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);
  delay(3000);
}
void fail() {
  Serial.println("kluis dicht");
  digitalWrite(greenLedPin, LOW);
  for (int i = 0; i <= 2; i++) {
    digitalWrite(redLedPin, LOW);
    delay(500);
    digitalWrite(redLedPin, HIGH);
    delay(500);
  }
}
void setup()
{
  Serial.begin(9600);//start serial monitor
  Serial.println("Serial begin 9600");

  // I/O
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  //blink red green
  digitalWrite(redLedPin, HIGH);
  delay(400);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, LOW);
  delay(400);
  digitalWrite(greenLedPin, LOW);
}

void loop()
{
  // read the value from the sensor:



  if (!codeSet)
  {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, HIGH);
    inputNumber = readInputNumber();
    if (lastInputNumber != inputNumber){
      Serial.print("Stel uw code in:");
      displayVaultCode();
    }
    lastInputNumber = inputNumber;
    if (readButtonTrigger())
    {
      vaultCode[numbersEntered] = inputNumber;
      numbersEntered++;
      lastInputNumber =50;
      
    }
    if (numbersEntered > 3)
    {
      
      Serial.print("Code is ");
      displayVaultCode();
      lastInputNumber = 50;
      delay(2500);
      numbersEntered=0;
      codeSet = true;
    } 
  }

  if (codeSet)
  {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    inputNumber = readInputNumber();
    if (lastInputNumber != inputNumber){
      Serial.print("Vul uw code in:");
      displayVaultCode();
    }
    lastInputNumber = inputNumber;
    if (readButtonTrigger())
    {
      inputCode[numbersEntered] = inputNumber;
      lastInputNumber = 50;
      numbersEntered++;
    }
    if (numbersEntered < 3)
    {
      digitalWrite(redLedPin, HIGH);
      
    }
    if (numbersEntered > 3)
    {
      bool codeCorrect = checkCode();
      if(codeCorrect){
        succes();    
      } else {
        fail();
      }
      reset();
    }
  }
}
