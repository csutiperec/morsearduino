#define msgreader A0 //this is the Arduino pin for the light sensor
#define msgled 9 // this is the Arduino pin for the led that we transfer our message with
#define laser 8 //this is the Arduino pin for the led that lights up when we press the button
#define debugled 2 //this is the Arduino pin for the led that lights up when there is some kind of error
#define bttnpin 7 //this is the Arduino pin for the button
#define potmeterPin A1 //this is the Arduino pin for the potmeter
#define in1  6 //these are the Arduino pins that we use to activate coils 1-4 of the stepper motor
#define in2  5 //*
#define in3  4 //*
#define in4  3 //*********************************************************************************


#define delaytime 1   //delay time in ms to control the stepper motor delaytime.
#define lightenviromentstrength 800 //the  strength of light in the enviroment the  device is used in

int currentMode; //can be: writemessage (1), readmessage (2)
                   

void setup() {
  pinMode(msgreader, INPUT);
  pinMode(msgled, OUTPUT);
  pinMode(laser, OUTPUT);
  pinMode(debugled, OUTPUT);
  pinMode(bttnpin, INPUT);
  pinMode(potmeterPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT);

  digitalWrite(msgled, HIGH);
  digitalWrite(laser, LOW);
  digitalWrite(debugled, LOW);
  currentMode = 1;

  Serial.begin(9600);
}

void loop(){
  checkMode();
  switch(currentMode){
    case 1:
      if(Serial.available()>0){
        displayMsg(Serial.readString());        
      }
    break;
    case 2:
      String msg = encodeMessage();
      if(msg.indexOf("b")>=0)
        Serial.println(msg);
    break;
  }
}

void checkMode(){
  if(analogRead(potmeterPin)>=512){
    currentMode=2;
  }
  else if(analogRead(potmeterPin)<=512){
    currentMode=1;
  }
}

void displayMsg(String message){
  digitalWrite(debugled, LOW);
  message.toLowerCase();
  if(message.indexOf("hello")>=0)
  {
    wave(120);
    wave(120);
  }
  message = decodeMessage(message);
  for(int i= 0; i<=message.length(); i++){
    checkMode();
    if(currentMode==2)
      break;
    switch(message.charAt(i)){
      case 's':
        shortBoop();
        break;
      case 'l':
        longBoop();
        break;
      case 'b':
        delay(2000);
        break;
      case 'e':
        if(i>=message.length()-1){
          digitalWrite(debugled, HIGH);
          delay(100);
          digitalWrite(debugled, LOW);
        }
        break;
    }
    
    if(message.charAt(i)=='e'){
      break;
    }
  }
}

void checkBtn()
{
  if (digitalRead(bttnpin) == LOW)
    digitalWrite(laser, LOW);
  if (digitalRead(bttnpin) == HIGH)
    digitalWrite(laser, HIGH);      
}

String encodeMessage(){
  String encodeMsg = "";
  while (currentMode == 2){
    while (encodeMsg.charAt(encodeMsg.length() - 1) != 'b'){
      checkBtn();
      if (analogRead(msgreader) > 800){
        checkBtn();
        int startTime = millis();
        int stopTime = startTime;
        while (analogRead(msgreader) > 800){
          checkBtn();
          stopTime = millis();
        }
        if (abs(stopTime - startTime) < 1000)
          encodeMsg += "s";
        else if (abs(stopTime - startTime) > 1000)
          encodeMsg += "l";
        int emptyTime = millis();
        int secondEmptyTime = emptyTime;
        while (analogRead(msgreader) < 800){
          checkBtn();
          secondEmptyTime = millis();
          if (abs(secondEmptyTime - emptyTime > 3000)){
            encodeMsg += "b";
            break;
          }
        }
      }
      checkMode();
      if(currentMode == 1)
        break;
      delay(200);
    }
    return encodeMsg;
    checkMode(); 
  }
}

//creates a decoded message, where s stands for short, l stands for long, b stands for the end of a character and e stands for an error
String decodeMessage(String message){
  String decodedMsg = "";
  for(int i= 0; i<=message.length(); i++){
    decodedMsg = decodedMsg+getCharacterMorse(message.charAt(i));
  }
  return decodedMsg;
}

