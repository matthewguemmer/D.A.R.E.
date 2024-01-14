#define SW_1_PIN 4
#define SW_2_PIN 3
#define SW_3_PIN 2

#define VRX_PIN A6
#define VRY_PIN A5


struct packet {
   float leftSpd;
   float rightSpd;
   char sw_1_state;
   char sw_2_state;
   char sw_3_state;
};



void setup() {
  // put your setup code here, to run once:
  pinMode(SW_1_PIN, INPUT_PULLUP);
  pinMode(SW_2_PIN, INPUT_PULLUP);
  pinMode(SW_3_PIN, INPUT_PULLUP);


  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  bool sw_1_state = digitalRead(SW_1_PIN) == HIGH;
  bool sw_2_state = digitalRead(SW_2_PIN) == HIGH;
  bool sw_3_state = digitalRead(SW_3_PIN) == HIGH;

//  if (sw_1_state) {
//    Serial.print("1");
//  }
//  if (sw_2_state) {
//    Serial.print("2");
//  }
//  if (sw_3_state) {
//    Serial.print("3");
//  }
//  Serial.println("");

  int xValue = analogRead(VRX_PIN) - 506;
  int yValue = analogRead(VRY_PIN) - 496;

  float leftSpd = ((float)-yValue)/512;
  float rightSpd = ((float)-yValue)/512;

  leftSpd -= ((float)-xValue)/512;
  rightSpd += ((float)-xValue)/512;

  if (leftSpd > 1) {
    leftSpd = 1;
  } else if (leftSpd < -1) {
    leftSpd = -1;
  }
  if (rightSpd > 1) {
    rightSpd = 1;
  } else if (rightSpd < -1) {
    rightSpd = -1;
  }

  struct packet packet;
  packet.leftSpd = leftSpd;
  packet.rightSpd = rightSpd;
  packet.sw_1_state = sw_1_state;
  packet.sw_2_state = sw_2_state;
  packet.sw_3_state = sw_3_state;


  Serial.write((char*)&packet, sizeof(packet));

  delay(100);
  
}
