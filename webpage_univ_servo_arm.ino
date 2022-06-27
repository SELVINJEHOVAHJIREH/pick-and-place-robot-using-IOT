int a;
int b;
int c;
int f = 16;
#include <AccelStepper.h>
#include <Servo.h>
  String command; 
  //4,5 
Servo myservo1;
Servo myservo2;
  #define ENA   14          // Enable/speed motors Right        GPIO14(D5)
  #define ENB   12          // Enable/speed motors Left         GPIO12(D6)
  #define IN_1  15          // L298N in1 motors Rightx          GPIO15(D8)
  #define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
  #define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
  #define IN_4  0           // L298N in4 motors Left            GPIO0(D3)
/*
const int dirPin = 16;
const int stepPin = 5;
const int dirPin2 = 4;
const int stepPin2 = 0;
const int dirPin3 = 14;
const int stepPin3 = 12;
*/
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver
/*
#define motorInterfaceType 1
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin); // Pin 2 connected to DIRECTION & Pin 3 connected to STEP Pin of Driver
AccelStepper myStepper2(motorInterfaceType, stepPin2, dirPin2);
AccelStepper myStepper3(motorInterfaceType, stepPin3, dirPin3);
*/
#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <SPIFFS.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <Hash.h>
  #include <FS.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "Admin";
const char* password = "Admin123";

const char* PARAM_STRING = "inputString";
const char* PARAM_INT = "inputInt";
const char* PARAM_FLOAT = "inputFloat";

// HTML web page to handle 3 input fields (inputString, inputInt, inputFloat)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>

<head>
    <title>ESP Input Form</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<style>
    .hidden-text-input {
        display: none;
    }
    
    .joypad-container {
        width: 300px;
        display: grid;
        grid-template-areas: "a b c""d q e""f g h""i j k""l m n""o p .";
    }
    
    .arrow-button {
        height: 100px;
        width: 100px;
        font-size: 85px;
        background: transparent;
        border: none;
    }
    
    .arrow-button-upleft-container {
        grid-area: a;
    }
    
    .arrow-button-up-container {
        grid-area: b;
    }
    
    .arrow-button-upright-container {
        grid-area: c;
    }
    .arrow-button-left-container {
        grid-area: d;
    }
    
    .arrow-button-right-container {
        grid-area: e;
    }
    
    .arrow-button-downleft-container {
        grid-area: f;
    }
    .arrow-button-down-container {
        grid-area: g;
    }
    
    .arrow-button-downright-container {
        grid-area: h;
    }
    
    .arrow-button-pick-container {
        grid-area: i;
    }
    
    .arrow-button-moveleft-container {
        grid-area: j;
    }
    
    .arrow-button-moveright-container {
       grid-area: k;
    }
    
    .arrow-button-moveup-container {
        grid-area: l;
    }
    .arrow-button-movedown-container {
        grid-area: m;
    }
    .arrow-button-moveright2-container {
        grid-area: n;
    }
    .arrow-button-moveleftb-container {
        grid-area: o;
    }
    .arrow-button-place-container {
        grid-area: p;
    }
    .arrow-button-drop-container {
        grid-area: q;
    }
</style>

<body>
    

    <div class="joypad-container">

        <div class="arrow-button-upleft-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="G">
                <input class="arrow-button " type="submit" value="&#8598">
            </form>
        </div>

        <div class="arrow-button-up-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="F">
                <input class="arrow-button" type="submit" value="&#8593">
            </form>
        </div>
        <div class="arrow-button-upright-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="I">
                <input class="arrow-button" type="submit" value="&#8599">
            </form>
        </div>
        <div class="arrow-button-left-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="L">
                <input class="arrow-button " type="submit" value="&#8592">
            </form>
        </div>

        <div class="arrow-button-right-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="R">
                <input class="arrow-button" type="submit" value="&#8594">
            </form>
        </div>
        <div class="arrow-button-downleft-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="H">
                <input class="arrow-button" type="submit" value="&#8601">
            </form>
        </div>
        <div class="arrow-button-down-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="B">
                <input class="arrow-button" type="submit" value="&#8595">
            </form>
        </div>

        <div class="arrow-button-downright-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="J">
                <input class="arrow-button" type="submit" value="&#8600">
            </form>
        </div>
         <div class="arrow-button-pick-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="PICK">
                <input class="arrow-button" type="submit" value="&#8605">
            </form>
        </div>
         <div class="arrow-button-moveleft-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="LEFT">
                <input class="arrow-button" type="submit" value="&#8608">
            </form>
        </div>
         <div class="arrow-button-moveright-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="RIGHT">
                <input class="arrow-button" type="submit" value="&#8606">
            </form>
        </div>

        <div class="arrow-button-moveup-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="UP">
                <input class="arrow-button" type="submit" value="&#8607">
            </form>
        </div>

        <div class="arrow-button-movedown-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="DOWN">
                <input class="arrow-button" type="submit" value="&#8609">
            </form>
        </div>
        <div class="arrow-button-moveright2-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="RIGHT2">
                <input class="arrow-button" type="submit" value="&#8649">
            </form>
        </div>
        <div class="arrow-button-moveleftb-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="LEFT">
                <input class="arrow-button" type="submit" value="&#8606">
            </form>
        </div>
        <div class="arrow-button-place-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="PLACE">
                <input class="arrow-button" type="submit" value="&#8623">
            </form>
        </div>
        <div class="arrow-button-stop-container">
            <form action="/get">
                <input type="text" class="hidden-text-input" name="inputString" value="S">
                <input class="arrow-button" type="submit" value="&#9635">
            </form>
        </div>


    </div>
