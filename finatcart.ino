#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN         9
#define SS_PIN          10
#define SERVO_PIN       6
#define BUZZER_PIN      7
#define BUTTON_PIN      8

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

String knownIDs[] = {"C3 CB 53", "93 4A 91"}; // Replace with your actual tag IDs
String productNames[] = {"Rice", "Cofee"}; // Corresponding product names
int productPrices[] = {60, 20}; // Corresponding product prices
int totalPrice = 0;
String lastScannedID = ""; // To track the last scanned product ID

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(SERVO_PIN);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Scan a product");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    if (digitalRead(BUTTON_PIN) == HIGH ) {
      delay(100); // Debounce delay
      if (digitalRead(BUTTON_PIN) == LOW) { // Check if button is still pressed
        for (int i = 0; i < sizeof(knownIDs) / sizeof(knownIDs[0]); i++) {
          if (lastScannedID == knownIDs[i]) {
            totalPrice -= productPrices[i];
            
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Removing ");
            lcd.print(productNames[i]);
            
            myServo.write(90);     // Open the trolley
            delay(2000);           // Keep it open for 2 seconds
            myServo.write(0);      // Close the trolley
            
            lastScannedID = "";    // Clear the last scanned ID
            
            delay(2000);  // Delay to display the removal message
            
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Total: Rs ");
            lcd.print(totalPrice);
            break;
          }
        }
      }
    }
    return;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  int productIndex = -1;
  for (int i = 0; i < sizeof(knownIDs) / sizeof(knownIDs[0]); i++) {
    if (content.indexOf(knownIDs[i]) > -1) {
      productIndex = i;
      break;
    }
  }

  if (productIndex != -1) {
    lastScannedID = knownIDs[productIndex];
    totalPrice += productPrices[productIndex];

    tone(BUZZER_PIN, 1000);  // Buzzer on
    delay(500);              // Keep the buzzer on for 500ms
    noTone(BUZZER_PIN);      // Buzzer off

    myServo.write(90);       // Open the trolley
    delay(5000);             // Keep it open for 2 seconds
    myServo.write(0);        // Close the trolley

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(productNames[productIndex]);
    lcd.setCursor(0, 1);
    lcd.print("Price: Rs ");
    lcd.print(productPrices[productIndex]);

    delay(2000);  // Delay to display the product details

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total: Rs ");
    lcd.print(totalPrice);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unknown product");
  }

  delay(1000);  // Delay for debounce
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan a product");
}