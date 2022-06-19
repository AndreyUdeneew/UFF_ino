int pinsNum = 6;
int PWMvals[pinsNum] = {}; // 0 - 255
int steps[pinsNum] = {0,1,2,3};// 0 = Dunkelheit, 1 - white, 2 - UV, 3 - RED
bool pinsPWM[pinsNum] = {true,true,true,true,true,true};
int pins[pinsNum] = {3,5,6,9,10,11};
int pimCombinations1[][]=
{{}
}};
int pimCombinations2[][]=
{{}
}};
int pimCombinations3[][]=
{{}
}};
int pimCombinations4[][]=
{{}
}};
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
int c = 0, lampc = 0;
int LampState = 0;
void loop()
{
  CurState = digitalRead(2);

  //Here we manage LEDS to work sequentially
  if(CurState < PrevState)
  {
//    digitalWrite(5 + c, LOW);
//        analogWrite(5 + c, 0);
          analogWrite(UV_LED, 0);

//    lampc++;
//    c++;
    if(c >= WL_NUM)
//      c = 0;
//    digitalWrite(5 + c, HIGH);
//        analogWrite(5 + c, PWM_UV);
          analogWrite(UV_LED, PWM_UV);
  }
 
  //Here Loop control signal
  if(CurState > PrevState && c == 0)
    digitalWrite(5 + WL_NUM, HIGH);
  if(CurState < PrevState && c ==0)
    digitalWrite(5 + WL_NUM, LOW);
 
  //Arduino onboard lamp flashing if frames are arriving; for debug purposes
  if(lampc > 20)
  {
      LampState = !LampState;  
      digitalWrite(13, LampState);
      lampc = 0;
  }

  PrevState = CurState;
}
