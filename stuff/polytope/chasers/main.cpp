#include "../common/PolytopesDefs.h"

#include <qualia/learning/NeuralNetwork.h>

#include <qualia/rl/RLQualia.h>
#include <qualia/rl/QLearningAgent.h>
#include <qualia/rl/QLearningEGreedyPolicy.h>
#include <qualia/rl/QLearningSoftmaxPolicy.h>
#include <qualia/rl/QLearningEDecreasingPolicy.h>

#include "PolytopesChaserGridWorld.h"
#include "../osc/PolytopesOSC.h"
#include "PolytopesOSCChaserEnvironment.h"

#include <getopt.h>
#include <iostream>

#include <stdio.h>
#include <vector>
#include <assert.h>

#define N_HIDDEN 3

#define LEARNING_RATE 0.1f
#define DECREASE_CONSTANT 1e-6f
#define WEIGHT_DECAY 1e-6f

#define EPSILON 0.1f
#define EPSILON_DECAY 1e-5f

#define LAMBDA 0.3f
#define GAMMA 0.5f


#include "../osc/oscin.h"

int chaserToDelete = -1;
bool hasChaserToAdd = false;
int chaserToAdd[6];

static int add_chaser_handler( handlerArgs )
{
//   PolytopeOSC* osc = ( PolytopeOSC* ) user_data;
//   PolytopesChaserGridWorld* world = ( PolytopesChaserGridWorld* ) user_data;
//   int parameters[6];
  int size = argc;
  if ( size > 6 ){ size = 6; }
  for ( int i=0; i<size; i++ ){
      chaserToAdd[i] = argv[i]->i;
  }
  hasChaserToAdd = true;
//   world->queueChaser( parameters );
  return 0;
}

static int del_chaser_handler( handlerArgs )
{
//   PolytopeOSC* osc = ( PolytopeOSC* ) user_data;
//   PolytopesChaserGridWorld* world = ( PolytopesChaserGridWorld* ) user_data;
//   world->queueDeleteChaser( argv[0]->i );
  chaserToDelete = argv[0]->i;
  return 0;
}


PolytopesChaserGridWorld::ChaserGridChaser& addChaser(int id, PolytopesChaserGridWorld* world, int line, int column,
    real rewardOnTouch, real rewardOnMove, real rewardOnStay=0);

void removeChaser(int id, PolytopesChaserGridWorld* world);

void cleanupChaser(PolytopesChaserGridWorld::ChaserGridChaser& chaser);

#include <signal.h>
void doneHandler(int s) {
  printf("Done: stopping\n");
  PolytopeOSC::instance().stop();
  exit(0);
}

int nolines = N_LINES;
int nonodesperline = N_NODES_PER_LINE;
int noledsperline = N_LEDS_PER_LINE;

int main(int argc, char** argv) {
  signal(SIGABRT, &doneHandler);
  signal(SIGTERM, &doneHandler);
  signal(SIGINT,  &doneHandler);

  const char * targetip = POLYTOPES_TARGET_IP;
  const char * targetport = POLYTOPES_TARGET_PORT;
  const char * listenport = POLYTOPES_LISTEN_PORT;
//   int nonodes = N_NODES;
  // default values:

    int c;
    int digit_optind = 0;
    

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
//             {"nonodes", required_argument, 0,  0 },
	    {"nolines", required_argument, 0,  0 },
	    {"nonodesperline", required_argument, 0,  0 },
            {"listenport", no_argument,       0,  0 },
            {"targetport", no_argument,       0,  0 },
            {"targetip",   no_argument,       0,  0 },
            {0,            0,             0,  0 }
        };

       c = getopt_long(argc, argv, "N:M:l:p:i", long_options, &option_index);
       if (c == -1)
            break;

       switch (c) {
        case 0:
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

	case 'l':
	    listenport = optarg;
            break;

	case 'p':
	    targetport = optarg;
            break;

	case 'i':
	    targetip = optarg;
            break;

// 	case 'n':
// 	    nonodes = atoi( optarg );
//             break;

	case 'N':
	    nolines = atoi( optarg );
            break;

	case 'M':
	    nonodesperline = atoi( optarg );
            break;

      }
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    noledsperline = nonodesperline * N_LEDS_PER_NODE;
    int noleds = noledsperline * nolines;

    std::cout << "=============================================================" << std::endl;
    std::cout << "ChaserOSC" << std::endl;
    std::cout << "OSC listening port: " << listenport << std::endl;
    std::cout << "OSC target ip: " << targetip << ", target port: " << targetport << std::endl;
