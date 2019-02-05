/*
 * PolytopesDrunkAgent.cpp
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

#include "PolytopesDrunkAgent.h"
#include <qualia/util/random.h>

#include <string.h>

PolytopesDrunkAgent::PolytopesDrunkAgent(float maxLedInc_) : actionProps(ACTION_DIM, N_ACTIONS_PER_DIM), currentAction(0) {
  maxLedInc = maxLedInc_;
  currentAction = Q_NEW(Action)(&actionProps);
  init();
}

PolytopesDrunkAgent::~PolytopesDrunkAgent() {
  Q_DELETE(currentAction);
}

void PolytopesDrunkAgent::init() {
  
  mainWeight = lineWeight = nodeWeight = ledWeight = 0.25f;
  mainValue = 0;
  
}

void PolytopesDrunkAgent::initValues( int nlines, int nnodes, int nleds, int nodesperline ) {
  nolines = nlines;
  nonodes = nnodes;
  noleds = nleds;
  nonodesperline = nodesperline;  
  
  lineValues = (float*) malloc( nolines * sizeof( float ) );
  memset(lineValues, 0, nolines*sizeof(float));
  nodeValues = (float*) malloc( nonodes * sizeof( float ) );
  memset(nodeValues, 0, nonodes*sizeof(float));
  ledValues = (float*) malloc( noleds * sizeof( float ) );
  memset(ledValues,  0, noleds*sizeof(float));
}

Action* PolytopesDrunkAgent::start(const Observation* observation) {
  init();
  return step(observation);
}

void PolytopesDrunkAgent::updateParameters( float * params ){
//   float params[READ_PARAMETERS_SIZE];
//   PolytopesNodesClient::instance().readData(READ_PARAMETERS, params); // FIXME
  int i=0;
  maxLedInc  = params[i++];
  mainWeight = params[i++];
  lineWeight = params[i++];
  nodeWeight = params[i++];
  ledWeight  = params[i++];

  // Normalize weights.
  float sumWeights = mainWeight + lineWeight + nodeWeight + ledWeight;
  mainWeight /= sumWeights;
  lineWeight /= sumWeights;
  nodeWeight /= sumWeights;
  ledWeight  /= sumWeights; 
}

Action* PolytopesDrunkAgent::step(const Observation* observation) {
  // Update all.
  update(&mainValue, maxLedInc, 1);
  update(lineValues, maxLedInc, nolines); // FIXME
  update(nodeValues, maxLedInc, nonodes); // FIXME
  update(ledValues,  maxLedInc, noleds); // FIXME

// //   float params[READ_PARAMETERS_SIZE];
// //   PolytopesNodesClient::instance().readData(READ_PARAMETERS, params); // FIXME
//   int i=0;
// //   maxLedInc  = params[i++];
// //   mainWeight = params[i++];
// //   lineWeight = params[i++];
// //   nodeWeight = params[i++];
// //   ledWeight  = params[i++];
// 
//   // Normalize weights.
//   float sumWeights = mainWeight + lineWeight + nodeWeight + ledWeight;
//   mainWeight /= sumWeights;
//   lineWeight /= sumWeights;
//   nodeWeight /= sumWeights;
//   ledWeight  /= sumWeights;

  // Compute actions.
  int node=0;
  int led=0;
  float mainVal = mainWeight*mainValue;
  for (int line=0; line<nolines; line++) { // FIXME
    float lineVal = lineWeight*lineValues[line];
    for (int i=0; i<nonodesperline; i++, node++) { // FIXME
      float nodeVal = nodeWeight*nodeValues[node];
      for (int j=0; j<N_LEDS_PER_NODE; j++, led++) { // FIXME
        float ledVal = ledWeight*ledValues[led];
        float action = mainVal + lineVal + nodeVal + ledVal;
        (*currentAction)[led] = (int) (ACTION_MAX * action);
      }
    }
  }

  return currentAction;
}

void PolytopesDrunkAgent::update(float* values, float maxInc, int n) {
  for (int i=0; i<n; i++)
    values[i] = update(values[i], maxInc);
}

real PolytopesDrunkAgent::update(float value, float maxInc) {
  maxInc = POLYTOPES_DRUNK_MAX_LED_INC; // XXX: hack
  float lowerBound = (value - maxInc >= 0 ? -maxInc : -value);
  float upperBound = (value + maxInc <= 1 ? +maxInc : (1-value));
  //printf("Value: %f , maxInc: %f, lowerBound: %f, upperBound: %f", value, maxInc, lowerBound, upperBound);
  //value += randomUniform(lowerBound, upperBound);
  value += randomUniform(-maxInc, +maxInc);
  value = (value > 1 ? 1 : (value < 0 ? 0 : value));
  //printf(" ==> Next value: %f\n", value);
  return value;
}
