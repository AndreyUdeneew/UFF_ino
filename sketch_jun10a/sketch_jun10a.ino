int WL_NUM = 2;   //Number of Wavelengths (LED drivers connected), should not be higher than 7
int PWM_White = 20;
int PWM_UV = 20;
void setup()
{
  pinMode(2, INPUT); /// Our camera strobe in HIGH - Acquiring, LOW - not acquiring
  for(int i = 0; i < WL_NUM; i++)
    pinMode(3 + i ,OUTPUT); // LED control OUTPUTS (could be later moved to PWM or AM intensity control)
  pinMode(WL_NUM + 3, OUTPUT);  //Loop control; happens only once per cycle of all LEDs; for debug
  pinMode(13, OUTPUT); ///LAMP !
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
    digitalWrite(3 + c, LOW);
    //    analogWrite(3 + c, 0);
    lampc++;
    c++;
    if(c >= WL_NUM)
      c = 0;
    digitalWrite(3 + c, HIGH);
    //    analogWrite(3 + c, PWM_UV);
  }
 
  //Here Loop control signal
  if(CurState > PrevState && c == 0)
    digitalWrite(3 + WL_NUM, HIGH);
  if(CurState < PrevState && c ==0)
    digitalWrite(3 + WL_NUM, LOW);
 
  //Arduino onboard lamp flashing if frames are arriving; for debug purposes
  if(lampc > 20)
  {
      LampState = !LampState;  
      digitalWrite(13, LampState);
      lampc = 0;
  }

  PrevState = CurState;
}