void setup() {
  Serial.begin(115200);


  pinMode(A1, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  
  analogWrite(A1, 1023);

  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);


}

boolean flag = true;
int count = 15;
int interval = 10;

int pinA = 0;
int pinB = 0;

int pinVal[6][4];

int score[2];
int sub_score = 0;

void loop() {

  if(flag){
    Serial.println("");

    transistorDetect("positive");
    transistorDetect("negative");
    Serial.println("=================================");


    
  }

   //repeater();


}







void repeater(){

}










void transistorDetect(String mode){

  if(mode == "positive"){
  

    Serial.println("===== POSITIVE TEST (NPN) =====");
    Serial.println("");

    for(int i = 0; i < count; i++){

      pinA = analogRead(A2);
      pinB = analogRead(A3);

    
      Serial.print(" + | ");
      Serial.print(pinA);
      Serial.print(" | ");
      Serial.println(pinB);
/*    
      delay(interval);
*/
      pinVal[0][0] = pinVal[0][0] + pinA;
      pinVal[0][1] = pinVal[0][1] + pinB;
      

    }

    Serial.println("");

  
    pinMode(A1, INPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, INPUT);
    
    analogWrite(A2, 1023);

    for(int i = 0; i < count; i++){

      pinA = analogRead(A1);
      pinB = analogRead(A3);

      
      Serial.print(" ");
      Serial.print(pinA);
      Serial.print(" | + | ");
      Serial.println(pinB);
/*      
      delay(interval);
      
*/

      pinVal[1][0] = pinVal[1][0] + pinA;
      pinVal[1][1] = pinVal[1][1] + pinB;
     
  
      
    }

    Serial.println("");
 
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, OUTPUT);
  
    analogWrite(A3, 1023);
  
    for(int i = 0; i < count; i++){

      pinA = analogRead(A1);
      pinB = analogRead(A2);
     
      Serial.print(" ");
      Serial.print(pinA);
      Serial.print(" | ");
      Serial.print(pinB);
      Serial.println(" | +");
 /*  
      delay(interval);
*/

      pinVal[2][0] = pinVal[2][0] + pinA;
      pinVal[2][1] = pinVal[2][1] + pinB;
     
  
      
    }
  
    Serial.println("");
 
    pinMode(A1, OUTPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
  
    analogWrite(A1, 1023);
  

  }else if(mode == "negative"){


    Serial.println("===== NEGATIVE TEST (PNP) =====");
    Serial.println("");

    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);

    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);

//=====================================


    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, OUTPUT);

    analogWrite(A3, 0);
     
    for(int i = 0; i < count; i++){


      pinA = analogRead(A1);
      pinB = analogRead(A2);
  
      
      Serial.print(" ");
      Serial.print(1023 - pinA);
      Serial.print(" | ");
      Serial.print(1023 - pinB);
      Serial.println(" | -");
/*
      delay(interval);
*/

      pinVal[3][0] = pinVal[3][0] + (1023 - pinA);
      pinVal[3][1] = pinVal[3][1] + (1023 - pinB);
     
      
    }
  
    Serial.println("");

//=====================================

    pinMode(A1, INPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, INPUT);
    
    analogWrite(A2, 0);
  
    for(int i = 0; i < count; i++){


      pinA = analogRead(A1);
      pinB = analogRead(A3);
  
      
      Serial.print(" ");
      Serial.print(1023 - pinA);
      Serial.print(" | - | ");
      Serial.println(1023 - pinB);
/*  
      delay(interval);
*/

      pinVal[4][0] = pinVal[4][0] + (1023 - pinA);
      pinVal[4][1] = pinVal[4][1] + (1023 - pinB);
     
      
    }
  
    Serial.println("");


//=====================================

 
    pinMode(A1, OUTPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    
    analogWrite(A1, 0);



    for(int i = 0; i < count; i++){


      pinA = analogRead(A2);
      pinB = analogRead(A3);
  
    
      Serial.print(" - | ");
      Serial.print(1023 - pinA);
      Serial.print(" | ");
      Serial.println(1023 - pinB);
/*
      delay(interval);
*/

      pinVal[5][0] = pinVal[5][0] + (1023 - pinA);
      pinVal[5][1] = pinVal[5][1] + (1023 - pinB);
     
      
    }
  
    Serial.println("");
    Serial.println("=================================");

    checkType();

  
    pinMode(A1, OUTPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
  
    analogWrite(A1, 0);
  

    
  }
  
  flag = false;

  
}

