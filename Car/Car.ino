#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

long lastsend = 0.001;//seconds

struct CarPackage
{
  int Motor1 = 0;
  int Motor2 = 0;// set the first mid range values for servos in resiver
};
typedef struct CarPackage Package2;
Package2 CarData;
const byte address[][6] = {"CA001", "NP2TE"}; // address

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);  //left motors forward
  pinMode(5, OUTPUT);  //left motors reverse
  pinMode(4, OUTPUT);  //right motors forward
  pinMode(3, OUTPUT);  //right motors reverse

  pinMode(2 , OUTPUT);
  radio.begin();
  radio.openWritingPipe(address[1]);    //NP2TE
  radio.openReadingPipe(1, address[0]); //CA001
  radio.setPALevel(RF24_PA_MAX);        //set nRF24L01
  radio.setChannel(115);
  radio.setDataRate(RF24_250KBPS);//nRF24L01 settings
  lastsend = millis() / 1000;
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    lastsend = millis() / 1000;//save the time of the last message
    radio.read(&CarData, sizeof(CarData));
    Serial.print("Motor1 = ");
    Serial.print(CarData.Motor1);
    Serial.print("\t Motor2 = ");
    Serial.println(CarData.Motor2);
    digitalWrite(2 , HIGH);
    /*if (CarData.Motor1 == 0) {
      digitalWrite(6 , LOW);
      digitalWrite(5 , LOW);
      } else if (CarData.Motor1 == 1) {
      digitalWrite(6 , HIGH);
      digitalWrite(5 , LOW);
      } else if (CarData.Motor1 == -1) {
      digitalWrite(6 , LOW);
      digitalWrite(5 , HIGH);
      }
      if (CarData.Motor2 == 0) {
      digitalWrite(4 , LOW);
      digitalWrite(3 , LOW);
      } else if (CarData.Motor2 == 1) {
      digitalWrite(4 , HIGH);
      digitalWrite(3 , LOW);
      } else if (CarData.Motor2 == -1) {
      digitalWrite(4 , LOW);
      digitalWrite(3 , HIGH);
      }*/
    lastsend = millis() / 1000;
  } else if (!radio.available()) {
    if (millis() - (lastsend * 1000) > 1200) {
      digitalWrite(2 , LOW);
      radio.stopListening();
      const char text[] = "Car-001";
      radio.write(&text, sizeof(text));//send the mode again to the hand
      delay(10);
      radio.startListening();
      lastsend = millis() / 1000;//save the time of the last message
    }
  }
}
