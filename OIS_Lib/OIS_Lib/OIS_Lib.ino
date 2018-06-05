#include "my_OIS.h";

/*
 * 
 * Setup Variables
 * 
 */
  const int CHANNELS = 1;
  Controller controller(CHANNELS);
  bool flag[CHANNELS];//used to tell when something updates
//end setup

String output;

void setup() {
  output = "";
  for(int i=0; i<CHANNELS; ++i)
    flag[i]=false;
  light=false;
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  lightTog();
  //Handshake wont let anything happen untill it gets its ACK or DEN
  Handshake();//use an int as a parameter for a diferent delay between shake requests default is 5000ms (+300ms, from Beep sorry)

  controller.add(0, Comm("NIN","IS_DOCKED",0));
//  controller.add(1, Comm("CMD","REQUEST_UNDOCKING_PERMISSION",1));
//  controller.add(2, Comm("CMD","UNDOCK",2));

  controller.sync();
}

void loop() {
  output = GetSerial();
  if(output.length()>0){
    if(output.indexOf("=")!=-1){
      int i = controller.runUpdate(output).getA();
      flag[i]=true;
    }
  }
  //Temporary till I do somthing better
  if(flag[0]){
    lightTog(controller.getData(0));
    flag[0]=false;
  }
    
}

