#include <ezButton.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,-1);
ezButton button1(13);
ezButton button2(33);
ezButton button3(14);
ezButton button4(27);
ezButton button5(26);

int vote1=0, vote2=0, vote3=0, vote4=0;
int flag=0;
int voting_completed=0;

void setup() {
  Serial.begin(9600);
  button1.setDebounceTime(25);
  button2.setDebounceTime(25);
  button3.setDebounceTime(25);
  button4.setDebounceTime(25);
  button5.setDebounceTime(25);
  if(!oled.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println(F("Alocation Failed"));
    for(;;);
  };
  delay(2000);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.clearDisplay();
  oled.setCursor(2,5);
  oled.println("Start Voting");
  oled.setCursor(2,15);
  oled.println("A - Green");
  oled.setCursor(2,25);
  oled.println("B - Yellow");
  oled.setCursor(2,35);
  oled.println("C - Red");
  oled.setCursor(2,45);
  oled.println("D - Blue");
  oled.display();
  Serial.println("Result Will Be Shown After the Grey Button is Being Pressed");
}

void loop() {
  button1.loop();
  button2.loop();
  button3.loop();
  button4.loop();
  button5.loop();

  if(voting_completed==0){
    if(button1.isPressed()){
      vote1++;
    }
    else if(button2.isPressed()){
      vote2++;
    }
    else if(button3.isPressed()){
      vote3++;
    }
    else if(button4.isPressed()){
      vote4++;
    }
    else if(button5.isPressed()){
      voting_completed=1;
      vote_count();
      delay(3000);
      Serial.println("Working Completed");
    }
  }
  else{
    determine_winner();
  }

  
  delay(50);
}

void vote_count(){
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);

  oled.setCursor(1,0);
  oled.print("A B C D");
  oled.setCursor(1,20);
  oled.print(vote1);
  oled.setCursor(35,20);
  oled.print(vote2);
  oled.setCursor(65,20);
  oled.print(vote3);
  oled.setCursor(100,20);
  oled.print(vote4);
  oled.display();

}

void determine_winner(){
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);

  oled.setCursor(1,10);

  if((vote1>vote2 && vote1>vote3 && vote1>vote4))
    oled.print("A is the Winner");
  else if((vote2>vote1 && vote2>vote3 && vote2>vote4))
    oled.print("B is the Winner");
  else if((vote3>vote1 && vote3>vote2 && vote3>vote4))
    oled.print("C is the Winner");
  else if((vote4>vote1 && vote4>vote2 && vote4>vote3))
    oled.print("D is the Winner");
  else
    oled.print("There was a Tie, start vote again");
  oled.display();
}
