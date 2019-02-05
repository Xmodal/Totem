/*
 * PolytopesFireflyAgent.cpp
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

#include "PolytopesFireflyAgent.h"
#include <qualia/util/random.h>
#include <math.h>

#include <string.h>

// ActionProperties PolytopesFireflyNodeAgent::fireflyProperties(N_LEDS_PER_NODE, N_ACTIONS_PER_DIM);
ActionProperties fireflyProperties(N_LEDS_PER_NODE, N_ACTIONS_PER_DIM);

PolytopesFireflyNodeAgent::PolytopesFireflyNodeAgent(int flashPowerThreshold_, int flashTime_, int blindTime_)
  : currentAction(&fireflyProperties),
    power(0), blind(0), flash(0),
    flashPowerThreshold(flashPowerThreshold_), flashTime(flashTime_), blindTime(blindTime_),
    lastIncomingLight(0),
    mean(0, 10000),
    var(0, 10000)
    {}

PolytopesFireflyNodeAgent::~PolytopesFireflyNodeAgent() { }

void PolytopesFireflyNodeAgent::init() {
  // Offset the period so as to desynchronize the agents.
  power = (int)randomUniform(0, flashPowerThreshold);
  blind = flash = 0;
  lastIncomingLight = 0;
  mean.reset(FIREFLY_DEFAULT_DETECTION_THRESHOLD);
  var.reset(FIREFLY_DEFAULT_DETECTION_THRESHOLD*FIREFLY_DEFAULT_DETECTION_THRESHOLD);
}

Action* PolytopesFireflyNodeAgent::start(const Observation* observation) {
  init();
  return step(observation);
}
#include <stdio.h>
Action* PolytopesFireflyNodeAgent::step(const Observation* observation) {

  real incomingLight = observation->observations[0];

  // Update statistics.
  mean.update(incomingLight);
  var.update(incomingLight*incomingLight);

  // Flashing.
  if (flash) {
//     printf("***** Flashing *****\n");
    // Turn on LEDs.
    for (int i=0; i<N_LEDS_PER_NODE; i++)
      currentAction[i] = N_ACTIONS_PER_DIM-1;

    flash--; // Decrease flash timer.

    // Stop flashing.
    if (!flash) {
      power = 0;
      blind = blindTime; // refraction period
    }
  }

  // Idle.
  else {

    // Turn off LEDs.
    for (int i=0; i<N_LEDS_PER_NODE; i++)
      currentAction[i] = 0;

    // Increase power in a logarithmic way.
    int inc = 4 * -log((real)(power+1) / (real)(flashPowerThreshold + 1));
    if (inc <= 0) inc = 1;
    power += inc;

    // Not blind: check if we get some light.
    if (!blind) {
      real m = mean.get();
      real v = var.get();
      real stddev = v - m*m;
      stddev = sqrt( abs(stddev) );
      real threshold = mean.get();// + stddev;
      //printf("Fire? %s %f > %f (stddev = %f, mean=%f, var=%f, mean2=%f)\n", (incomingLight > threshold ? "yes" : "no"), incomingLight, threshold, stddev, m, v, m*m);
      if (incomingLight > threshold) {
	  //        printf("Fire: %f > %f (stddev = %f, mean=%f, var=%f, mean2=%f)", incomingLight, threshold, stddev, m, v, m*m);
        power += flashPowerThreshold / 40;
        blind = blindTime; // be blind for some time
      }
    }

    // Decrease blind counter.
    else
      blind--;

    // Start flashing.
    if (power > flashPowerThreshold) {
      power = 0;
      flash = flashTime;
    }
  }

  return &currentAction;
}


// PolytopesFireflyAgent::PolytopesFireflyAgent(int flashPowerThreshold, int blinkTime, int blindTime)
//   : MultiAgent(N_NODES), //FIXME
PolytopesFireflyAgent::PolytopesFireflyAgent(int flashPowerThreshold, int blinkTime, int blindTime, int noAgents)
  : MultiAgent(noAgents), //FIXME
    actionProperties(noAgents*N_LEDS_PER_NODE, N_ACTIONS_PER_DIM),
    currentAction(0),
    agentNodeObservation(FIREFLY_NODE_AGENT_OBSERVATION_DIM) {
  for (int i=0; i<noAgents; i++) // FIXME
    agents[i] = new PolytopesFireflyNodeAgent(flashPowerThreshold, blinkTime, blindTime);
  currentAction = new Action(&actionProperties);
}

PolytopesFireflyAgent::~PolytopesFireflyAgent() {
  delete currentAction;
}
//
//PolytopesFireflyAgent::~PolytopesFireflyAgent() {
//  for (int i=0; i<N_NODES; i++)
//    delete agents[i];
//  free(agents);
//}
//
//void PolytopesFireflyAgent::init() {
//  for (int i=0; i<N_NODES; i++)
//    agents[i]->init();
//}
//
//Action* PolytopesFireflyAgent::start(const Observation* observation) {
//  for (int i=0; i<N_NODES; i++) {
//    PolytopesFireflyNodeAgent* firefly = agents[i];
//    initNodeAgentObservation(i, observation);
//    Action* fireflyAction = firefly->start(&agentNodeObservation);
//    fillMainAction(i, fireflyAction);
//  }
//  return &currentAction;
//}
//
//Action* PolytopesFireflyAgent::step(const Observation* observation) {
//  for (int i=0; i<N_NODES; i++) {
//    PolytopesFireflyNodeAgent* firefly = agents[i];
//    initNodeAgentObservation(i, observation);
//    Action* fireflyAction = firefly->step(&agentNodeObservation);
//    fillMainAction(i, fireflyAction);
//  }
//  return &currentAction;
//}
//
//void PolytopesFireflyAgent::initNodeAgentObservation(int nodeIndex, const Observation* mainObservation) {
//  agentNodeObservation[0] = mainObservation->observations[nodeIndex];
//}

Observation* PolytopesFireflyAgent::extractAgentObservation(int agentIdx, const Observation* observation) {
  agentNodeObservation[0] = observation->observations[agentIdx];
  return &agentNodeObservation;
}

void PolytopesFireflyAgent::appendAgentAction(int agentIdx, const Action* agentAction) {
  int k = agentIdx*N_LEDS_PER_NODE;
  for (int i=0; i<N_LEDS_PER_NODE; i++) {
    currentAction->actions[k++] = agentAction->actions[i];
  }
}

Action* PolytopesFireflyAgent::combineAgentActions() {
  return currentAction;
}
