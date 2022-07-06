String cmd, CMDcur;
int programNumber;
int lamp = 13;
volatile int counter = 0;
volatile int lampCounter = 0;
int PWM_White = 250;
int PWM_UV = 250;
int UV_LED = 5;
int WHITE_LED = 6;

void setup()
{
//  pinMode(2, INPUT_PULLUP); /// Our camera strobe in HIGH - Acquiring, LOW - not acquiring
  pinMode(UV_LED, OUTPUT);// UV LED
  pinMode(2,INPUT_PULLUP);
  pinMode(WHITE_LED, OUTPUT);// White LED
  pinMode(13, OUTPUT); ///LAMP !
  analogWrite(WHITE_LED, PWM_White);
  Serial.begin(115200);
  Serial.setTimeout(100);
  attachInterrupt(0, Strob_Input_Handler, FALLING);
//  while (!Serial) {
//    ;
//  }
}


void Strob_Input_Handler() { 
  if (counter == 2) {
    counter = 0;
    }
     if (counter == 1) {
    analogWrite(UV_LED, PWM_UV);
  }
  else {
    analogWrite(UV_LED, 0);
  }
  counter++;  // + синхр.
  lampCounter += 1;
  
}
void waiting_4_command() {
  int PWM_VAL, PWM_VALH, PWM_VALL;
  cmd = "";
  if (Serial.available()) {
    cmd = Serial.readString();
    cmd.trim();
  }


  if (cmd.substring(0, 2) == "UV") {
    PWM_VALH = cmd[2] - '0';
    PWM_VALL = cmd[3] - '0';
    if (cmd[3] != '\0') {
      PWM_VAL = (PWM_VALH * 10) + (PWM_VALL * 1);
    }
    else {
      PWM_VAL = (PWM_VALH * 1) + (PWM_VALL * 0);
    }
    PWM_UV = PWM_VAL;
  }

  if (cmd.substring(0, 2) == "WH") {
    PWM_VALH = cmd[2] - '0';
    PWM_VALL = cmd[3] - '0';
    if (cmd[3] != '\0') {
      PWM_VAL = (PWM_VALH * 10) + (PWM_VALL * 1);
    }
    else {
      PWM_VAL = (PWM_VALH * 1) + (PWM_VALL * 0);
    }
    PWM_White = PWM_VAL;
    analogWrite(WHITE_LED, PWM_White);
  }
}

void loop()
{
  waiting_4_command();
  if (lampCounter == 10)
  {
    digitalWrite(lamp, HIGH);
  }
}
