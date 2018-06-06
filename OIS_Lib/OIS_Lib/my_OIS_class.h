//my_OIS_class.h
//holds all the classes for use by my_OIS

//Class Pair_i
//used to return a pair of Ints
class Pair_i{
  public:
  Pair_i():_a(-1),_b(-1)
  {}
  Pair_i(int a, int b):_a(a),_b(b)
  {}
  Pair_i(const Pair_i &p){
    this->_a = p.getA();
    this->_b = p.getB();  
  }
  int getA() const{
    return this->_a;
  }
  int getB() const{
    return this->_b;
  }
  void setA(int a){
    this->_a=a;
  }
  void setB(int b){
    this->_b=b;
  }
  void set(int a,int b){
    this->_a=a;
    this->_b=b;
  }
  private:
  int _a;
  int _b;
};


//Class Clock
//used to track passage of time
//_startClock is a unsigned long stored when startClock() is called
//_clockOn is a bool and should be set to true if the clock is on and false if the clock is off
//
//Clock Constructor fets all variables to default values
//Call startClock() to start tracking time
//Call stopClock() to stop tracking time
//Call deltaTime() to get the get the time elapsed form when startClock() was called
//      deltaTime() returns a unsigned long (that is what millis() returns)
//Call clockOn() to findout if the clock is running returns a bool true for ON false for OFF

class Clock{
  public:
    Clock();
    void startClock();
    void stopClock();
    unsigned long deltaTime();
    bool clockOn();
  private:
    bool _clockOn;
    unsigned long _startClock;
};

Clock::Clock(){
  this->_clockOn=false;
  this->_startClock=0;
}

void Clock::startClock(){
  this->_startClock = millis();
  this->_clockOn = true;
}

void Clock::stopClock(){
  this->_clockOn = false;
}

unsigned long Clock::deltaTime(){
  unsigned long dTime = millis() - this->_startClock;
  return dTime;
}

bool Clock::clockOn(){
  return this->_clockOn;
}

//end class Clock


//Class Comm
//used for all the commands and data requests
//there is no validation checking use wildly at your own risk
//_type should be either CMD, NIB,NIN, or NIF (look at the docs on objectsgame.com)
//_cmd should be one of the commands or data request values
//_data is be where the requested data gets updated
//_ch should be the channel number the command or request is on (this could also be the index of an array to simplify lookup for updates)
//
//Comm constructor defalts all variables to 0 or empty string
//Comm(Str type, Str cmd, Int ch) sets the variables _type,_cmd and _ch to their respective parameter
//accsesors do what they look like they do
//mutators do what they look like they do
//sync take no parameters and returns a string in the format needed to send to the game during the sync phase of setup
//exc() returns a empty string if _cmd is anything other than CMD if it is CMD then it will return the proper format the be sent to the game
class Comm{
  public:
    Comm();
    Comm(String t, String c):_type(t), _cmd(c),_ch(-1),_data(0){
       if(this->_ch<0 && !(t!="CMD" || t!="NIB" || t!="NIN" || t!="NIF"))
        this->_ch=-1;
    }
    Comm(String t,String c,int ch):_type(t), _cmd(c),_ch(ch),_data(0){
      if(this->_ch<0 && !(t!="CMD" || t!="NIB" || t!="NIN" || t!="NIF"))
        this->_ch=-1;
    }
    
    String getType();
    String getCmd();
    int getCh();
    int getData();
    void setType(String t);
    void setCmd(String c);
    void setCh(int ch);
    void setData(int d);
    String sync();
    String exc();
    
  private:
    String _type;
    String _cmd;
    int _ch;
    int _data;
};

Comm::Comm(){
  this->_type="";
  this->_cmd="";
  this->_ch=-1;
  this->_data=0;
}

String Comm::getType(){
  return this->_type;
}

String Comm::getCmd(){
  return this->_cmd;
}

int Comm::getCh(){
  return this->_ch;
}

int Comm::getData(){
  return this->_data;
}

void Comm::setType(String t){
  this->_type=t;
}

void Comm::setCmd(String c){
  this->_cmd=c;
}

void Comm::setCh(int ch){
  this->_ch=ch;
}

void Comm::setData(int d){
  this->_data=d;
}

String Comm::sync(){
  if(this->_ch!=-1)
    return (this->getType() +"="+this->_cmd+","+ this->_ch +"\n");
  return "";
}

String Comm::exc(){
  if(this->getType() != "CMD" || this->_ch==-1)
    return "";
  return ("EXC="+String(this->_ch)+"\n");
}

//end Class Comm

//Class Controller

class Controller{
  public:
    Controller(int s):_size(s)
    {
      _comms = new Comm[_size];
      for(int i=0; i<_size; i++)
      {
        _comms[i] = Comm();
      }
    }
    ~Controller(){
      delete _comms;
    }
    
    int getSize();
    Comm add(int i, Comm c);
    Comm operator[](int i);
    void sync();
    void exc(int i);
    bool updateData(int i, int data);
    bool updateData(Pair_i p);
    int getData(int i);
    Pair_i readUpdate(String s);
    Pair_i runUpdate(String s);
    
  private:
  const int _size;
  Comm* _comms;
};

int Controller::getSize(){
  return this->_size;
}

Comm Controller::add(int i, Comm c){
  int s=this->getSize();
  String t = c.getType();
  if(0<=i && i<s){
    if(c.getCh()==-1){
      c.setCh(i);
    }
    this->_comms[i]=c;
    return this->_comms[i]; 
  }
  return Comm();
}

Comm Controller::operator[](int i){
  if(i>=0 && i<this->getSize()){
    return this->_comms[i];
  }
  return Comm();
}

void Controller::sync(){
  for(int i=0;i<this->getSize(); ++i)
  {
    Serial.print(this->_comms[i].sync());
  }
  Serial.print("ACT\n");
}

void Controller::exc(int i){
  if(i>=0 && i<this->getSize()){
    Serial.print(this->_comms[i].exc());
  }
}

//updateData
//sets data in _comms[i] = d
bool Controller::updateData(int i,int d){
  if(i>=0 && i<this->getSize() && this->_comms[i].getType()!="CMD"){
    this->_comms[i].setData(d);
    return true;
  }
  return false;
}


//updateData
//sets data in _comms[Pair_i._a] = Pair_i._b
bool Controller::updateData(Pair_i p){
  if(p.getA()>=0 && p.getA()<this->getSize()){
    if(this->_comms[p.getA()].getType()!="CMD"){
      this->_comms[p.getA()].setData(p.getB());
      return true;
    }
  }
  return false;
}

//getData
//Returns data form _comms[i]
int Controller::getData(int i){
  if(i>=0 && i<this->getSize()){
    return this->_comms[i].getData();
  }
  return 0;
}

//Read update function
//this function takes a string and returns a pair_i
//pair_i.a = channel
//pair_i.b = data
Pair_i Controller::readUpdate(String s){
  if(s.indexOf('=')!=-1){
    return Pair_i(s.substring(0,s.indexOf('=')).toInt(),s.substring(s.indexOf('=')+1,s.length()).toInt());
  }
  return Pair_i();
}

//Function runUpdate(String)
Pair_i Controller::runUpdate(String s){
  if(s.indexOf('=')!=-1)
  {
    #ifdef DEBUG
    Serial.print(s);
    Serial.print(this->readUpdate(s).getA());
    Serial.print(" <> ");
    Serial.println(this->readUpdate(s).getB());
    #endif
    if(this->updateData(this->readUpdate(s))){
      return this->readUpdate(s);
    }
      
  }
  return Pair_i();
}