//     std::cout << "Number of nodes: " << nonodes << std::endl;
//     std::cout << "Number of leds: " << noleds << std::endl;
    std::cout << "Number of lines: " << nolines << std::endl;
    std::cout << "Number of nodes per line: " << nonodesperline << std::endl;
    std::cout << "=============================================================" << std::endl;

  PolytopeOSC::instance().initialize( targetip, targetport, listenport );
  
  if (!PolytopeOSC::instance().isInitialized())
    {
        std::cout << "Could not initialize OSC server" << std::endl;
        return 1;
    } else {
	std::cout << "OSC server is initialized, listening at: " << listenport << ", sending to: " << targetip << ":" << targetport << std::endl;
    }

    
  PolytopesOSCChaserEnvironment env;
  PolytopesChaserGridWorld world;

  PolytopeOSC::instance().addMethod( "/qualia/add/chaser", "iiiiii", add_chaser_handler, NULL );
  PolytopeOSC::instance().addMethod( "/qualia/remove/chaser", "i", del_chaser_handler, NULL );
  PolytopeOSC::instance().addMethods();
  PolytopeOSC::instance().start();

//   PolytopeOSC::instance().initNodeData( nonodes );
  
  ActionProperties props(noleds, N_ACTIONS_PER_DIM);
  Action ledAction(&props);

// //  for (int i=0; i<N_LINES; i++) {
// //    addChaser(&world, i, 3, -50, 0, 2); // evader
// //    addChaser(&world, i, 8,  10, 3, 0); // chaser
// //  }
// //

