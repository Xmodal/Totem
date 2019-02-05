/*
 * PolytopesChaserGridWorld.cpp
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

#include "PolytopesChaserGridWorld.h"

#include <stdio.h>

PolytopesChaserGridWorld::ChaserGridChaser& PolytopesChaserGridWorld::addChaser(int id, int line, int column, Qualia* qualia) {
  ChaserMap::iterator it = chasers.find(id);
  if (it == chasers.end()) {
    chasers[id] = ChaserGridChaser(line, column, qualia);
    return chasers[id];
  } else
    return it->second;
}

PolytopesChaserGridWorld::ChaserGridChaser PolytopesChaserGridWorld::removeChaser(int id) {
  ChaserMap::iterator it = chasers.find(id);
  if (it != chasers.end()) {
    chasers.erase(it);
    return it->second;
  } else
    return ChaserGridChaser();  
}

// void PolytopesChaserGridWorld::checkQueuedChasers(){
//   if ( hasChaserToAdd ){
//       int id = chaserToAdd[0];
//       
//       PolytopesChaserGridWorld::ChaserGridChaser& chaser = addChaser( id, this, (int)chaserToAdd[1], (int)chaserToAdd[2], (real)chaserToAdd[3], (real)chaserToAdd[4], (real)chaserToAdd[5]);
//       printf("!!!!!!! Got chaser: %d %d %d %f %f %f !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
//           id, (int)chaserToAdd[1], (int)chaserToAdd[2], (real)chaserToAdd[3], (real)chaserToAdd[4], (real)chaserToAdd[5]);
//       assert(chaser.qualia);
//       chaser.qualia->init();
//       chaser.qualia->start();
//       
//       hasChaserToAdd = false;
//     }
//     
//     if ( chaserToDelete != -1) {
//       removeChaser(chaserToDelete, this);      
// //       PolytopesChaserGridWorld::ChaserGridChaser chaser = removeChaser(id);
// //       cleanupChaser(chaser);
// 
//       printf("!!!!!!! Remove chaser: %d !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", chaserToDelete );
//       chaserToDelete = -1;
//     }
// }
// 
// void PolytopesChaserGridWorld::queueChaser( int chaserparameters[5] ){
//   // id ,line, col, rew1, rew2, rew3
//   for ( int i=0; i<5; i++ ){
//     chaserToAdd[i] = chaserparameters[i];
//   }
// }
// 
// 
// void PolytopesChaserGridWorld::queueDeleteChaser( int id ){
//   chaserToDelete = id;
// }


void PolytopesChaserGridWorld::init() {
  
//   hasChaserToAdd = false;
//   chaserToDelete = -1;
  
  for (ChaserMap::iterator it = chasers.begin(); it != chasers.end(); ++it)
    it->second.qualia->init();
}

void PolytopesChaserGridWorld::start() {
  for (ChaserMap::iterator it = chasers.begin(); it != chasers.end(); ++it)
    it->second.qualia->start();
}

void PolytopesChaserGridWorld::step() {
  for (ChaserMap::iterator it = chasers.begin(); it != chasers.end(); ++it)
    it->second.column = it->second.nextColumn;
  for (ChaserMap::iterator it = chasers.begin(); it != chasers.end(); ++it)
    it->second.qualia->step();
}

//void PolytopesChaserGridWorld::init() {
//  for (std::vector<ChaserGridChaser>::iterator it = chasers.begin(); it != chasers.end(); ++it)
//    it->agent->init();
//}
//
//void PolytopesChaserGridWorld::step() {
//  int i=0;
//  int obs=0;
//  for (std::vector<ChaserGridChaser>::iterator it = chasers.begin(); it != chasers.end(); ++it, ++i) {
//
//    // Step the agent.
//    lastAction = it->agent->step(&agentObservation);
//  }
//}

PolytopesChaserEnvironment::PolytopesChaserEnvironment(PolytopesChaserGridWorld* world_, real rewardOnTouch_, real rewardOnMove_, real rewardOnStay_)
  : world(world_), rewardOnTouch(rewardOnTouch_), rewardOnMove(rewardOnMove_), rewardOnStay(rewardOnStay_), currentObservation(CHASER_OBSERVATION_DIM), chaser(0) {}

void PolytopesChaserEnvironment::init() {
  // Find agent index.
  for (PolytopesChaserGridWorld::ChaserMap::iterator it = world->chasers.begin();
      it != world->chasers.end(); ++it) {
    if (it->second.qualia->environment == this) {
      chaser = &(it->second);
      break;
    }
  }
}

Observation* PolytopesChaserEnvironment::start() {
  return moveChaser(0, CHASER_N_ACTIONS[0] /* dummy */);
}

Observation* PolytopesChaserEnvironment::step(const Action* action) {
  int maxMove = (int) ( 0.5* ((real)action->properties->nActions(0) - 1 ) + 0.1);
  return moveChaser( action->actions[0] - maxMove, maxMove );
}

Observation* PolytopesChaserEnvironment::moveChaser(int move, int maxMove) {
  // Accomplish last action.
  int line   = chaser->line;
  int column = chaser->column;

  // Do the action.
  column += move;
  while (column < 0) column += world->noledsperline;
  while (column >= world->noledsperline) column -= world->noledsperline;

  // Get the observation back for the agent.
  int closestBack  = world->noledsperline;
  int closestFront = world->noledsperline;
  for (PolytopesChaserGridWorld::ChaserMap::iterator it = world->chasers.begin();
      it != world->chasers.end(); ++it) {
    if (chaser != &(it->second) && line == it->second.line) {
      closestBack  = std::min(closestBack,
                              (column - it->second.column + world->noledsperline) % world->noledsperline);
      closestFront = std::min(closestFront,
                              (it->second.column - column + world->noledsperline) % world->noledsperline);
    }
  }

  // Fill the observation.
  currentObservation[0] = (real)closestBack  / (real)world->noledsperline;
  currentObservation[1] = (real)closestFront / (real)world->noledsperline;

  // Get reward.
  real reward = 0;

  // Check touch.
  if (closestBack == 0 || closestFront == 0)
    reward += rewardOnTouch; // HIT

  // Check move.
  reward += (move / (real)maxMove) * rewardOnMove;

  // Check stay.
  reward += (move == 0 ? rewardOnStay : -rewardOnStay);

  currentObservation.reward = reward;

  // Don't move yet (parallel processing).
  chaser->nextColumn = column;

  return &currentObservation;
}
