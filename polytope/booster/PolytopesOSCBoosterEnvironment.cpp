/*
 * PolytopesOSCBoosterEnvironment.cpp
 *
 * (c) 2012 Sofian Audry -- info(@)sofianaudry(.)com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PolytopesOSCBoosterEnvironment.h"

#include "../common/PolytopesDefs.h"
#include "../osc/PolytopesOSC.h"

#include <unistd.h>

PolytopesOSCBoosterEnvironment::PolytopesOSCBoosterEnvironment()
  : currentObservation(OBSERVATION_DIM) {
    noleds = N_LEDS;
    nonodes = N_NODES;
}

PolytopesOSCBoosterEnvironment::~PolytopesOSCBoosterEnvironment() {
}

Observation* PolytopesOSCBoosterEnvironment::start() {

  return &currentObservation;
}

void PolytopesOSCBoosterEnvironment::setNoLeds( int nol ){
    noleds = nol;
}

void PolytopesOSCBoosterEnvironment::setNoNodes( int non ){
    nonodes = non;
}


Observation* PolytopesOSCBoosterEnvironment::step(const Action* action) {
  PolytopeOSC& osc = PolytopeOSC::instance();

  //printf("Sending the data\n");
  for (int i=0; i<nonodes; i++) {
    if (action->actions[i*N_LEDS_PER_NODE]) {
      float val = ((real)action->actions[i*N_LEDS_PER_NODE]) / real(ACTION_MAX);
      osc.sendOutputNode( i, val );
//       osc.sendData(WRITE_NODE_SINGLE_VALUE, &val, i);      
      //printf("Sending val: %f\n", val);
    }
  }

  usleep(10000L); // sleep for 10 millis

  int k=0;

  // Receive data (light).
  float * inputdata = osc.getNodeData();
  int inputsize = osc.getNodeDataSize();
//   osc.getNodeData( (float*)&inputs );
//   osc.readData(READ_ALL_NODES_SINGLE_VALUE, (void*)&inputs);
  for (int i=0; i<inputsize; i++) {
    currentObservation[k++] = inputdata[i];
    //printf("%f %f %f -> %f | ", input.photoFront, input.photoLeft, input.photoRight, light);
  }
  //printf("\n");

  // Complete for consistency.
  for (int i=0; i<noleds; i++) {
    currentObservation[k++] = (float)action->actions[i] / (float) ACTION_MAX;
  }

  osc.checkBang( POLYTOPES_BANG_TIMEOUT );
//   osc.hasNewData(READ_BANG, POLYTOPES_BANG_TIMEOUT);

  return &currentObservation;
}
