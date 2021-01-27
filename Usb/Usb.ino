#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

long lastsend = 0.001;//seconds

struct UsbPackage
{
  int Move = 0;
};
typedef struct UsbPackage Package2;
Package2 UsbData;
const byte address[][6] = {"US001", "NP2TE"}; // address
void setup() {
  pinMode(9, OUTPUT);  //right motors forward
  pinMode(6, OUTPUT);  //right motors reverse
  pinMode(2 , OUTPUT);
  radio.begin();
  radio.openWritingPipe(address[1]);    //NP2TE
  radio.openReadingPipe(1, address[0]); //US001
  radio.setPALevel(RF24_PA_MAX);        //set nRF24L01
  radio.setChannel(115);
  radio.setDataRate(RF24_250KBPS);//nRF24L01 settings
  lastsend = millis() / 1000;
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    lastsend = millis() / 1000;//save the time of the last message
    radio.read(&UsbData, sizeof(UsbData));
    digitalWrite(2 , HIGH);
    if(UsbData.Move == 1){
      digitalWrite(9, LOW);
      digitalWrite(6, HIGH);
    }else if(UsbData.Move == -1){
      digitalWrite(9, HIGH);
      digitalWrite(6, LOW);
    }else{
      digitalWrite(9, LOW);
      digitalWrite(6, LOW);
    }
    lastsend = millis() / 1000;
  } else if (!radio.available()) {
    if (millis() - (lastsend * 1000) > 1200) {
      digitalWrite(9, LOW);
      digitalWrite(6, LOW);
      digitalWrite(2 , LOW);
      radio.stopListening();
      const char text[] = "Usb-001";
      radio.write(&text, sizeof(text));//send the mode again to the hand
      delay(10);
      radio.startListening();
      lastsend = millis() / 1000;//save the time of the last message
    }
  }
}
