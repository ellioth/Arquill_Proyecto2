char serialData;
int pin=11;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0){
    serialData = Serial.read();
    Serial.print(serialData);
   
   
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    //set hour
    if(serialData == '3'){
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      Serial.write("3",1);
    }
    //set alarm
    else if(serialData == '2') {
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      Serial.write("2",1);
    }
    //select 7 segment
    else if(serialData == '1') {
      digitalWrite(11, HIGH);
      Serial.write("1",1);
    }
    //up clock
    else if(serialData == '0') {
      digitalWrite(10, HIGH);
      Serial.write("0",1);
    }
    //set clock
    else if(serialData == '9') {
      digitalWrite(9, HIGH);
      Serial.write("9",1);
    }
    
  }

}
