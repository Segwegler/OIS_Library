# OiS_Library
A library to help interface with objects in space
The serial protocol can be found at http://objectsgame.com/the-controllers/ois-serial-data-protocol/
Commands and requests can be found in the wiki 

To use this with the Arduino ide put the header files in the sketch folder 
Then put #include "my_OIS.h" at the begining of your sketch

This library contains a few classes to help with comunicating with the game
-Controller
-Comm
-Clock
-Pair_i

*Controller: holds all the requests and commands that you set up and has functions to sync and execute each one
  Constructors
    -Controller(int s)
      s is the number of requests and commands the controller will hold
  Member Functions
    -getSize() returns int _size  The max number of Comms
    -add(int, Comm) adds a Comm to the _comms array at the int index
    -operator [int] returns the Comm in _comms at int index
    -sync() Sends the sync commands for all commands and requests per the serial protocol 
    -exc(int) Sends the command set up in the sync protocol
    -updateData(int i,int d) Updates the data in _comms[i] to d returns true if it is sucsessful
    -updateData(Pair_i) Updates the data in _comms[Pair_i.A] to Pair_i.B returns true if it is sucsessful
    -getData(int) returns the data in _comms[int]
    -readUpdate(String) Returns the channel and data from the string read in from the string in a Pair_i .A=channel .B=data
    -runUpdate(String) Updates the data in the Comm in _comms at the index = to the channel in the string to the data in the string
  Private Data Members
    -const int _size The size of _comms
    -Comm* _comms Array of Comm
      
*Comm: container for requests and commands
  Constructors
    -Default
      sets all string data menbers to ""
      sets all int data members to -1
    -Comm(String t, String c, int ch)
      sets _type to t
      sets _cmd to c
      sets _ch to ch if a valid value
  Member Functions 
    -getType() returns the _type string
    -getCmd() returns the _cmd string
    -getCh()  returns the _ch int 
    -getData() returns the _data int
    -setType(String) sets _type to String
    -setCmd(String) sets _cmd to String
    -setCh(int) sets _ch to int
    -setData(int) sets _data to int
    -String sync() returns the sync string per serial protocol
    -String exc()  returns the exc string per serial protocol
  Private Data Members
    -String _type the type of request/command  ie: CMD || NIB || NIN || NIF
    -String _command the command/request 
    -int _ch channel to listen to or send command to
    -int _data data from request
    
*Clock: used to track passage of time
  Constructors
    -Default
      sets _clockOn to false
      sets _startClock to 0
  Member Functions
    -startClock() sets _startClock to millis() sets _clockOn to true
    -stopClock() sets _clockOn to false
    -unsigned long deltaTime() returns the differnce between millis() and _startClock
    -bool clockOn() returns _clockOn true = on
  Private Data Members
    -unsigned long _startClock when the clock starts
    -bool _clockOn if the clock is on
    
*Pair_i: int pair for some returns
  Constructors
    -Default
      sets _a=-1
      sets _b=-1
    -Pair_i(int a, int b)
      sets _a=a
      sets _b=b
  Member Functions
    -int getA() returns _a
    -int getB() returns _b
    -setA(int a) sets _a=a
    -setA(int b) sets _b=b
  Private Data Members
    -int _a
    -int _b
    
% Handshake(): sends initial connection request and waits for the responce
  How to call
    Handshake();  Will delay ~
      
      
    
     
      
      
      
      
      