void checkType(){

    score[0] = 0;
    score[1] = 0;

    Serial.println("Transistor info:");
    Serial.println("");


    for(int a = 0; a < 6; a++){
      for(int b = 0; b < 2; b++){

        if(pinVal[a][b] > 1500){
          if(a < 3){
            score[0]++;
          }else{
            score[1]++;
          }
        }
      
      }
    }
    
    if((score[0] + score[1]) == 6){
      if((score[0] == 2) && (score[1] == 4)){
        Serial.println("  Type: NPN");
        CheckPinouts(0);
      }else if((score[0] == 4) && (score[1] == 2)){
        Serial.println("  Type: PNP");
        CheckPinouts(1);
      }else{
        Serial.println("  Unknown Transistor!");
      }
    }else{
      Serial.println("  Bad Transistor!");
    }

}

void CheckPinouts(int tType){

  int pins;
  
  if(tType == 0){

    if((pinVal[0][0] + pinVal[0][1]) > 400){
      if(pinVal[0][0] > pinVal[0][1]){
        pins = 0;
      }else{
        pins = 1;
      }
    }else if((pinVal[1][0] + pinVal[1][1]) > 400){
      if(pinVal[1][0] > pinVal[1][1]){
        pins = 2;
      }else{
        pins = 3;
      }
    }else if((pinVal[2][0] + pinVal[2][1]) > 400){
      if(pinVal[2][0] > pinVal[2][1]){
        pins = 4;
      }else{
        pins = 5;

      }
    }else{
      Serial.println("  Uncnown");
    }

    
  }else if(tType == 1){


    if((pinVal[3][0] + pinVal[3][1]) > 400){
      if(pinVal[3][0] > pinVal[3][1]){
        pins = 4;
      }else{
        pins = 5;
      }
    }else if((pinVal[4][0] + pinVal[4][1]) > 400){
      if(pinVal[4][0] > pinVal[4][1]){
        pins = 2;
      }else{
        pins = 3;
      }
    }else if((pinVal[5][0] + pinVal[5][1]) > 400){
      Serial.println("  Pin 1 - Base");
      if(pinVal[5][0] > pinVal[5][1]){
        pins = 0;
      }else{
        pins = 1;
      }
    }else{
      Serial.println("Uncnown");
    }

  }

  if(pins == 0){
      Serial.println("  Pin 1 - Base (100%)");
      Serial.println("  Pin 2 - Collector");
      Serial.println("  Pin 3 - Emitter");
  }else if(pins == 1){
      Serial.println("  Pin 1 - Base (100%)");
      Serial.println("  Pin 2 - Emitter");
      Serial.println("  Pin 3 - Collector");
  }else if(pins == 2){
      Serial.println("  Pin 1 - Collector");
      Serial.println("  Pin 2 - Base (100%)");
      Serial.println("  Pin 3 - Emitter");
  }else if(pins == 3){
      Serial.println("  Pin 1 - Emitter");
      Serial.println("  Pin 2 - Base (100%)");
      Serial.println("  Pin 3 - Collector");
  }else if(pins == 4){
      Serial.println("  Pin 1 - Collector");
      Serial.println("  Pin 2 - Emitter");
      Serial.println("  Pin 3 - Base (100%)");
  }else if(pins == 5){
      Serial.println("  Pin 1 - Emitter");
      Serial.println("  Pin 2 - Collector");
      Serial.println("  Pin 3 - Base (100%)");
  }

  //details();
  Serial.println("");

}
/*
void details(){

 
  Serial.println("");
  Serial.println("Details (Positive):");
  Serial.println("");

  Serial.print("  [ + ] [ ");
  Serial.print(pinVal[0][0]);
  Serial.print(" ] [ ");
  Serial.print(pinVal[0][1]);
  Serial.println(" ]");

  Serial.print("  [ ");
  Serial.print(pinVal[1][0]);
  Serial.print(" ] [ + ] [ ");
  Serial.print(pinVal[1][1]);
  Serial.println(" ]");

  Serial.print("  [ ");
  Serial.print(pinVal[2][0]);
  Serial.print(" ] [ ");
  Serial.print(pinVal[2][1]);
  Serial.println(" ] [ + ]");
  
  Serial.println("");
  Serial.println("Details (Negative):");
  Serial.println("");

  Serial.print("  [ ");
  Serial.print(pinVal[3][0]);
  Serial.print(" ] [ ");
  Serial.print(pinVal[3][1]);
  Serial.println(" ] [ - ]");
  
  Serial.print("  [ ");
  Serial.print(pinVal[4][0]);
  Serial.print(" ] [ + ] [ ");
  Serial.print(pinVal[4][1]);
  Serial.println(" ]");

  Serial.print("  [ + ] [ ");
  Serial.print(pinVal[5][0]);
  Serial.print(" ] [ ");
  Serial.print(pinVal[5][1]);
  Serial.println(" ]");

}
*/
