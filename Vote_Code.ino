
/* 

Code completed on 12-10-2023 20:17 pm IST.

You are free to use the code anyhow you want, but please try to keep this comment attached. It means a lot to me.

  _____  _____ _______ _    _ _____ _   _ 
 |  __ \|_   _|__   __| |  | |_   _| \ | |
 | |__) | | |    | |  | |__| | | | |  \| |
 |  _  /  | |    | |  |  __  | | | | . ` |
 | | \ \ _| |_   | |  | |  | |_| |_| |\  |
 |_|  \_\_____|  |_|  |_|  |_|_____|_| \_|

Support me 

Github - https://github.com/RithinM69

*/

#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int n = 1;

void getFingerprintID();

#define S1 7
#define S2 6
#define S3 5

#define S4 4
#define S5 8

int vote1=0;
int vote2=0;
int vote3=0;
int total_vote=0;
void setup()
{
  pinMode(S1,INPUT_PULLUP);
  pinMode(S2,INPUT_PULLUP);
  pinMode(S3,INPUT_PULLUP);
  pinMode(S4,INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("");
  Serial.println("");
  Serial.println("--- Electronic Voting Machine ---");
  Serial.println("");
  Serial.println("Candidates");
  Serial.println("----------");
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  digitalWrite(S4, HIGH);
  digitalWrite(S5, HIGH);


  Serial.println("A");
  Serial.println("B");
  Serial.println("C");

  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }


  finger.getTemplateCount();

    if (finger.templateCount == 0) {
    Serial.println("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  } 
  else {
    Serial.println("Waiting for valid finger...");
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}


void result(){
  total_vote=vote1+vote2+vote3;
  if(total_vote){
    if((vote1 > vote2 && vote1 > vote3)){
      Serial.println("A is the winner");
      delay(3000);
    }
    else if((vote2 > vote1 && vote2 > vote3)){
      Serial.println("B is the winner");
      delay(3000);
    }
    else if((vote3 > vote1 && vote3 > vote2)){
      Serial.println("C is the winner");
      delay(3000);
    }
    else{
      Serial.print(" Tie Up Or ");
      Serial.println(" No Result ");
      delay(1000);
    }
  }
  else{
    Serial.println("No Voting....");
    delay(1000);
  }

  Serial.print("A - ");
  Serial.println(vote1);
  Serial.print("B - ");
  Serial.println(vote2);
  Serial.print("C - ");
  Serial.println(vote3);
  vote1=0;vote2=0;vote3=0;total_vote=0;
  return 0;
}




void voting()
{ 
  
  while(true)
  {
    if(n<2){
      Serial.println("Please Vote");
      n++;
    }
    if(digitalRead(S1)==0){
      vote1++;
      Serial.println("Voted");
      delay(1000);
      getFingerprintID();
    }
  
    if(digitalRead(S2)==0){
      vote2++;
      Serial.println("Voted");
      delay(1000);
      getFingerprintID();
    }

    if(digitalRead(S3)==0){
      vote3++;
      Serial.println("Voted");
      delay(1000);
      getFingerprintID();
    }
    if(digitalRead(S4)==0){
      result();
    }
  }
}
 


void getFingerprintID() {
  n=1;
  uint8_t p = finger.getImage();
  if(p == FINGERPRINT_OK){
    Serial.println("Image taken");
    p = finger.image2Tz();
    if(p == FINGERPRINT_OK){
      Serial.println("Image converted");
      p = finger.fingerFastSearch();
      if (p == FINGERPRINT_OK) {
        Serial.println("Found a print match!");
        voting();
      } 
      else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Communication error 1");
      } 
      else if (p == FINGERPRINT_NOTFOUND) {
        Serial.println("Did not find a match");
        delay(1000);
        getFingerprintID();
      }
    }

  }
  else if(p == FINGERPRINT_NOFINGER)
  {
    Serial.println("No finger detected");
    Serial.println("Try Again");
    delay(1000);
    getFingerprintID();
  
  }

  }




void monitor(){
  getFingerprintID();
  
}

void loop()
{
  monitor();
}
