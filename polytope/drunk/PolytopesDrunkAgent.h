/*
 * PolytopesDrunkAgent.h
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

#ifndef POLYTOPESDRUNKAGENT_H_
#define POLYTOPESDRUNKAGENT_H_

#include "../common/PolytopesDefs.h"
#include <qualia/core/Agent.h>

class PolytopesDrunkAgent : public Agent {
public:
  Action* currentAction;
  ActionProperties actionProps;

  float mainValue;
//   float lineValues[N_LINES]; //FIXME
//   float nodeValues[N_NODES]; //FIXME
//   float ledValues[N_LEDS]; //FIXME

  float * lineValues; //FIXME
  float * nodeValues; //FIXME
  float * ledValues; //FIXME

  float mainWeight;
  float lineWeight;
  float nodeWeight;
  float ledWeight;

  float maxLedInc;

  PolytopesDrunkAgent(float maxLedInc);
  virtual ~PolytopesDrunkAgent();
  virtual void init();
  virtual Action* start(const Observation* observation);
  virtual Action* step(const Observation* observation);
  
  static void update(float* values, float maxInc, int n);
  static real update(float value, float maxInc);
  
  void initValues( int nlines, int nnodes, int nleds, int nodesperline );
  void updateParameters( float * params );
  
private:
  int nolines;
  int nonodes;
  int noleds;
  int nonodesperline;
};

#endif /* POLYTOPESDRUNKAGENT_H_ */
