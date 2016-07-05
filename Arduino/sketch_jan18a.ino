int inputRef = A0;
int inputPin = A1;
int V0 = 0;
int V1 = 0;
int Vdiff = 0.0;
boolean check = false;
int sum = 0;
int bitPos = 0;
int bitValue = 0;
int blinkDelay =40;
float vOCmin = 30.0;
int Vthresh = 25;
int time=0;
int denom=0;
float Vdiff_sum=0.0;

void setup()
{
  pinMode(inputPin, INPUT);
  pinMode(inputRef,INPUT);
  Serial.begin(9600);
  
  V0 = analogRead(A0);
  V1 = analogRead(A1);
  delay(2000); 
}

void loop()
{
  
  if (!check)
  {
    V0 = analogRead(A0);
    V1 = analogRead(A1);
    
    Vdiff = abs(V1 - V0);
    if (Vdiff > Vthresh)
    {
      check = true;
      time=millis();
    }
     
}
  
  if (check)
  {
    if( ( (millis()-time) > (blinkDelay * (bitPos + 1) ) - 3*blinkDelay/4) && ((millis()-time) < (blinkDelay * (bitPos + 1) ) - 1*blinkDelay/4) )
    {
      V0 = analogRead(A0);
      V1 = analogRead(A1);
      Vdiff = abs(V1 - V0) ;
      denom++;
      Vdiff_sum = Vdiff_sum + Vdiff;
    }
    
    if( ( (millis()-time) >= (blinkDelay * (bitPos + 1) )-1*blinkDelay/4 ) && ( (millis()-time) <= (blinkDelay * (bitPos + 1) ) ) )
    {
      
      
      if( (Vdiff_sum/denom) > vOCmin)
      {
        bitValue = 1;
      }
      else
      {
        bitValue = 0;
      }
      
      Serial.print(denom);
      Serial.print("\t");
      Serial.print(Vdiff_sum);
      Serial.print("\t");
      Serial.print(bitPos);
      Serial.print("\t");
      Serial.print(Vdiff_sum/denom);
      Serial.print("\t");
      
      denom=0;
      Vdiff_sum=0.0;
      
      if(bitPos%4==0)
        sum += bitValue*1;
      if(bitPos%4==1)
        sum += bitValue*2;
      if(bitPos%4==2)
        sum += bitValue*4;
      if(bitPos%4==3)
        sum += bitValue*8;
    
      Serial.print(bitValue);
      Serial.print("\t");
      Serial.print(sum);
      Serial.print("\t");
      Serial.print((millis()-time)%blinkDelay);;
      Serial.print("\n");
      
      bitPos++;
   
      if (bitPos%4 ==0)
      {
        if (sum == 0)
        {
          check = false;
          bitPos=0;
        }
        else
        {
          
          Serial.print("\t");
          Serial.print("\t");
          Serial.print("\t");
          Serial.print("\t");
          Serial.print("\t");
          Serial.print("\t");
          Serial.print("\t");
          
          if(sum!=15)
          Serial.print((sum - 2));
          Serial.print("\n");
          sum = 0;
        }
      }
    }
  }
}
