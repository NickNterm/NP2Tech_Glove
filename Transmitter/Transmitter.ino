#include <EEPROM.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "U8glib.h"

const unsigned char logo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0x00, 0xc0, 0xfe, 0x00, 0x30, 0x07, 0xff, 0xe3, 0xfe, 0x00, 0xf8, 0x18, 0x07, 0x00,
  0x00, 0x07, 0x80, 0xc0, 0xff, 0x80, 0x30, 0x07, 0xff, 0xe3, 0xfe, 0x03, 0xfe, 0x18, 0x07, 0x00,
  0x00, 0x07, 0x80, 0xc0, 0xc1, 0xc0, 0x60, 0x00, 0x18, 0x03, 0x00, 0x07, 0x06, 0x18, 0x07, 0x00,
  0x00, 0x07, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x18, 0x03, 0x00, 0x0e, 0x02, 0x18, 0x07, 0x00,
  0x00, 0x06, 0xc0, 0xc0, 0xc0, 0xe1, 0x80, 0x00, 0x18, 0x03, 0x00, 0x1c, 0x00, 0x18, 0x07, 0x00,
  0x00, 0x06, 0xe0, 0xc0, 0xc0, 0xe3, 0x00, 0x00, 0x18, 0x03, 0x00, 0x1c, 0x00, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x60, 0xc0, 0xc0, 0xc7, 0xf8, 0x00, 0x18, 0x03, 0x00, 0x18, 0x00, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x70, 0xc0, 0xc0, 0xc7, 0xf8, 0x00, 0x18, 0x03, 0x00, 0x18, 0x00, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x38, 0xc0, 0xc3, 0xc0, 0x00, 0x00, 0x18, 0x03, 0xfc, 0x38, 0x00, 0x1f, 0xff, 0x00,
  0x00, 0x06, 0x18, 0xc0, 0xff, 0x80, 0x00, 0x00, 0x18, 0x03, 0xfc, 0x38, 0x00, 0x1f, 0xff, 0x00,
  0x00, 0x06, 0x1c, 0xc0, 0xfe, 0x00, 0x00, 0x00, 0x18, 0x03, 0x00, 0x18, 0x00, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x0c, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x03, 0x00, 0x18, 0x00, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x0e, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x03, 0x00, 0x18, 0x00, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x06, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x03, 0x00, 0x1c, 0x00, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x07, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x03, 0x00, 0x0e, 0x01, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x03, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x03, 0x00, 0x0f, 0x07, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x01, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x03, 0xff, 0x07, 0xfe, 0x18, 0x07, 0x00,
  0x00, 0x06, 0x01, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x03, 0xff, 0x01, 0xf8, 0x18, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00,
  0x00, 0x3f, 0xff, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0x03, 0xff, 0xf0, 0x00,
  0x00, 0x7f, 0xf0, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x3f, 0xf8, 0x00,
  0x01, 0xff, 0x80, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xfe, 0x00,
  0x03, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xff, 0xc0, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00,
  0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x3f, 0xf8, 0x00, 0x1f, 0xe0, 0x00, 0xff, 0x80,
  0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0xff, 0xe0, 0x00, 0x1f, 0xe0, 0x00, 0x7f, 0xc0,
  0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xe0, 0x00, 0x3f, 0xc0,
  0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x3f, 0xe0,
  0x1f, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xe0,
  0x1f, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x00, 0x7f, 0xf8, 0x00, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xe0,
  0x1f, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x00, 0x7f, 0xf8, 0x00, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xe0,
  0x1f, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xe0,
  0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x3f, 0xe0,
  0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xe0, 0x00, 0x3f, 0xc0,
  0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0xff, 0xe0, 0x00, 0x1f, 0xe0, 0x00, 0x7f, 0xc0,
  0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x3f, 0xf8, 0x00, 0x1f, 0xe0, 0x00, 0xff, 0x80,
  0x03, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xff, 0xc0, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00,
  0x01, 0xff, 0x80, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xfe, 0x00,
  0x00, 0x7f, 0xf0, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x3f, 0xf8, 0x00,
  0x00, 0x3f, 0xff, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0x03, 0xff, 0xf0, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00,
  0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};// Team logo

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

const int MPU = 0x68; //gyroscope address
const int okbtn = 3;
const int upbtn = 4;
const int downbtn = 2;//Init btn's pins
const int Finger1 = A3;
const int Finger2 = A2;
const int Finger3 = A1;
const int Finger4 = A7;//Init Flex sensor's pins
const int Laser = A0;

