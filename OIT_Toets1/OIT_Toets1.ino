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
const int greenLedPin = 12;    // pin for the Green LED
const int buttonPin = 11;

//Vault
int vaultCode[] = {22, 1, 30, 0};
int inputCode[] = {0, 0, 0, 0};

//input
int inputNumber;    //number seletected by user
int numbersEntered; //amount of numbers guessed by user.

//button debouncing
bool codeSet = false;
bool buttonTriggered;
bool buttonState;
bool lastButtonState;
long lastDebounceTime = 0;
bool trigger = false;


void readButtonPress() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on
      trigger = HIGH;
    } else {
      // if the current state is LOW then the button went from on to off:

    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
}

int readInputNumber()
{
  int potValue = analogRead(potPin);
  return map(potValue, 0, 1023, 0, 25);
}

void displayVaultCode()
{

  if (numbersEntered >= 0)
  {

  }
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
  if (numbersEntered >= 0)
  {

  }
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

  Serial.println(inputNumber);
}
void reset(){
  numbersEntered = 0;
}
void succes(){
  digitalWrite(redLedPin, LOW);
  delay(500);
  digitalWrite(redLedPin, HIGH);
  delay(500);
  digitalWrite(redLedPin, LOW);
  delay(500);
  digitalWrite(redLedPin, HIGH);
  delay(500);
  digitalWrite(redLedPin, LOW);
  delay(500);
  digitalWrite(redLedPin, HIGH);
  delay(500);
  digitalWrite(redLedPin, LOW);
  delay(500);
}
void Fail(){
  
}
void setup()
{
  Serial.begin(9600);//start serial monitor
  Serial.println("Serial begin 9600");

  // I/O
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

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
  inputNumber = readInputNumber();
  readButtonPress();

  if (!codeSet)
  {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, HIGH);
    if (trigger == HIGH)
    {
      vaultCode[numbersEntered] = inputNumber;
      numbersEntered++;
      trigger = LOW;
    }
    if (numbersEntered > 3)
    {
      codeSet = True;
      Serial.print("Code is ");
      displayVaultCode();
    } else
    {
      Serial.print("Set Vault Code ");
      displayVaultCode();
    }

  }


  if (codeSet)
  {
    if (numbersEntered < 4)
    {
      digitalWrite(redLedPin, HIGH);
    }
    if (trigger == HIGH)
    {
      inputCode[numbersEntered] = inputNumber;
      numbersEntered++;
      trigger = LOW;
    }

    displayInputCode();
  }

}
