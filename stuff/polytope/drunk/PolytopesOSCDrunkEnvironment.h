/*
 * PolytopesDataNetworkDrunkEnvironment.h
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

#ifndef POLYTOPESOSCDRUNKENVIRONMENT_H_
#define POLYTOPESOSCDRUNKENVIRONMENT_H_

// #include "common/PolytopesNodesClient.h"
#include "../osc/PolytopesOSC.h"
#include "../common/PolytopesDefs.h"
#include <qualia/core/Environment.h>

class PolytopesOSCDrunkEnvironment: public Environment {
public:
  Observation currentObservation;

  PolytopesOSCDrunkEnvironment();
  virtual ~PolytopesOSCDrunkEnvironment();
  virtual Observation* start();
  virtual Observation* step(const Action* action);
  
  void setNoLeds( int nol );

private:
  int noleds;

};

#endif /* POLYTOPESOSCDRUNKENVIRONMENT_H_ */
