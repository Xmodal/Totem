/*
 * PolytopesBoosterAgent.h
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

#ifndef POLYTOPESBOOSTERAGENT_H_
#define POLYTOPESBOOSTERAGENT_H_

#include "../common/PolytopesDefs.h"
#include <qualia/core/MultiAgent.h>
#include <qualia/rl/QLearningAgent.h>
#include <qualia/rl/RLObservation.h>
#include <qualia/signal/MovingAverage.h>

const unsigned int BOOSTER_QLEARNING_AGENT_OBSERVATION_DIM = 4;
#define BOOSTER_QLEARNING_AGENT_ACTION_DIM 1 // fire or not
#define BOOSTER_QLEARNING_AGENT_N_ACTIONS_PER_DIM 2 // fire or not

const int BOOSTER_AGENT_OBSERVATION_DIM = 1+N_LEDS_PER_NODE;
#define BOOSTER_AGENT_ACTION_DIM N_LEDS_PER_NODE
#define BOOSTER_AGENT_N_ACTIONS_PER_DIM ACTION_DIM // like for the leds

class PolytopesBoosterAgent : public MultiAgent {
public:
  real energy;
  real timer;
  MovingAverage perceivedLight;
  int localization;
  RLObservation agentObservation;
  Action currentAction;

  static ActionProperties boosterProperties;

  PolytopesBoosterAgent(int localization, QLearningAgent* subAgent);

  virtual Action* start(const Observation* observation);
  virtual Observation* extractAgentObservation(int agentIdx, const Observation* observation);
  virtual void appendAgentAction(int agentIdx, const Action* agentAction);
  virtual Action* combineAgentActions();
//  virtual void init();
//  virtual Action* start(const Observation* observation);
//  virtual Action* step(const Observation* observation);
//  virtual Action* end();
};

class PolytopesBoosterGlobalAgent: public MultiAgent {
public:
  Action currentAction;
  Observation agentObservation;

  real totalReward;

  PolytopesBoosterGlobalAgent(int nAgents, ActionProperties* props);
  virtual ~PolytopesBoosterGlobalAgent();

  virtual Action* start(const Observation* observation);

  virtual Observation* extractAgentObservation(int agentIdx, const Observation* observation);
  virtual void appendAgentAction(int agentIdx, const Action* agentAction);
  virtual Action* combineAgentActions();
};

#endif /* POLYTOPESBOOSTERAGENT_H_ */
