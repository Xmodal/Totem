/*
 * PolytopesFireflyAgent.h
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

#ifndef POLYTOPESFIREFLYAGENT_H_
#define POLYTOPESFIREFLYAGENT_H_

#include "../common/PolytopesDefs.h"
#include <qualia/core/Agent.h>
#include <qualia/core/MultiAgent.h>
#include <qualia/signal/MovingAverage.h>

#include <assert.h>

#define FIREFLY_NODE_AGENT_OBSERVATION_DIM 1

//#define FIREFLY_NODE_AGENT_DEFAULT_CYCLE_TIME 600
//#define FIREFLY_NODE_AGENT_DEFAULT_BLINK_TIME 20
//#define FIREFLY_NODE_AGENT_DEFAULT_BLIND_TIME 100
//#define FIREFLY_NODE_AGENT_DEFAULT_DETECTION_TIME_INC 75
//#define FIREFLY_NODE_AGENT_DEFAULT_DETECTION_THRESHOLD 0.05f

#define FIREFLY_DEFAULT_FLASH_POWER_THRESHOLD 1200
#define FIREFLY_DEFAULT_FLASH_TIME 1
#define FIREFLY_DEFAULT_BLIND_TIME 20
//#define FIREFLY_DEFAULT_DETECTION_THRESHOLD 0.25f
#define FIREFLY_DEFAULT_DETECTION_THRESHOLD 0.07f

extern ActionProperties fireflyProperties;

class PolytopesFireflyNodeAgent : public Agent {
public:
  Action currentAction;

//   static ActionProperties fireflyProperties;

  int power;
  int blind;
  int flash;

  int flashPowerThreshold;
  int flashTime;
  int blindTime;

  real lastIncomingLight;
  MovingAverage mean;
  MovingAverage var;

  PolytopesFireflyNodeAgent(int flashPowerThreshold=FIREFLY_DEFAULT_FLASH_POWER_THRESHOLD,
                            int flashTime=FIREFLY_DEFAULT_FLASH_TIME,
                            int blindTime=FIREFLY_DEFAULT_BLIND_TIME);
  virtual ~PolytopesFireflyNodeAgent();

  virtual void init();
  virtual Action* start(const Observation* observation);
  virtual Action* step(const Observation* observation);
};

class PolytopesFireflyAgent : public MultiAgent {
public:
  Action* currentAction;
  ActionProperties actionProperties;

  Observation agentNodeObservation;

  PolytopesFireflyAgent(int flashPowerThreshold=FIREFLY_DEFAULT_FLASH_POWER_THRESHOLD,
                        int blinkTime=FIREFLY_DEFAULT_FLASH_TIME,
                        int blindTime=FIREFLY_DEFAULT_BLIND_TIME,
			int noAgents = N_NODES
 		      );
  virtual ~PolytopesFireflyAgent();

  virtual Observation* extractAgentObservation(int agentIdx, const Observation* observation);
  virtual void appendAgentAction(int agentIdx, const Action* agentAction);
  virtual Action* combineAgentActions();
};


#endif /* POLYTOPESFIREFLYAGENT_H_ */
