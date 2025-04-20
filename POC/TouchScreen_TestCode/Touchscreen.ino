int LED = 13;                                

void setup() {
  Serial.begin(9600);                               
  pinMode(LED,OUTPUT);                      

}

void loop() {
  if(Serial.available()>0)                  
  {
    String Received = Serial.readString();  
    if(int(Received[0]) == 1)              
    {
      digitalWrite(LED,HIGH);               
    if(int(Received[0]) == 0)              
    {
      digitalWrite(LED,LOW);                
    }
  }

}
