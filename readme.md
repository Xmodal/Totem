Totem
=====

Github for the totem project

# Working pipe

* openFrameworks (video generation) => syphon => touch designer (conversion video to serial) => serial => teensy => LED
* LED array : 9 x 360 

# Folders

* **Code** : working folder, one folder by language. 
* **Hardware** : PCB files, gerbers, BOM… coming from Lucas.
* **Stuff** : for dumping potential codes, examples, snippets… working or not.


# openFrameworks

Install the OF folder “of_v0.10.1_osx_release” in ```Totem/Code/openFrameworks/of_v0.10.1_osx_release```
“of_v0.10.1_osx_release” is included in the .gitignore .



# Touchdesigner

Disable auto backup (to avoid cluttering the git) : ```Preference -> increment filename on save -> off```

# Syphon


Issue with Touch Designer not reconnecting with syphon:
* **Processing** : To stop a program do not click the "stop" button but the close the display window
* **openFrameworks** : To stop a program close the display window

**Open Frameworks**

Need ofxSyphon

In ofApp.h
```
#include "ofxSyphon.h"

public:
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonClient mClient;
```

In ofApp.cpp
```
void ofApp::setup(){
	mainOutputSyphonServer.setName("OF_syphon");
	mClient.setup();
}

void ofApp::draw(){
	mClient.draw(9,360);
	mainOutputSyphonServer.publishScreen();
}
```

# OSC

**Data** : floats normalized between ```0 & 1``` or ```-1 & 1```
**message** : in the form of ```/addr param1 param1 ...```

**lightboard** : port-12000 - message: ```/led float[0..1]```
**optical_flow_with_osc** : send: ```/aveFlow x[-1..1] y[-1..1]```

### Example for receiving OSC with Processing

```
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
```

### Example for sending OSC with Processing

```
/* in the following different ways of creating osc messages are shown by example */
  OscMessage myMessage = new OscMessage("/test");
  
  myMessage.add(123); /* add an int to the osc message */

  /* send the message */
  oscP5.send(myMessage, myRemoteLocation); 
  ```
