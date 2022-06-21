#define pinsNum 3
#define stepsNum 3

int WL_NUM = 2;   //Number of Wavelengths (LED drivers connected), should not be higher than 7
int PWM_White = 20;
int PWM_UV = 250;
int UV_LED = 5;
int WHITE_LED = 6;
int PWMvals[pinsNum] = {0, 5, 250}; // 0 - 255
int steps[pinsNum] = {0, 1, 2}; // 0 = Dunkelheit, 1 - white, 2 - UV, 3 - RED
bool pinsPWM[pinsNum] = {true, true, true}; // pins with PWM are 3,5,6,9,10,11
int pins[pinsNum] = {3, 5, 6};
int pinsCombinations0[stepsNum][pinsNum] =
{
  {1, 0},
  {1, 1}
};
int pinsCombinations1[stepsNum][pinsNum] =
{
  {0, 0, 0},
  {0, 1, 1},
  {0, 0, 1}
};
int pinsCombinations2[stepsNum][pinsNum] =
{
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1}
};
int pinsCombinations3[stepsNum][pinsNum] =
{
  {0, 0, 0},
  {0, 1, 0},
  {0, 0, 1}
};

void setup()
{
  pinMode(2, INPUT); /// Our camera strobe in HIGH - Acquiring, LOW - not acquiring
  pinMode(UV_LED, OUTPUT);// UV LED
  pinMode(WHITE_LED, OUTPUT);// White LED
  //  for(int i = 0; i < WL_NUM; i++)
  //    pinMode(5 + i ,OUTPUT); // LED control OUTPUTS (could be later moved to PWM or AM intensity control)
  //  pinMode(WL_NUM + 5, OUTPUT);  //Loop control; happens only once per cycle of all LEDs; for debug
  pinMode(13, OUTPUT); ///LAMP !
  analogWrite(WHITE_LED, PWM_White);
}

int CurState = 0;
int PrevState = 0;
int curStep = 0, lampc = 0;
int LampState = 0;
void loop()
{
  CurState = digitalRead(2);

  //Here we manage LEDS to work sequentially
  if (CurState < PrevState)
  {
    //    digitalWrite(5 + curStep, LOW);
    //        analogWrite(5 + curStep, 0);
    //          analogWrite(UV_LED, 0);

    lampc++;
    curStep++;
    if (curStep >= WL_NUM)
      curStep = 0;
    //    digitalWrite(5 + curStep, HIGH);
    //        analogWrite(5 + curStep, PWM_UV);
    //          analogWrite(UV_LED, PWM_UV);

    for (uint8_t LED = 0; LED < pinsNum; LED += 1)
    {
      analogWrite(pins[LED], (PWMvals[LED])*pinsCombinations1[curStep][LED]);
    }
  }

  //Here Loop control signal
  if (CurState > PrevState && curStep == 0)
    digitalWrite(5 + WL_NUM, HIGH);
  if (CurState < PrevState && curStep == 0)
    digitalWrite(5 + WL_NUM, LOW);

  //Arduino onboard lamp flashing if frames are arriving; for debug purposes
  if (lampc > 20)
  {
    LampState = !LampState;
    digitalWrite(13, LampState);
    lampc = 0;
  }

  PrevState = CurState;
}
