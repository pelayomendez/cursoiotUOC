
/* Recive ON / OFF commands from serial on MKR1000 and light inner LED
 * UOC iOT
 * Pelayo Méndez 
 * 
 */

String receivedChars = "";
bool newData = false;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop() {
    reciveData();
    showNewData();
}

void reciveData() {
  if (Serial.available() > 0 && newData == false) {
    receivedChars = Serial.readStringUntil('\n');
    Serial.flush();
    newData = true;
  }  
}

void showNewData() {
    if (newData == true) {
        Serial.println(receivedChars);
        if(receivedChars == "ON") {
          Serial.println("LED ON");
          digitalWrite(LED_BUILTIN, HIGH);
        }
        if(receivedChars == "OFF") {
          Serial.println("LED OFF");
          digitalWrite(LED_BUILTIN, LOW);
        }

        receivedChars = "";
        newData = false;
    }
}
