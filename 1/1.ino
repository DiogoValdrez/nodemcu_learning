/*With this you program can turn on and off the led 
 *with a button.
 *
 *Esquematics are apresented in this folder with the 
 *same name as the code file(they work both on arduino 
 *and nodemcu).
 *
 *Made by: Diogo Valdrez
 *Setember 2021
 *
 *https://github.com/DiogoValdrez
*/

#define BUTTON D2
#define LED D4

int buttonState = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

}

void loop() {
  buttonState = digitalRead(BUTTON);

  if(buttonState == HIGH) {
    digitalWrite(LED, HIGH);
    
  } else {
    digitalWrite(LED, LOW);
  }

}