</body>

</html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

// Replaces placeholder with stored values
String processor(const String& var){
  //Serial.println(var);
  if(var == "inputString"){
    return readFile(SPIFFS, "/inputString.txt");
  }
  else if(var == "inputInt"){
    return readFile(SPIFFS, "/inputInt.txt");
  }
  else if(var == "inputFloat"){
    return readFile(SPIFFS, "/inputFloat.txt");
  }
  return String();
}

void setup() {
  
 //pinMode(ENA, OUTPUT);
 //pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
//  pinMode();
  Serial.begin(115200);
  // Initialize SPIFFS
  #ifdef ESP32
    if(!SPIFFS.begin(true)){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #else
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #endif
  
  pinMode(f,OUTPUT);
  myservo2.attach(4);
  myservo1.attach(5);
  /*
  myStepper.setMaxSpeed(1000);
  myStepper.setAcceleration(50);
  myStepper.setSpeed(200);
  myStepper.moveTo(200);

  myStepper2.setMaxSpeed(1000);
  myStepper2.setAcceleration(50);
  myStepper2.setSpeed(200);
  myStepper2.moveTo(200);

  myStepper3.setMaxSpeed(1000);
  myStepper3.setAcceleration(50);
  myStepper3.setSpeed(200);
  myStepper3.moveTo(200);
  */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/get?inputString=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET inputString value on <ESP_IP>/get?inputString=<inputMessage>
    if (request->hasParam(PARAM_STRING)) {
      inputMessage = request->getParam(PARAM_STRING)->value();
      writeFile(SPIFFS, "/inputString.txt", inputMessage.c_str());
    }
    // GET inputInt value on <ESP_IP>/get?inputInt=<inputMessage>
    else if (request->hasParam(PARAM_INT)) {
      inputMessage = request->getParam(PARAM_INT)->value();
      writeFile(SPIFFS, "/inputInt.txt", inputMessage.c_str());
    }
    // GET inputFloat value on <ESP_IP>/get?inputFloat=<inputMessage>
    else if (request->hasParam(PARAM_FLOAT)) {
      inputMessage = request->getParam(PARAM_FLOAT)->value();
      writeFile(SPIFFS, "/inputFloat.txt", inputMessage.c_str());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send_P(200, "text/html", index_html, processor);
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  // To access your stored values on inputString, inputInt, inputFloat
  int yourInputString = readFile(SPIFFS, "/inputString.txt").toInt();
  Serial.print("*** Your inputString: ");
  Serial.println(yourInputString);
  
  int yourInputInt = readFile(SPIFFS, "/inputInt.txt").toInt();
  Serial.print("*** Your inputInt: ");
  Serial.println(yourInputInt);
  
  int yourInputFloat = readFile(SPIFFS, "/inputFloat.txt").toInt();
  Serial.print("*** Your inputFloat: ");
  Serial.println(yourInputFloat);
  //digitalWrite(f,HIGH);

  String valour = readFile(SPIFFS, "/inputString.txt");
  Serial.print("*** Your inputString: ");
  Serial.println(valour);

  //myservo1.write(yourInputString); 
  //myservo2.write(yourInputInt); 

  command = valour;

      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "S") stopRobot();
      if (command == "PICK") digitalWrite(f, HIGH);
      else if (command == "LEFT") myservo1.write(0); 
      else if (command == "RIGHT") myservo1.write(90); 
      else if (command == "UP") myservo2.write(180); 
      else if (command == "DOWN") myservo2.write(0); 
      else if (command == "RIGHT2") myservo1.write(180); 
      else if (command == "LEFT") myservo1.write(0); 
      else if (command == "PLACE") digitalWrite(f, LOW);
      else if (command == "DROP") digitalWrite(f, LOW);
  /*
  myStepper.moveTo(yourInputString);
  myStepper2.moveTo(yourInputInt);
  myStepper3.moveTo(yourInputFloat);
  myStepper.run();
  myStepper2.run();
  myStepper3.run();
  */
}
void goAhead(){ 
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, HIGH);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, HIGH);
  }

void goBack(){
   
      
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, HIGH);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, HIGH);
  }

void goRight(){ 
     
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, HIGH);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, HIGH);
  }

void goLeft(){
     
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, HIGH);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, HIGH);
  }

void goAheadRight(){
    
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, HIGH);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, HIGH);
   }

void goAheadLeft(){
     
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, HIGH);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, HIGH);
  }

void goBackRight(){ 
      
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, HIGH);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, HIGH);
  }

void goBackLeft(){ 
     
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, HIGH);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, HIGH);
  }

void stopRobot(){  
   
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, LOW);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, LOW);
 }
