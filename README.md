# OiS_Library
A library to help interface with objects in space <br>
The serial protocol can be found at http://objectsgame.com/the-controllers/ois-serial-data-protocol/ <br>
Commands and requests can be found in the wiki <br> 

To use this with the Arduino ide put the header files in the sketch folder  <br>
Then put #include "my_OIS.h" at the begining of your sketch <br>

This library contains a few classes to help with comunicating with the game <br>
-Controller <br>
-Comm <br>
-Clock <br>
-Pair_i <br>

*Controller: holds all the requests and commands that you set up and has functions to sync and execute each one <br>
  Constructors <br>
    -Controller(int s) <br>
      s is the number of requests and commands the controller will hold <br>
  Member Functions <br>
    -getSize() returns int _size  The max number of Comms <br>
    -add(int, Comm) adds a Comm to the _comms array at the int index <br>
    -operator [int] returns the Comm in _comms at int index <br>
    -sync() Sends the sync commands for all commands and requests per the serial protocol  <br>
    -exc(int) Sends the command set up in the sync protocol <br>
    -updateData(int i,int d) Updates the data in _comms[i] to d returns true if it is sucsessful <br>
    -updateData(Pair_i) Updates the data in _comms[Pair_i.A] to Pair_i.B returns true if it is sucsessful <br>
    -getData(int) returns the data in _comms[int] <br>
    -readUpdate(String) Returns the channel and data from the string read in from the string in a Pair_i .A=channel .B=data <br>
    -runUpdate(String) Updates the data in the Comm in _comms at the index = to the channel in the string to the data in the string <br>
  Private Data Members <br>
    -const int _size The size of _comms <br>
    -Comm* _comms Array of Comm <br>
       <br>
*Comm: container for requests and commands <br>
  Constructors <br>
    -Default <br>
      sets all string data menbers to "" <br>
      sets all int data members to -1 <br>
    -Comm(String t, String c, int ch) <br>
      sets _type to t <br>
      sets _cmd to c <br>
      sets _ch to ch if a valid value <br>
  Member Functions  <br>
    -getType() returns the _type string <br>
    -getCmd() returns the _cmd string <br>
    -getCh()  returns the _ch int <br> 
    -getData() returns the _data int <br>
    -setType(String) sets _type to String <br>
    -setCmd(String) sets _cmd to String <br>
    -setCh(int) sets _ch to int <br>
    -setData(int) sets _data to int <br>
    -String sync() returns the sync string per serial protocol <br>
    -String exc()  returns the exc string per serial protocol <br>
  Private Data Members <br>
    -String _type the type of request/command  ie: CMD || NIB || NIN || NIF <br>
    -String _command the command/request <br> 
    -int _ch channel to listen to or send command to <br>
    -int _data data from request <br>
    
*Clock: used to track passage of time <br>
  Constructors <br>
    -Default <br>
      sets _clockOn to false <br>
      sets _startClock to 0 <br>
  Member Functions <br>
    -startClock() sets _startClock to millis() sets _clockOn to true <br>
    -stopClock() sets _clockOn to false <br>
    -unsigned long deltaTime() returns the differnce between millis() and _startClock <br>
    -bool clockOn() returns _clockOn true = on <br>
  Private Data Members <br>
    -unsigned long _startClock when the clock starts <br>
    -bool _clockOn if the clock is on <br>
    
*Pair_i: int pair for some returns <br>
  Constructors <br>
    -Default <br>
      sets _a=-1 <br>
      sets _b=-1 <br>
    -Pair_i(int a, int b) <br>
      sets _a=a <br>
      sets _b=b <br>
  Member Functions <br>
    -int getA() returns _a <br>
    -int getB() returns _b <br>
    -setA(int a) sets _a=a <br>
    -setA(int b) sets _b=b <br>
  Private Data Members <br>
    -int _a <br>
    -int _b <br>
    
% Handshake(): sends initial connection request and waits for the responce <br>
  How to call <br>
    Handshake();  Will delay ~5000ms <br>
      
      
    
     
      
      
      
      
      
