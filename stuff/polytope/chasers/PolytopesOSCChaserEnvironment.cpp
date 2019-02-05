/*
 * PolytopesOSCChaserEnvironment.cpp
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

#include "PolytopesOSCChaserEnvironment.h"

PolytopesOSCChaserEnvironment::PolytopesOSCChaserEnvironment()
  : currentObservation(OBSERVATION_DIM) {
}

PolytopesOSCChaserEnvironment::~PolytopesOSCChaserEnvironment() {
}

Observation* PolytopesOSCChaserEnvironment::start() {

  return &currentObservation;
}

void PolytopesOSCChaserEnvironment::setNoLeds( int nol ){
    noleds = nol;
}

Observation* PolytopesOSCChaserEnvironment::step(const Action* action) {
  PolytopeOSC& osc = PolytopeOSC::instance();

  for (int i=0; i<noleds; i++) {
    if (action->actions[i]) {
      //printf("Action received: %d\n", i);
      float val = ((real)action->actions[i]) / real(ACTION_MAX);
      //printf("Action received: %d, sending: %f\n", i, val);
      osc.sendOutputLed( i, val );
//       client.sendData(WRITE_LED_SINGLE_VALUE, &val, i);
    }
  }

  // Wait for bang trigger.
  osc.checkBang( POLYTOPES_BANG_TIMEOUT );
  
  return &currentObservation;
}
