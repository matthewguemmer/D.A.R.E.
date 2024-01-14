#define M1_1_PIN 3
#define M1_2_PIN 5

#define M2_1_PIN 6
#define M2_2_PIN 9

struct packet {
   float leftSpd;
   float rightSpd;
   char sw_1_state;
   char sw_2_state;
   char sw_3_state;
};



void setMotor1PWM(float p) {
  setMotorGenericPWM(p, M1_1_PIN, M1_2_PIN);
}

void setMotor2PWM(float p) {
  setMotorGenericPWM(p, M2_1_PIN, M2_2_PIN);
}

void setMotorGenericPWM(float p, int pin1, int pin2) {
  if (p > 1.0) {
    p = 1.0;
  } else if (p < -1.0) {
    p = -1.0;
  }

  if (p == 0.0) {
    analogWrite(pin1, 0);
    analogWrite(pin2, 0);
  }

  else if (p > 0) {
    analogWrite(pin1, p * 255.0);
    analogWrite(pin2, 0);
  } else {
    analogWrite(pin1, 0);
    analogWrite(pin2, -p * 255.0);
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(M1_1_PIN, OUTPUT);
  pinMode(M1_2_PIN, OUTPUT);
  pinMode(M2_1_PIN, OUTPUT);
  pinMode(M2_2_PIN, OUTPUT);

  setMotor1PWM(0);
  setMotor2PWM(0);

  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:
  struct packet packet;
  
  while (Serial.available() < sizeof(packet)) {
    // wait for a packet to be available
  }

  char *p = (char*)&packet;

  for (int i = 0; i < sizeof(packet); i ++ ) {
    p[i] = Serial.read();
  
  }

  setMotor1PWM(packet.leftSpd);
  setMotor2PWM(packet.rightSpd);

  if ((!!packet.sw_1_state) ^ (!!packet.sw_2_state) ^ (!!packet.sw_3_state)) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  // consume the reset of the Serial buffer
  while (Serial.available() > 0) {
    Serial.read();
  }

}
