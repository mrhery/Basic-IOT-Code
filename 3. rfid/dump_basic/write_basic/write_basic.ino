#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         0
#define SS_PIN          15

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

int block = 2;
byte blockcontent[16] = {"abcdefghijklmno"};
byte readbackblock[18];

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  Serial.println();
  Serial.println(F("Imbas Kad Anda"));

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println("Kad Dipilih");
  writeBlock(block, blockcontent);

  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  delay(3000);
}

int writeBlock(int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;
  if (blockNumber > 2 && (blockNumber+1)%4 == 0){
    Serial.print(blockNumber);
    Serial.println(" is a trailer block:");
    return 2;
  }
  Serial.print(blockNumber);
  Serial.println(" is a data block:");
  
  MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed: ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  
  MFRC522::StatusCode statusx = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);
  if (statusx != MFRC522::STATUS_OK) {
       Serial.print("MIFARE_Write() failed: ");
       Serial.println(mfrc522.GetStatusCodeName(statusx));
       return 4;//return "4" as error message
  }
  
  Serial.println("block was written");
}
