int enA = 5;
int in1 = 2;
int in2 = 3;
int enB = 6;
int in3 = 7;
int in4 = 8;

int receiver_pins[] = {A0, A1, A2, A3, A4, A5};
int receiver_values[] = {0, 0, 0, 0, 0, 0};
int res_min = 1100;
int res_max = 1900;

int working_range = 255;// motor driver range

boolean prt = true;

int mode = 0;
//-1 - transmeter not connected or out of range
//0- trans connected and ready
//1 - low speed
//2 = high speed mode

void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB,  OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(115200);
  //Staring delay with LED
  setLED(1);
  delay(300);
  setLED(1);
  delay(300);
  setLED(2);
  delay(300);
  setLED(3);
  delay(300);
  setLED(0);


}

void loop() {
  receive();
  setModeLED();

  int m1 = 0;
  int m2 = 0;

  int rot = receiver_values[0];

  if (mode == 1) {
    m1 = receiver_values[1] / 2 + (rot );
    m2 = receiver_values[1] / 2 - (rot );

  } else if (mode == 2) {

    m1 = receiver_values[1] + rot / 2;
    m2 = receiver_values[1] - rot / 2
         ;
  }

  mpower(1,  m1);
  mpower(2,  m2);
}
int rp = 0;
void receive() {

  receiver_values[rp] = map(pulseIn (receiver_pins[rp], HIGH), res_min, res_max, -1 * working_range, working_range);
  rp++;
  if (rp == 6) {
    rp = 0;
  }
  boolean activevalues = true;
  for (int i = 0; i < 6; i++) {
    if (prt) {
      Serial.print("CH");
      Serial.print(i);
      Serial.print(" : ");
      Serial.print(receiver_values[i]);
      Serial.print(",\t");
      
    }
    if (receiver_values[i] < -500) {
      activevalues = false;
    }
  }
  mode = 0;
  if (!activevalues) {
    mode = -1;
    Serial.print("mode01");
  } else if (receiver_values[4] > -100) {
    mode = 2;
    Serial.print("mode02");
  } else if (receiver_values[5] > -100) {
    mode = 1;
    Serial.print("mode01");
  }
  if (prt) {
    Serial.println("");
  }

}

void setModeLED() {
  if (mode == -1) {
    setLED(-0);
  } else if (mode == 0) {
    setLED(1);
  } else if (mode == 1) {
    setLED(2);
  } else if (mode == 2) {
    setLED(3);
  }
}
void setLED(int led) {
  for (int i = 1; i < 4; i++) {
    if (led == i) {
      digitalWrite(10 + i, LOW);
    } else {
      digitalWrite(10 + i, HIGH);
    }
  }
}
void mpower(int motor,  int spd) {
  int rotation = 0;
  if (spd > 0) {
    rotation = 1;
  } else if (spd < 0) {
    rotation = -1;
    spd *= -1;
  }
  if (spd > 255) {
    spd = 255;
  }
  int pwm;
  int pA;
  int pB;
  if (motor == 1) {
    pwm = enA;
    pA = in1;
    pB = in2;
  } else if (motor == 2) {
    pwm = enB;
    pA = in3;
    pB = in4;
  } else {
    return;
  }

  if (rotation == 0) {
    digitalWrite(pA, LOW);
    digitalWrite(pB, LOW);
  } else if (rotation == 1) {
    digitalWrite(pA, HIGH);
    digitalWrite(pB, LOW);
  } else if (rotation == -1) {
    digitalWrite(pA, LOW);
    digitalWrite(pB, HIGH);
  }
  analogWrite(pwm, spd);

}
