/*
 * PolytopesOSCFireflyEnvironment.cpp
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

#include "PolytopesOSCFireflyEnvironment.h"

#include "../common/PolytopesDefs.h"

#include <assert.h>
#include <unistd.h>

PolytopesOSCFireflyEnvironment::PolytopesOSCFireflyEnvironment()
  : currentObservation(OBSERVATION_DIM) {
}

PolytopesOSCFireflyEnvironment::~PolytopesOSCFireflyEnvironment() {
}

Observation* PolytopesOSCFireflyEnvironment::start() {

  return &currentObservation;
}

void PolytopesOSCFireflyEnvironment::setNoNodes( int non ){
    nonodes = non;
}

void PolytopesOSCFireflyEnvironment::setNoLeds( int nol ){
    noleds = nol;
}

Observation* PolytopesOSCFireflyEnvironment::step(const Action* action) {
//   PolytopesNodesClient& client = PolytopesNodesClient::instance();
  PolytopeOSC& osc = PolytopeOSC::instance();

  // Send data (one value per node).
  float oneValue = 1;
  //printf("Sending the data\n");
  for (int i=0; i<nonodes; i++) {
    if (action->actions[i*N_LEDS_PER_NODE])
      osc.sendOutputNode( i, oneValue );
  }

  usleep(10000L); // sleep for 10 millis

  int k=0;

  // Receive data (light).
//   float inputs[N_NODES];
  float * inputdata = osc.getNodeData();
  int inputsize = osc.getNodeDataSize();
//   client.readData(READ_ALL_NODES_SINGLE_VALUE, (void*)&inputs);
//   assert(N_NODES == client.getDataNodeSize(READ_ALL_NODES_SINGLE_VALUE));
  for (int i=0; i<inputsize; i++) {
    currentObservation[k++] = inputdata[i];
    //printf("%f %f %f -> %f | ", input.photoFront, input.photoLeft, input.photoRight, light);
  }

  int dimensions = action->dim();
  // Complete for consistency.
  assert(action->dim() == noleds);
  for (int i=0; i<noleds; i++) {
//     currentObservation[k++] = (float)action->actions[i] / (float) action->properties->maxAction(i);
    currentObservation[k++] = (float)action->actions[i] / (float) ACTION_MAX;
  }

  osc.checkBang( POLYTOPES_BANG_TIMEOUT );

  return &currentObservation;
}