// #if SIMULATION_MODE
//   int id = 0;
//   addChaser(id++, &world, 1, 3, -50, 0, 5); // lazy evader
//   addChaser(id++, &world, 1, 8, 10,  3, 0); // motivated chaser
// 
//   addChaser(id++, &world, 4, 1, -10,  1); // evading sprinter
//   addChaser(id++, &world, 4, 9, -10, -1); // evading backspinner
// 
//   addChaser(id++, &world, 7, 3, 0,  10); // sprinter
//   addChaser(id++, &world, 7, 8, 0, -10); // backspinner
// 
//   addChaser(id++, &world, 10, 3, 10, 3); // dancers ...
//   addChaser(id++, &world, 10, 8, 10, 3);
// #endif

  env.init();
  env.start();
  world.init();
  world.start();
  
  env.setNoLeds( noleds );
  world.noledsperline = noledsperline;
  
  int nChasersPerLine[nolines];
  memset(nChasersPerLine, 0, nolines*sizeof(int));
  for (PolytopesChaserGridWorld::ChaserMap::iterator it = world.chasers.begin();
      it != world.chasers.end(); ++it)
    nChasersPerLine[it->second.line]++;

  unsigned int iter=0;
  while (!PolytopeOSC::instance().hasQuit()) {

    PolytopeOSC& osc = PolytopeOSC::instance();
    
//     world.checkQueuedChasers();
    // Check if we were asked for new agents or to delete some of them.
//     if (client.hasNewData(READ_CREATE_AGENT)) {
    if ( hasChaserToAdd ) {
//       float data[READ_CREATE_AGENT_SIZE];
//       client.readData(READ_CREATE_AGENT, &data);
      int id = chaserToAdd[0];
      
      if (!world.chaserExists(id)) {
	PolytopesChaserGridWorld::ChaserGridChaser& chaser = addChaser( id, &world, chaserToAdd[1], chaserToAdd[2], (real)chaserToAdd[3], (real)chaserToAdd[4], (real)chaserToAdd[5]);
// 	printf("!!!!!!! Got chaser: %d %d %d %f %f %f !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
// 	    id, chaserToAdd[1], chaserToAdd[2], (real)chaserToAdd[3], (real)chaserToAdd[4], (real)chaserToAdd[5]);
	assert(chaser.qualia);
	chaser.qualia->init();
	chaser.qualia->start();
      }
      
      hasChaserToAdd = false;
    }
    if ( chaserToDelete != -1 ) {
//       float id;
//       client.readData(READ_DELETE_AGENT, &id);
      if ( world.chaserExists(chaserToDelete) ) {
	removeChaser(chaserToDelete, &world);
// 	printf("!!!!!!! Remove chaser: %d !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", chaserToDelete);
      }
      chaserToDelete = -1;
    }

    // Do one step.
    world.step();

    // Init all leds to 0.
    for (int i=0; i<noleds; i++)
      ledAction[i] = 0;

    // Update led values according to position of each chaser.
    for (PolytopesChaserGridWorld::ChaserMap::iterator it = world.chasers.begin();
        it != world.chasers.end(); ++it) {
      int ledIndex = it->second.line * noledsperline + it->second.column;
      ledIndex = constrain(ledIndex, 0, noleds-1); // XXX just to be sure
      ledAction[ledIndex] += 128;
      ledAction[ledIndex] = constrain(ledAction[ledIndex], 0, ledAction.properties->nActions(ledIndex)-1);
      
      //int inc = (int) ( ledAction.nActions[ledIndex] / (0.001f + nChasersPerLine[it->second.line]) ) + 1;
//       int inc = 128;
      //printf("Inc: %d (%d=> %d %d)\n", inc, it->second.line, ledIndex, nChasersPerLine[it->line]);
//       ledAction[ledIndex] = std::min(ledAction[ledIndex] + inc, ledAction.properties->nActions(ledIndex)-1);
    }

    // Send led values.
    env.step(&ledAction); // ignore observations

//     if ( (iter % 10) == 0)
//       printf("t=%d\n", iter);

    iter ++;
  } // end of loop

  // Free.
  for (PolytopesChaserGridWorld::ChaserMap::iterator it = world.chasers.begin();
      it != world.chasers.end(); ++it) {
    cleanupChaser(it->second);
  }

  return 0;
}

ActionProperties chaserActionProperties(CHASER_ACTION_DIM, CHASER_N_ACTIONS);

PolytopesChaserGridWorld::ChaserGridChaser& addChaser(int id, PolytopesChaserGridWorld* world, int line, int column,
    real rewardOnTouch, real rewardOnMove, real rewardOnStay) {

  line = constrain(line, 0, nolines-1);
  column = constrain(column, 0, noledsperline-1);

  return world->addChaser(id, line, column,
                  new RLQualia(
                      new QLearningAgent(
                          new QFunction(
                              new NeuralNetwork(
                                  CHASER_OBSERVATION_DIM + CHASER_ACTION_DIM,
                                  N_HIDDEN, 1, LEARNING_RATE, DECREASE_CONSTANT, WEIGHT_DECAY),
                                  CHASER_OBSERVATION_DIM, &chaserActionProperties),
                          new QLearningEDecreasingPolicy(EPSILON, EPSILON_DECAY),
                          CHASER_OBSERVATION_DIM,
                          &chaserActionProperties,
                          LAMBDA, GAMMA,
                          false),
                      new PolytopesChaserEnvironment(world, rewardOnTouch, rewardOnMove, rewardOnStay)));
}

void removeChaser(int id, PolytopesChaserGridWorld* world) {
  PolytopesChaserGridWorld::ChaserGridChaser chaser = world->removeChaser(id);
  cleanupChaser(chaser);
}

void cleanupChaser(PolytopesChaserGridWorld::ChaserGridChaser& chaser) {
  Qualia* qualia = chaser.qualia;
  if (qualia) {
    QLearningAgent* agent = (QLearningAgent*)qualia->agent;
    delete agent->qFunction->function;
    delete agent->qFunction;
    delete agent->policy;
    delete agent;
    delete qualia->environment;
    delete qualia;
  }
}
