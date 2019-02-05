/*
 * PolytopesBoosterAgent.cpp
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

#include "PolytopesBoosterAgent.h"
#include <assert.h>

#include <stdio.h>

ActionProperties PolytopesBoosterAgent::boosterProperties(BOOSTER_AGENT_ACTION_DIM, BOOSTER_QLEARNING_AGENT_N_ACTIONS_PER_DIM);

PolytopesBoosterAgent::PolytopesBoosterAgent(int localization_, QLearningAgent* subAgent_)
: MultiAgent(1),
  energy(0), timer(0),
  perceivedLight(0, 100),
  localization(localization_),
  agentObservation(BOOSTER_QLEARNING_AGENT_OBSERVATION_DIM), // energy + timer + light + leds
  currentAction(&boosterProperties) {
  agents[0] = subAgent_;
}

Action* PolytopesBoosterAgent::start(const Observation* observation) {
  perceivedLight.reset(observation->observations[0]);
  return MultiAgent::start(observation);
}

#include <stdio.h>
Observation* PolytopesBoosterAgent::extractAgentObservation(int agentIdx, const Observation* observation) {
  assert( agentIdx == 0 );

  int k=0;

  // First element is the incoming light / second one is the trace of the perceived light.
  real light = observation->observations[0];
  agentObservation[k++] = light;
  agentObservation[k++] = perceivedLight.get();

  // Add other info.
  agentObservation[k++] = energy/ACTION_MAX;
  agentObservation[k++] = timer/100;

  // Assign reward from second elements (LEDs value).
  real reward = 0;

  // Rewarded by its own light!
  for (int i=0; i<N_LEDS_PER_NODE; i++)
    reward += observation->observations[i+1] / 3.0f;

  if (reward > 0) {
    if (reward > 0.02f) { // ie. at least boost > 5
      reward = reward*reward*1000;
    }
    else
      reward = -reward*10; // punish bad bursts
//     printf("Reward: %f (boost=%f %f %f, light=%f)\n", reward, observation->observations[1], observation->observations[2], observation->observations[3], light);
  }

  agentObservation.reward = reward;

  perceivedLight.update(light);

  if (timer > 30) { // you cannot light-recharge for a while after emitting
    energy += light*10;                        // light gives a lot of energy!
  }
  energy += 0.1f;                            // time gives some energy
  //printf("%f %f\n", energy, observation->observations[0]);
  timer++;

  return &agentObservation;
}

void PolytopesBoosterAgent::appendAgentAction(int agentIdx, const Action* agentAction) {
  assert( agentIdx == 0 );

  if (agentAction->actions[0] != 0) { // boost!

//#if SIMULATION_MODE
//    int boost = (int) ( energy );
//    //printf("BOOST! %d (t=%f e=%f)\n", boost, timer, energy);
//    boost *= N_LEDS_PER_NODE;
//    for (int i=0; i<N_LEDS_PER_NODE; i++) {
//      int action = (boost >= ACTION_MAX ? ACTION_MAX : boost);
//      boost -= action;
//      boost = max(boost, 0);
//      currentAction[i] = action;
//    }
//#else
    int boost = (int) ( energy );
    boost = constrain(boost, 1, ACTION_MAX);
    //printf("BOOST! %d (t=%f e=%f)\n", boost, timer, energy);
    for (int i=0; i<N_LEDS_PER_NODE; i++)
      currentAction[i] = boost;
//#endif
    //printf("%d %d %d\n", currentAction[0], currentAction[1], currentAction[2]);

    // Clear energy and reset timer.
    energy = 0;
    timer = 0;
  } else {
    for (int i=0; i<N_LEDS_PER_NODE; i++)
      currentAction[i] = 0;
  }
}

Action* PolytopesBoosterAgent::combineAgentActions() {
  return &currentAction;
}


///////////////////////////

PolytopesBoosterGlobalAgent::PolytopesBoosterGlobalAgent(int nAgents, ActionProperties* props)
  : MultiAgent(nAgents),
    currentAction(props), agentObservation(BOOSTER_AGENT_OBSERVATION_DIM), totalReward(0) {
}

PolytopesBoosterGlobalAgent::~PolytopesBoosterGlobalAgent() {}

Action* PolytopesBoosterGlobalAgent::start(const Observation* observation) {
  totalReward = 0;
  return MultiAgent::start(observation);
}

Observation* PolytopesBoosterGlobalAgent::extractAgentObservation(int agentIdx, const Observation* observation) {
  // 1 light value and 3 led values
  PolytopesBoosterAgent* subAgent = (PolytopesBoosterAgent*)agents[agentIdx];

  int agentLoc = subAgent->localization;

  int k=0;
  agentObservation[k++] = observation->observations[agentLoc]; // incoming light value

  // led values
  int l = N_NODES + agentLoc*N_LEDS_PER_NODE;
  for (int i=0; i<N_LEDS_PER_NODE; i++)
    agentObservation[k++] = observation->observations[l++];
  //if (agentObservation[1] > 0 || agentObservation[2] || agentObservation[3])
  //  printf("Agent is boosting! %f\n", agentIdx, agentObservation[1]);

  assert( (int)agentObservation._dim == k );

  totalReward += subAgent->agentObservation.reward;

  return &agentObservation;
}

void PolytopesBoosterGlobalAgent::appendAgentAction(int agentIdx, const Action* agentAction) {
  int k;

  PolytopesBoosterAgent* subAgent = (PolytopesBoosterAgent*)agents[agentIdx];
  int agentLoc = subAgent->localization;

  k = agentLoc*N_LEDS_PER_NODE;

  for (int j=0; j<N_LEDS_PER_NODE; j++) {
      currentAction[k++] = agentAction->actions[j];
  }
}

Action* PolytopesBoosterGlobalAgent::combineAgentActions() {
  return &currentAction;
}

