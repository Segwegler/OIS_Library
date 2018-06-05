////uncoment for handshake debug data
//#ifndef DEBUG
//#define DEBUG 
//#endif

#include "my_OIS_class.h";



//For testing 
bool light; //for lightTog
void lightTog(){
  if(light){
    digitalWrite(LED_BUILTIN,HIGH);
    //Serial.println("on");
  }else{
    digitalWrite(LED_BUILTIN,LOW);
    //Serial.println("off");
  }
  light=!light;
}
void lightTog(bool t){
  if(t){
    digitalWrite(LED_BUILTIN,HIGH);
    //Serial.println("on");
  }else{
    digitalWrite(LED_BUILTIN,LOW);
    //Serial.println("off");
  }
   light=!t;
}

//Beep
//this is a simple output for debuging 
//Beep takes and int n then flashes the onboard LED n times
//the delay is not ideal but its got to flash
//also the High and low for some boards are flipped so it may be initialy on or off depending on your board (D1 mini off when high, Mega on when high)
void Beep(int n){
  for(int i=0; i<n; i++){
    delay(50);
    lightTog();
    delay(50);
    lightTog();
  }
  delay(200);//I know this is bad but it helps to tell beeps apart
}

//GetSerial function
//should pull input from the serial connection(this is my first time doing somthing like this)
//could be a problem if data is sent to slow I think because 
String GetSerial(){
  if(Serial.available()>0){
    String res = ""; //String for responces 
    //Beep(2); //if this in not here my arduino only reads one character then exits. So maybe its to fast?
    res = Serial.readStringUntil('\n');
    return res;
  }
  return "";
}

//Handshake function
//trys to connect to the game
//waits shakeDelay/1000 seconds then sends shake request again
//
/*


Right now the Handshake request is 451 and the response is 452


*/
//Returns true if connected next would be sync state
//Returns false if Denied by game
//
//This maay be a terible way of comunicating accross the serial port its the first time Ihave done this
//
bool Handshake(int shakeDelay = 5000){
  bool shake=false; //has a shake request been sent 
  String serverRes = "";
  Clock clck;
  while(true){
    if(!shake){
      Serial.write("451\n");
      //Beep(1);
      shake=true;
    }else{
      if(!clck.clockOn())
        clck.startClock();
      if(clck.deltaTime()>shakeDelay){ 
        shake=false; 
        clck.stopClock();//reset to start again next shake cycle
      }
    }

    serverRes = GetSerial();
    if(serverRes == "452"){
      #ifdef DEBUG
      Serial.println("Controller Lock Recived");
      Beep(4);
      #endif
      return true;
    }else if(serverRes == "DEN"){//not real?
      #ifdef DEBUG
      Serial.println("Controller Failed to Lock On");
      Beep(5);
      #endif
      return false;
    }
  }
}