long searchtime = 0;//Int to get a 17 sec Search time

int okispushed = 0;
int uppushed = 0;
int downpushed = 0;//ints in order to know when btns are pressed
int devisenum = 0;
int selectdev = 0;//for devise selection
int selectopt = 1;//for option selection
int RFIDtags = 0;
int minVal = 265;
int maxVal = 402;
int xAxis;
int yAxis;
int zAxis;//gyroscope varaibles

String ConnectedDevise;//name of connected devise
String mode = "before search";//modes for screen
String options[] = {"Search", "Disconnect", "Select device", "Set RFID", "Clear RFIDs"};//options when devise is connected
String devises[20]; //devises that have been found

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

byte address[][6] = {"", "NP2TE"}; // address
String Name;//Name for the communication pipe

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);
RF24 radio(7, 8); // CE, CSN

struct ArmPackage {
  int servo1 = 90;
  int servo2 = 90;
  int servo3 = 76;
  int servo4 = 140;
};
typedef struct ArmPackage Package;
Package ArmData;//the package that NRF sends to Arm

struct CarPackage {
  int Motor1 = 0;
  int Motor2 = 0;
};
typedef struct CarPackage Package1;
Package1 CarData;//the package that NRF sends to Car

struct UsbPackage {
  int Move = 0;
};
typedef struct UsbPackage Package2;
Package2 UsbData;//the package that NRF sends to Car


void setup() {
  Serial.begin(9600);
  SPI.begin();      // Init SPI bus

  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);        // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true); // give basic data to MPU6050

  pinMode(Finger1, INPUT);
  pinMode(Finger2, INPUT);
  pinMode(Finger3, INPUT);
  pinMode(Finger4, INPUT); //Init sensors
  pinMode(Laser, OUTPUT);
  analogWrite(Laser, 0);
  pinMode(okbtn, INPUT_PULLUP);
  pinMode(upbtn, INPUT_PULLUP);
  pinMode(downbtn, INPUT_PULLUP);//Init Btns

  u8g.firstPage();
  do {
    u8g.drawBitmapP( 0, 0, 16, 64, logo);
  } while ( u8g.nextPage() );//print logo for 3 sec

  delay(3000);

  radio.begin();
  radio.openReadingPipe(1, address[1]); //NP2T2
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(115);
  radio.setDataRate(RF24_250KBPS);//start NRF communication
  radio.stopListening();
}

