Totem
=====

Github for the totem project

# Folders

* **Code** : working folder, one folder by language. 
* **Hardware** : PCB files, gerbers, BOM… coming from Lucas.
* **Stuff** : for dumping potential codes, examples, snippets… working or not.

# OSC

Lightboard - Port: 12000 - message: `/led int[0..255]`

Data : float between 0 & 1

<h3>Example for receiving OSC with Processing</h3>


//import librarys for OSC
import oscP5.*;
import netP5.*;

//vars for OSC
OscP5 oscP5;
NetAddress myRemoteLocation;

void setup(){
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 12000);

  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("127.0.0.1", 12000);
}

/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
  println(" value: "+theOscMessage.get(0).intValue());

  if (theOscMessage.checkAddrPattern("/led") == true) {
    brightness = theOscMessage.get(0).intValue();
  }
}


<h3>Example for sending OSC with Processing</h3>

  /* in the following different ways of creating osc messages are shown by example */
  OscMessage myMessage = new OscMessage("/test");
  
  myMessage.add(123); /* add an int to the osc message */

  /* send the message */
  oscP5.send(myMessage, myRemoteLocation); 