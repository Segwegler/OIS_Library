
#include "my_OIS.h";

/*
 * 
 * Setup Variables
 * 
 */
 //CHANNELS is the number of channels that you want to use
 //A channel is required for each command and request you are going to use
  const int CHANNELS = 4;
  //controller will hold all of your commands and requests
  Controller controller(CHANNELS);
  bool flag[CHANNELS];//used to tell when something updates (will be updated)
//end setup

String output;//used to store responses from the game

void setup() {
  //set variables to default values
  output = "";
  for(int i=0; i<CHANNELS; ++i)
    flag[i]=false;
  
  Serial.begin(9600);//opens the serial port with a baud rate of 9600
  pinMode(LED_BUILTIN, OUTPUT);//A default output its built in to some boards and is also on pin 13 on the mega

  //a function to toggle the built in LED
  lightTog();

  //Handshake tells the game there is a controller here
  //it wont let anything happen untill the game responds accepting it as a controller
  //This must be called for your controller to work (or you could perform the handshake yourself)
  Handshake();//use an int as a parameter for a diferent delay between shake requests default is 5000ms (+300ms, from Beep sorry)

  //Here are some examples on how add Requests and Commands to the controller
  //The first number is the index that the Comm will be stored at (valid values are 0<=n<=CHANNELS) Order doesn't matter as long as you know where it is
  //The Comm object is created with ...
  //1. type either CMD for a command or NIB,NIN, or NIF for a Boolean or Numerical request (NIF will get you a a number that needs to be formatted to have 2 decimal places)
  //2. the command or request name
  //3. the channel for the command or request to be sent or recived on (If this is left blank it will be set to the index where the Comm is stored)
  controller.add(0, Comm("NIB","IS_DOCKED",112));//this comm will be stored in controller[0] it is a Boolean request for IS_DOCKED on channel 112
  controller.add(1, Comm("CMD","REQUEST_UNDOCKING_PERMISSION"));//this comm will be stored in controller[1] it s the REQUEST_UNDOCKING_PERMISSION command and will be on channel 1

  Comm comm1("CMD","TOGGLE_MAIN_ENGINE",10); //comm1 is the command TOGGLE_MAIN_ENGINE on channel 10
  Comm comm2("NIN","DIRECTION");//comm2 is a numeric request for DIRECTION and has no channel set

  controller.add(2,comm1);//comm1 will be stored at controller[2]
  controller.add(3,comm2);//comm2 will be stored at controller[3] and now has the channel 3

  //sync sends the commands and requests to the game so it knows which commands/requests should be on which channels
  //if this is not called the game wont respond to any serial commands and wont send any updates for your requests
  controller.sync();
}

void loop() {
  output = GetSerial();
  if(output != ""){
    Serial.println("DATA GET");
  }
  
  
  
    
}