void loop() {
  int num0 = EEPROM.read(0);
  int num1 = EEPROM.read(1);
  RFIDtags = num0 * 10 + num1;

  if (mode != "connected" && mode != "searching") {
    if (mfrc522.PICC_IsNewCardPresent()) {
      if (mfrc522.PICC_ReadCardSerial()) {
        String content = "";
        byte letter;
        for (byte i = 0; i < mfrc522.uid.size; i++)
        {
          content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
          content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        content.toUpperCase();
        if (mode == "Set RFID") {
          WriteToEEPROM((RFIDtags * 19) + 2, content);
          WriteToEEPROM((RFIDtags * 19) + 14, ConnectedDevise);
          RFIDtags++;
          EEPROM.write(0, int(RFIDtags / 10));
          EEPROM.write(1, RFIDtags % 10);
          delay(200);
          mode = "connected";
        } else {
          for (int i = 0; i < RFIDtags; i++) {
            if (content == ReadEEPROM((i * 19) + 2, 12)) {
              mode = "connected";
              ConnectedDevise = ReadEEPROM((i * 19) + 14, 7);
              if (getValue(ConnectedDevise, '-', 0) == "Arm") {//set the final pipe name
                Name = "AR" + String(getValue(ConnectedDevise, '-', 1));
              } else if (getValue(ConnectedDevise, '-', 0) == "Car") {
                Name = "CA" + String(getValue(ConnectedDevise, '-', 1));
              } else if (getValue(ConnectedDevise, '-', 0) == "Usb") {
                Name = "US" + String(getValue(ConnectedDevise, '-', 1));
              } else if (getValue(ConnectedDevise, '-', 0) == "Uni") {
                Name = "UN" + String(getValue(ConnectedDevise, '-', 1));
              }
              Name.getBytes(address[0], 6);//get string name and convert it to bytes
              radio.openWritingPipe(address[0]);
              Delete();
              devises[0] = ConnectedDevise;
              devisenum = 1;
            }
          }
        }
      }
    }
  }

  if (mode == "before search" && devisenum == 0) {//When 0 devises are saved and is before search
    u8g.firstPage();
    do {
      Print(1, 0);
    } while ( u8g.nextPage() );
  } else if (mode == "before search" && devisenum == -1) {//When 0 desive found on search
    u8g.firstPage();
    do {
      Print(3, 0);
    } while ( u8g.nextPage() );
  } else if (mode == "connected") {//when is connected (devisenum>0)
    u8g.firstPage();
    do {
      Print(4, selectopt);
    } while ( u8g.nextPage() );
  } else if (mode == "Set RFID") {
    u8g.firstPage();
    do {
      Print(5, 0);
    } while ( u8g.nextPage() );
  }

  if (digitalRead(okbtn) == LOW && mode != "searching") {
    okispushed = 1;
  }//ok button is pressed

  if (digitalRead(okbtn) == HIGH && okispushed == 1 && mode != "searching") {//ok button was pressed
    okispushed = 0;
    if (mode == "before search") {
      Delete();
      selectdev = 0;
      searchtime = millis() / 1000;
    } else if (mode == "select devise") {//select devise and get connected
      ConnectedDevise = devises[selectdev];
      mode = "connected";
      if (getValue(ConnectedDevise, '-', 0) == "Arm") {//set the final pipe name
        Name = "AR" + String(getValue(ConnectedDevise, '-', 1));
      } else if (getValue(ConnectedDevise, '-', 0) == "Car") {
        Name = "CA" + String(getValue(ConnectedDevise, '-', 1));
      } else if (getValue(ConnectedDevise, '-', 0) == "Usb") {
        Name = "US" + String(getValue(ConnectedDevise, '-', 1));
      } else if (getValue(ConnectedDevise, '-', 0) == "Uni") {
        Name = "UN" + String(getValue(ConnectedDevise, '-', 1));
      }
      Name.getBytes(address[0], 6);//get string name and convert it to bytes
      radio.openWritingPipe(address[0]);
    } else if (mode == "connected") {
      if (selectopt == 0) {//start searching
        ConnectedDevise = "";
        Delete();
        selectopt = 1;
        selectdev = 0;
        searchtime = millis() / 1000;
      } else if (selectopt == 1) {//go in first menu before search
        mode = "before search";
        ConnectedDevise = "";
        Delete();
        selectdev = 0;
      } else if (selectopt == 2) {//select a deivse again from the already found
        mode = "select devise";
        ConnectedDevise = "";
        selectdev = 0;
      } else if ( selectopt == 3) {
        mode = "Set RFID";
      } else if (selectopt == 4) {
        for (int i = 0 ; i < EEPROM.length() ; i++) {
          EEPROM.write(i, 0);
        }
      }
    }
  }

  if (searchtime != 0 && millis() - searchtime * 1000 < 17000) {//searching
    mode = "searching";
    search();
  } else if (devisenum > 0 && mode != "connected" && mode != "Set RFID") { //while devises are found
    radio.stopListening();
    mode = "select devise";
    selectopt = 1;
    u8g.firstPage();
    do {
      Print(2, selectdev);
    } while ( u8g.nextPage() );
  } else if (devisenum == 0 && mode == "searching") {//no devise found
    radio.stopListening();
    devisenum = -1;
    mode = "before search";
  }

  if (digitalRead(upbtn) == LOW) {
    uppushed = 1;
  }//up btn is pressed

  if (digitalRead(upbtn) == HIGH && uppushed == 1) {//up button was pressed
    uppushed = 0;
    if (mode == "select devise") { //go to the upper devise
      if (selectdev >= 1) {
        selectdev--;
      }
    }
    if (mode == "connected") {//go to the upper option
      if ( selectopt > 0) {
        selectopt--;
      }
    }
  }

  if (digitalRead(downbtn) == LOW) {
    downpushed = 1;
  }//down btn is pressed

  if (digitalRead(downbtn) == HIGH && downpushed == 1) {//down btn was pressed
    downpushed = 0;
    if (mode == "select devise") { // go one devise down
      if ( selectdev < devisenum - 1) {
        selectdev++;
      }
    }
    if (mode == "connected") {//go one option down
      if (selectopt < 4) {
        selectopt++;
      }
    }
  }

  if (getValue(ConnectedDevise, '-', 0) == "Arm" && mode == "connected") { //split the ID of the connected devise and know if it is car or arm
    gyro();
    if (yAxis >= 45 && yAxis <= 90) { // if the hand is pointing upwards then calculate the degrees of the bended finger //*++degrees
      if (analogRead(Finger1) > 850) { // first finger
        if (ArmData.servo1 < 180) {
          ArmData.servo1 = ArmData.servo1 + 3;
        }
      }
      else if (analogRead(Finger2) > 850) { // second finger
        if (ArmData.servo2 < 180) {
          ArmData.servo2 = ArmData.servo2 + 3;
        }
      }
      else if (analogRead(Finger3) > 850) { // third finger
        if (ArmData.servo3 < 130) {
          ArmData.servo3 = ArmData.servo3 + 3;
        }
      }
      else if (analogRead(Finger4) > 900) { // fourth finger
        if (ArmData.servo4 < 180) {
          ArmData.servo4 = ArmData.servo4 + 3;
        }
      }
    } else if (yAxis >= 250 && yAxis <= 330) { // if the hand is pointing downwards then calculate the degrees of the bended finger //*--degrees
      if (analogRead(Finger1) > 850) {      // first finger
        if (ArmData.servo1 > 0) {
          ArmData.servo1 = ArmData.servo1 - 3;
        }
      }
      else if (analogRead(Finger2) > 850) { // second finger
        if (ArmData.servo2 > 70) {
          ArmData.servo2 = ArmData.servo2 - 3;
        }
      } else if (analogRead(Finger3) > 850) { // third finger
        if (ArmData.servo3 > 50) {
          ArmData.servo3 = ArmData.servo3 - 3;
        }
      }
      else if (analogRead(Finger4) > 900) { // fourth finger
        if (ArmData.servo4 > 100) {
          ArmData.servo4 = ArmData.servo4 - 3;
        }
      }
    }
    radio.write(&ArmData, sizeof(ArmData)); // send the ArmData
  } else if (getValue(ConnectedDevise, '-', 0) == "Car" && mode == "connected") {
    gyro();
    if (yAxis >= 45 && yAxis <= 90) {
      if (xAxis >= 45 && xAxis <= 90) {
        CarData.Motor1 = 0;
        CarData.Motor2 = 1;
      } else if (xAxis >= 250 && xAxis <= 330) {
        CarData.Motor1 = 1;
        CarData.Motor2 = 0;
      } else if (xAxis > 330 || xAxis < 45) {
        CarData.Motor1 = 1;
        CarData.Motor2 = 1;
      }
    }
    else if (yAxis >= 250 && yAxis <= 330) {
      if (xAxis >= 45 && xAxis <= 90) {
        CarData.Motor1 = 0;
        CarData.Motor2 = -1;
      } else if (xAxis >= 250 && xAxis <= 330) {
        CarData.Motor1 = -1;
        CarData.Motor2 = 0;
      } else if (xAxis > 330 || xAxis < 45) {
        CarData.Motor1 = -1;
        CarData.Motor2 = -1;
      }
    } else {
      if (xAxis >= 45 && xAxis <= 90) {
        CarData.Motor1 = 1;
        CarData.Motor2 = -1;
      } else if (xAxis >= 250 && xAxis <= 330) {
        CarData.Motor1 = -1;
        CarData.Motor2 = 1;
      } else {
        CarData.Motor1 = 0;
        CarData.Motor2 = 0;
      }

    }
    radio.write(&CarData, sizeof(CarData)); // send the CarData
  } else if (getValue(ConnectedDevise, '-', 0) == "Usb" && mode == "connected") {
    if (analogRead(Finger1) < 850 && analogRead(Finger2) > 850 && analogRead(Finger3) > 850 && analogRead(Finger4) > 900) {
      analogWrite(Laser, 1023);
    } else {
      analogWrite(Laser, 0);
      if (yAxis >= 45 && yAxis <= 90) {
        if (analogRead(Finger1) > 850) {
          UsbData.Move = 1;
        } else if (analogRead(Finger2) > 850) {
          UsbData.Move = -1;
        } else {
          UsbData.Move = 0;
        }
      }
      else {
        UsbData.Move = 0;
      }
    }
    radio.write(&UsbData, sizeof(UsbData));
  } else if (getValue(ConnectedDevise, '-', 0) == "Uni" && mode == "connected") {
    gyro();
    String Unity = "";
    if (analogRead(Finger1) > 850) {
      Unity += "1.";
    } else {
      Unity += "0.";
    }
    if (analogRead(Finger2) > 850) {
      Unity += "1.";
    } else {
      Unity += "0.";
    }
    if (analogRead(Finger3) > 850) {
      Unity += "1.";
    } else {
      Unity += "0.";
    }
    if (analogRead(Finger4) > 850) {
      Unity += "1.";
    } else {
      Unity += "0.";
    }
    Unity += String(xAxis) + "." + String(yAxis);
    radio.write(&Unity, sizeof(Unity));
  }
}


void u8g_prepare(void) {//prepere the display for write
  u8g.setFont(u8g_font_6x13);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void Print(int num, int pos) {//this function makes printing easier
  u8g_prepare();
  switch (num) {
    case 0: Psearch(pos); break;
    case 1: StartSearch(); break;
    case 2: EndSearch(pos); break;
    case 3: SearchAgain(); break;
    case 4: Connected(pos); break;
    case 5: RFID(); break;
  }
}

void Psearch(int x) {//searching gif
  u8g.setPrintPos(0, 0);
  u8g.print("Searching");
  if (x == 1 || x == 5 || x == 9 || x == 13) {
    u8g.print(".");
  } else if (x == 2 || x == 6 || x == 10 || x == 14) {
    u8g.print("..");
  } else if (x == 3 || x == 7 || x == 11 || x == 15) {
    u8g.print("...");
  }
  u8g.setPrintPos(0, 12);
  u8g.print("Please Wait (:");
}

void search() {
  u8g.firstPage();
  do {
    Print(0, int((millis() - searchtime * 1000) / 1000));
  } while ( u8g.nextPage() );
  radio.startListening();
  if (radio.available()) {
    int check = 0;
    char text[32] = "";
    radio.read(&text, sizeof(text));
    for (int i = 0 ; i <= devisenum; i++) {
      if (devises[i] == String(text)) {
        check++;
        break;
      }
    }
    if (check == 0) {
      devises[devisenum] = String(text);
      devisenum++;
    }
  }
}


void StartSearch() {//before search print
  u8g.setPrintPos(0, 0);
  u8g.print("Press OK button to");
  u8g.setPrintPos(0, 12);
  u8g.print("start searching for ");
  u8g.setPrintPos(0, 24);
  u8g.print("nearby devices");
}

void EndSearch(int x) {//select devise print
  u8g.setPrintPos(0, 0);
  u8g.print(devisenum);
  if (devisenum == 1) {
    u8g.print(" devise has been");
  } else {
    u8g.print(" devises has been");
  }
  u8g.setPrintPos(0, 12);
  u8g.print("found.");
  if (selectdev != 0) {
    u8g.setPrintPos(0, 24);
    u8g.print("*" + devises[x - 1]);
  }
  u8g.setPrintPos(0, 36);
  u8g.print(">" + devises[x]);
  if (selectdev != devisenum - 1) {
    u8g.setPrintPos(0, 48);
    u8g.print("*" + devises[x + 1]);
  }
}

void SearchAgain() {//0 devise found search
  u8g.setPrintPos(0, 0);
  u8g.print("No devise has been");
  u8g.setPrintPos(0, 12);
  u8g.print("found. Press OK ");
  u8g.setPrintPos(0, 24);
  u8g.print("button to start ");
  u8g.setPrintPos(0, 36);
  u8g.print("searching again for");
  u8g.setPrintPos(0, 48);
  u8g.print("nearby devises.");
}

void Connected(int x) {//connected print
  u8g.setPrintPos(0, 0);
  u8g.print("You are connected ");
  u8g.setPrintPos(0, 12);
  u8g.print("with: " + ConnectedDevise);
  if (x > 0) {
    u8g.setPrintPos(0, 24);
    u8g.print("*" + options[x - 1]);
  }
  u8g.setPrintPos(0, 36);
  u8g.print(">" + options[x]);
  if (x < 4) {
    u8g.setPrintPos(0, 48);
    u8g.print("*" + options[x + 1]);
  }
}

void RFID() {
  u8g.setPrintPos(0, 0);
  u8g.print("Touch the RFID");
  u8g.setPrintPos(0, 12);
  u8g.print("to your palm.");
}

void gyro() {//gyroscope function
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // start MPU6050 communication

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read(); // read

  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90); // calculate

  xAxis = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  yAxis = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  zAxis = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI); // convert
}

String getValue(String data, char separator, int index)
{ //split function
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void Delete() {
  for (int i = 0; i < devisenum; i++) {
    devises[i] = "";
  }
  devisenum = 0;
}

void WriteToEEPROM(int add, String data) {
  int strsize = data.length();
  for (int i = 0; i <= strsize; i++) {
    EEPROM.write(add + i, data[i]);
  }
}

String ReadEEPROM(int add, int len) {
  String result = "";
  for (int i = 1; i <= len; i++) {
    result.concat(char(EEPROM.read(add + i - 1)));
  }
  return result;
}
