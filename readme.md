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


# OSC

Every message will be of the form
``` /[side]/[process]/[parameter] [val0] [val1] … ```

With:
* side : A or B (corresponds to the actual sides of the totem)
* process : CV (computer vision), mixer, SNN, coarse, glyph, transition
* parameter : depends on process
* values : floats normalized between ```0 & 1``` or ```-1 & 1```

Exemple:
``` /A/CV/flowInst 12 -13.5 100 ```
``` /B/mixer/faders 0 0 0.7 0.3 ```

## CV

* **flow**

Optical flows, gives three values : [x] SUM(vector x) ; [y] SUM (vector y) ; [s] SUM(speed).

4 different time windows : 0s (instantaneous), 10s, 30s, 60s

messages:

``` 
/[side]/CV/flow/0 [x] [y] [s]
/[side]/CV/flow/10 [x] [y] [s]
/[side]/CV/flow/30 [x] [y] [s]
/[side]/CV/flow/60 [x] [y] [s]
```

* **presence**

presence of people in the camera field, one value [0..1] (0: no one / 1: full with people).

4 different time windows : 1s, 10s, 30s, 60s

messages:

``` 
/[side]/CV/presence/1 [pres]
/[side]/CV/presence/10 [pres]
/[side]/CV/presence/30 [pres]
/[side]/CV/presence/60 [pres]
```

## mixer

* **faders**
corresponds to the mixing of the four visual processes (SNN, coards, glyph, transition).

4 float values [0..1]

messages:

```
/[side]/mixer/faders [SNN] [coarse] [glyph] [transition]
```


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
