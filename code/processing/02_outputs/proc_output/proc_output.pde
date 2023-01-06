//Necessary for OSC communication with Wekinator:
import oscP5.*;
import netP5.*;
OscP5 oscP5;
NetAddress dest;
import processing.serial.*;

int type;
Serial myPort;  // The serial port

void setup() {
  //Initialize OSC communication
  oscP5 = new OscP5(this, 12000); //listen for OSC messages on port 12000 (Wekinator default)
  dest = new NetAddress("127.0.0.1", 6448); //send messages back to Wekinator on port 6448, localhost (this machine) (default)

  myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
}

//This is called automatically when OSC message is received
void oscEvent(OscMessage theOscMessage) {
  //if (theOscMessage.checkAddrPattern("/wek/outputs")==true) {
  //  println(theOscMessage.get(0).floatValue());
  //}
  if (theOscMessage.checkAddrPattern("/idle")==true) {
    println("idle");
    myPort.write(0);
  }
  if (theOscMessage.checkAddrPattern("/circle")==true) {
    println("circle");
    myPort.write(1);
  }
  if (theOscMessage.checkAddrPattern("/shake")==true) {
    println("shake");
    myPort.write(2);
  }
}
