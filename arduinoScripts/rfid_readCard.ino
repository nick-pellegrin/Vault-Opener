#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5           // Configurable
#define SS_PIN          10          // Configurable
#define INDICATOR_PIN   7           // Configurable

String ALLOWED_KEYS[2] = {"99684732", ""};

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

//*****************************************************************************************//
void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
  pinMode(INDICATOR_PIN, OUTPUT);
}

//*****************************************************************************************//
void loop() {

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  String cardUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardUid += (mfrc522.uid.uidByte[i]);
  } 
  Serial.print(cardUid);
  for (auto i : ALLOWED_KEYS){
    if (i == cardUid)
      digitalWrite(INDICATOR_PIN, HIGH);
      delay(1000);
      digitalWrite(INDICATOR_PIN, LOW);
      break;
    }

  Serial.println(F("\n**End Reading**\n"));

  delay(1000); //change value if you want to read cards faster

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
//*****************************************************************************************//
