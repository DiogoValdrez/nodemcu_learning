/*This program is used to test the wiring of a relay
 * It should cycle throw on and off
 *
 *Esquematics are apresented in this folder with the 
 *same name as the code file(they work both on arduino 
 *and nodemcu).
 *
 *
 *Made by: Diogo Valdrez
 *Setember 2021
 *
 *https://github.com/DiogoValdrez
*/

#define RELAY D2

void setup() {
  pinMode(RELAY, OUTPUT);
}

void loop() {
  digitalWrite(RELAY, HIGH);
  delay(500);
  digitalWrite(RELAY, LOW);
  delay(500);
}