//returns a chain of characters, where s stands for short, l stands for long, b stands for the end of a character and e stands for an error
String getCharacterMorse(char character){
  if(character == 'a'){
    return "slb";
  }
  if(character == 'b'){
    return "lsssb";
  }
  if(character == 'c'){
    return "lslsb";
  }
  if(character == 'd'){
    return "lssb";
  }
  if(character == 'e'){
    return "sb";
  }
  if(character == 'f'){
    return "sslsb";
  }
  if(character == 'g'){
    return "llsb";
  }
  if(character == 'h'){
    return "ssssb";
  }
  if(character == 'i'){
    return "ssb";
  }
  if(character == 'j'){
    return "slllb";
  }
  if(character == 'k'){
    return "lslb";
  }
  if(character == 'l'){
    return "slssb";
  }
  if(character == 'm'){
    return "llb";
  }
  if(character == 'n'){
    return "lsb";
  }
  if(character == 'o'){
    return "lllb";
  }
  if(character == 'p'){
    return "sllsb";
  }
  if(character == 'q'){
    return "llslb";
  }
  if(character == 'r'){
    return "slsb";
  }
  if(character == 's'){
    return "sssb";
  }
  if(character == 't'){
    return "lb";
  }
  if(character == 'u'){
    return "sslb";
  }
  if(character == 'v'){
    return "ssslb";
  }
  if(character == 'w'){
    return "sllb";
  }
  if(character == 'x'){
    return "lsslb";
  }
  if(character == 'y'){
    return "lsllb";
  }
  if(character == 'z'){
    return "llssb";
  }
  if(character == '1'){
    return "sllllb";
  }
  if(character == '2'){
    return "sslllb";
  }
  if(character == '3'){
    return "sssllb";
  }
  if(character == '4'){
    return "sssslb";
  }
  if(character == '5'){
    return "sssssb";
  }
  if(character == '6'){
    return "lssssb";
  }
  if(character == '7'){
    return "llsssb";
  }
  if(character == '8'){
    return "lllssb";
  }
  if(character == '9'){
    return "llllsb";
  }
  if(character == '0'){
    return "lllllb";
  }
  if(character == ' '){
    return "";
  }
  /*
  if(character == ' '){
    return "pb";
  }
  if(character == '.'){
    return "db";
  }*/
  return "e";
}
/*
void dotBoop(){
  digitalWrite(msgled, LOW);
  delay(2000);
  digitalWrite(msgled, HIGH);
  delay(50);
  digitalWrite(msgled, LOW);
  delay(50);
  digitalWrite(msgled, HIGH);
  delay(50);
  digitalWrite(msgled, LOW);
  delay(50);
  digitalWrite(msgled, HIGH);
  delay(200);
}

void pauseBoop(){
  digitalWrite(msgled, LOW);
  delay(50);
  digitalWrite(msgled, HIGH);
  delay(50);
  digitalWrite(msgled, LOW);
  delay(50);
  digitalWrite(msgled, HIGH);
  delay(200);
}
*/
void shortBoop(){
  digitalWrite(msgled, LOW);
  delay(500);
  digitalWrite(msgled, HIGH);
  delay(200);
}
void longBoop(){
  digitalWrite(msgled, LOW);
  delay(1000);
  digitalWrite(msgled, HIGH);
  delay(200);
}

void wave(int numberOfWaves){
  int numberOfSteps = numberOfWaves;
  step_OFF();         //turning all coils off
  while(numberOfSteps>0){
    forward();        //going forward
    numberOfSteps -- ;//counting down the number of steps
  }
  delay(500);
  
  step_OFF();         //turning all coils off
  numberOfSteps = numberOfWaves;
  while(numberOfSteps>0){
    backward();       //going backward
    numberOfSteps -- ;//counting down the number of steps
  }
  delay(500);
  step_OFF();
}

void backward(){
    //step 1
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(delaytime);

    //step 2
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(delaytime);

    //step 3
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
    delay(delaytime);

    //step 4
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(delaytime);

    //step 5
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(delaytime);

    //step 6
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(delaytime);

    //step 7
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(delaytime);

    //step 8
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(delaytime);
}

void forward(){
    //step 1
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(delaytime);

    //step 2
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(delaytime);

    //step 3
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(delaytime);

    //step 4
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(delaytime);

    //step 5
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(delaytime);

    //step 6
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
    delay(delaytime);

    //step 7
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(delaytime);

    //step 8
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(delaytime);
}

void step_OFF(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
