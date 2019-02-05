/*
 * PolytopesChaserGridWorld.h
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

#ifndef POLYTOPESCHASERGRIDWORLD_H_
#define POLYTOPESCHASERGRIDWORLD_H_

#include "../common/PolytopesDefs.h"
#include <qualia/core/Agent.h>
#include <qualia/core/Qualia.h>
#include <qualia/rl/RLObservation.h>
#include <qualia/util/random.h>
#include <string.h>

#include <map>

#define CHASER_OBSERVATION_DIM 2
#define CHASER_ACTION_DIM      1
const unsigned int CHASER_N_ACTIONS[] = { 3 };


class PolytopesChaserGridWorld {
public:
  struct ChaserGridChaser {
    ChaserGridChaser(int l=0, int c=0, Qualia* q=0) : line(l), column(c), nextColumn(c), qualia(q) {}
    int line;
    int column;
    int nextColumn;
    Qualia* qualia;
  };
  typedef std::map<int, ChaserGridChaser> ChaserMap;
  ChaserMap chasers;

  //Action currentAction;
  //RLObservation agentObservation;
  
//   void queueChaser( int chaserparameters[5] ); // line, col, rew1, rew2, rew3
//   void queueDeleteChaser( int id );
//   
//   void checkQueuedChasers();

  bool chaserExists(int id) const {
    ChaserMap::const_iterator it = chasers.find(id);
    return (it != chasers.end());
 }

  ChaserGridChaser& addChaser(int id, int line, int column, Qualia* qualia);
  ChaserGridChaser removeChaser(int id);

  void init();
  void start();
  void step();
  
  int noledsperline;
  
//  void init();
//  void step();
};

class PolytopesChaserEnvironment : public Environment {
public:
  PolytopesChaserGridWorld* world;
  real rewardOnTouch;
  real rewardOnMove;
  real rewardOnStay;

  // Internal use.
  RLObservation currentObservation;
  PolytopesChaserGridWorld::ChaserGridChaser* chaser;

  PolytopesChaserEnvironment(PolytopesChaserGridWorld* world,
      real rewardOnTouch, real rewardOnMove, real rewardOnStay=0);
  virtual void init();
  virtual Observation* start();
  virtual Observation* step(const Action* action);

  Observation* moveChaser(int move, int maxMove);
    
};

#endif /* POLYTOPESCHASERGRIDWORLD_H_ */
