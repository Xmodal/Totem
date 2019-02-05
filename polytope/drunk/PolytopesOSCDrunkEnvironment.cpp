/*
 * PolytopesOSCDrunkEnvironment.cpp
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

#include "PolytopesOSCDrunkEnvironment.h"

PolytopesOSCDrunkEnvironment::PolytopesOSCDrunkEnvironment()
  : currentObservation(OBSERVATION_DIM) {
}

PolytopesOSCDrunkEnvironment::~PolytopesOSCDrunkEnvironment() {
}

Observation* PolytopesOSCDrunkEnvironment::start() {

  return &currentObservation;
}

void PolytopesOSCDrunkEnvironment::setNoLeds( int nol ){
    noleds = nol;
}


Observation* PolytopesOSCDrunkEnvironment::step(const Action* action) {
  PolytopeOSC& osc = PolytopeOSC::instance();

  std::vector<float> * ledValues = new std::vector<float>;
//   float ledValues[noleds];
  for (int i=0; i<noleds; i++) {
    float newvalue = (float)action->actions[i] / (float) ACTION_MAX;
    ledValues->push_back( newvalue );
//     ledValues[i] = 
//     printf("%f ", ledValues[i]);
//     printf("%f ", newvalue);
  }
//   printf("\n");

  // Send data.
  osc.sendOutputAllLeds( ledValues );
//   client.sendData(WRITE_ALL_LEDS_SINGLE_VALUE, ledValues);

  // Wait for bang.
  osc.checkBang( POLYTOPES_BANG_TIMEOUT );

  return &currentObservation;
}
