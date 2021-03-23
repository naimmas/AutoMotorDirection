#define motorO A1
#define motorO1 A2
#define ctrl A0
#define Ml 5
#define Mr 6
#define ps 4
void setup(){
  Serial.begin(9600);
  pinMode(motorO1, INPUT);pinMode(motorO, INPUT);pinMode(ps,INPUT);pinMode(ctrl,INPUT);
  pinMode(Ml, OUTPUT);pinMode(Mr, OUTPUT);}
  
float dly = 2500 ;bool act = true;bool psCh = true;int MotorDir = Ml;int sens = 100;

void loop() {

  if(analogRead(motorO)>=sens && digitalRead(ps)){ Serial.println(analogRead(motorO)); runMotor(MotorDir == Ml ? Ml : Mr);}
  
  if(analogRead(motorO1)>=sens && digitalRead(ps)){ Serial.println(analogRead(motorO)); runMotor(MotorDir == Ml ? Mr : Ml);}
  
  if (!digitalRead(ps) && psCh) {Serial.println("Your power supply is off");psCh = false;}

  else if (digitalRead(ps) && !psCh) {Serial.println("Your power supply is on");psCh = true;act = true;}
  
  if(act && digitalRead(ps)){ Serial.println("Waiting for action..."); act = false;}
  
  if(readRes()>=500 && readRes()<= 550){ dly+=250; Serial.print("Current turning duration => "); Serial.print(dly/1000); Serial.println("s");delay(500);}
  
  if (dly>=1000 && (readRes()>=800 && readRes()<= 850)){ dly-=250; if(dly<1000){ Serial.println("Minimum allowed turning time 1s"); dly = 1000;} Serial.print("Current turning duration => "); Serial.print(dly/1000); Serial.println("s");delay(500);}
  
  if(readRes()>=2000 && readRes()<= 2100){ MotorDir = Ml; Serial.println("Motor Turning Direction => Same");delay(500);}
  
  if (readRes()>=3200 && readRes()<= 3300){ MotorDir = Mr; Serial.println("Motor Turning Direction => Reverse");delay(500);}

  if (sens >= 50 && (readRes()>=9500 && readRes()<= 10050)){ sens -= 25; if(sens < 50) {Serial.println("Minimum allowed sensitivity 50");sens = 50;} Serial.print("sensitivity => ");Serial.println(sens);delay(500);}
  
  if (readRes()>=5300 && readRes()<= 5400){ sens += 25; Serial.print("Sensitivity => ");Serial.println(sens);delay(500);}
  
  if(readRes()>=450 && readRes()<= 500){ Serial.println("Resetting settings... \tturning duration = 2.5s\tTurning direction = Same\tMotor sensitivity = 100"); dly = 2500;MotorDir = Ml;sens = 100;delay(1000);}
}
void runMotor(int direct)
{
    Serial.println("Motor ON...");
    digitalWrite(direct, HIGH);delay(dly);digitalWrite(direct, LOW);
    Serial.println("Motor OFF...");delay(500);
    act = true;
}

int readRes()
{
  int Ref = 10000, Vin = 5;
  if(analogRead(ctrl))
    return  Ref * ((Vin/((analogRead(ctrl) * Vin)/1024.0)) -1);
  else
    return 0;
}
