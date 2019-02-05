#include "../common/PolytopesDefs.h"

#include <qualia/learning/NeuralNetwork.h>
#include <qualia/rl/RLQualia.h>
#include <qualia/rl/QLearningAgent.h>
#include <qualia/rl/QLearningEGreedyPolicy.h>
#include <qualia/rl/QLearningEDecreasingPolicy.h>
#include <qualia/rl/QLearningSoftmaxPolicy.h>

#include "PolytopesBoosterAgent.h"

#include "../osc/PolytopesOSC.h"
#include "PolytopesOSCBoosterEnvironment.h"


#include <getopt.h>
#include <iostream>

#include <stdio.h>
#include <vector>

#define N_HIDDEN 8

#define LEARNING_RATE 0.5f
#define DECREASE_CONSTANT 1e-3f
#define WEIGHT_DECAY 1e-6f

//#define USE_SOFTMAX

#ifdef USE_SOFTMAX
#define TEMPERATURE 1.0f
#define EPSILON 0.0f

#else
#define EPSILON 0.01f
#define EPSILON_DECAY 1e-3f
#endif

#define LAMBDA 0.7f
#define GAMMA 0.99f

// #define N_SUB_AGENTS N_NODES
//#define N_SUB_AGENTS 10
//const int SUB_AGENT_LOCS[] = { 2, 4, 5, 14, 17, 22, 24, 27, 30, 42 };

PolytopesBoosterAgent* createSubAgent(int loc);

// PolytopesOSC * osc;

// #if !SIMULATION_MODE
#include <signal.h>
void doneHandler(int s) {
  printf("Done: stopping\n");
//   osc->stop();
  PolytopeOSC::instance().stop();
  exit(0);
}
// #endif

int main(int argc, char** argv) {

  signal(SIGABRT, &doneHandler);
  signal(SIGTERM, &doneHandler);
  signal(SIGINT,  &doneHandler);

  const char * targetip = POLYTOPES_TARGET_IP;
  const char * targetport = POLYTOPES_TARGET_PORT;
  const char * listenport = POLYTOPES_LISTEN_PORT;
  int nonodes = N_NODES;

    int c;
    int digit_optind = 0;
    

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"nonodes", required_argument, 0,  0 },
            {"listenport", no_argument,       0,  0 },
            {"targetport", no_argument,       0,  0 },
            {"targetip",   no_argument,       0,  0 },
            {0,            0,             0,  0 }
        };

       c = getopt_long(argc, argv, "n:l:p:i", long_options, &option_index);
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

	case 'n':
	    nonodes = atoi( optarg );
            break;
        }
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    int noleds = nonodes * N_LEDS_PER_NODE;

    std::cout << "=============================================================" << std::endl;
    std::cout << "BoosterOSC" << std::endl;
    std::cout << "OSC listening port: " << listenport << std::endl;
    std::cout << "OSC target ip: " << targetip << ", target port: " << targetport << std::endl;
    std::cout << "Number of nodes: " << nonodes << std::endl;
    std::cout << "Number of leds: " << noleds << std::endl;
    std::cout << "=============================================================" << std::endl;

  PolytopeOSC::instance().initialize( targetip, targetport, listenport );
  
  if (!PolytopeOSC::instance().isInitialized())
    {
        std::cout << "Could not initialize OSC server" << std::endl;
        return 1;
    } else {
	std::cout << "OSC server is initialized, listening at: " << listenport << ", sending to: " << targetip << ":" << targetport << std::endl;
    }
      
  PolytopeOSC::instance().addMethods();
  PolytopeOSC::instance().start();

  PolytopeOSC::instance().initNodeData( nonodes );

  PolytopesOSCBoosterEnvironment env;
// #endif

  int ACTION_DIM      = noleds;
  int N_SUB_AGENTS    = nonodes;

  int * SUB_AGENT_LOCS = (int*) malloc( N_SUB_AGENTS * sizeof( int ) );
//   int SUB_AGENT_LOCS[N_NODES];
  for (int i=0; i<N_SUB_AGENTS; i++)
    SUB_AGENT_LOCS[i] = i;

  
  ActionProperties props(ACTION_DIM, N_ACTIONS_PER_DIM);
  PolytopesBoosterGlobalAgent agent(N_SUB_AGENTS, &props);

  for (int i=0; i<N_SUB_AGENTS; i++)
    agent.agents[i] = createSubAgent(SUB_AGENT_LOCS[i]);

  Qualia qualia(&agent, &env);
  qualia.init();
  qualia.start();

#define EPISODE_N_STEPS 100

  bool quit = false;
  int t=0;
  while (!quit) {
//     printf("Episode # %d\n", t);
    for (int i=0; i<EPISODE_N_STEPS; i++) {
      qualia.step();
      if (PolytopeOSC::instance().hasQuit()) {
        quit = true;
        break;
      }
    }
    QLearningAgent* a = (QLearningAgent*)((PolytopesBoosterAgent*)agent.agents[0])->agents[0];
    t++;
//     printf("Total reward = %f (epsilon=%f, lr=%f)\n", agent.totalReward / N_SUB_AGENTS / EPISODE_N_STEPS / t,
//            ((QLearningEDecreasingPolicy*)a->policy)->epsilon / ((QLearningEDecreasingPolicy*)a->policy)->_epsilonDiv,
//            ((NeuralNetwork*)a->qFunction->function)->getCurrentLearningRate());
  }

  // Free.
  for (int i=0; i<N_SUB_AGENTS; i++) {
    QLearningAgent* a = (QLearningAgent*)((PolytopesBoosterAgent*)agent.agents[i])->agents[0];
    delete a->qFunction->function;
    delete a->qFunction;
    delete a->policy;
    delete a;
    delete agent.agents[i];
  }

  return 0;
}

ActionProperties boosterQLearningAgentActionProps(BOOSTER_QLEARNING_AGENT_ACTION_DIM, BOOSTER_QLEARNING_AGENT_N_ACTIONS_PER_DIM);
PolytopesBoosterAgent* createSubAgent(int loc) {
  return new PolytopesBoosterAgent(loc,
           new QLearningAgent(
               new QFunction(
                   new NeuralNetwork(
                         BOOSTER_QLEARNING_AGENT_OBSERVATION_DIM + BOOSTER_QLEARNING_AGENT_ACTION_DIM,
                         N_HIDDEN, 1, LEARNING_RATE, DECREASE_CONSTANT, WEIGHT_DECAY),
                   BOOSTER_QLEARNING_AGENT_OBSERVATION_DIM, &boosterQLearningAgentActionProps),
#ifdef USE_SOFTMAX
               new QLearningSoftmaxPolicy(TEMPERATURE, EPSILON),
#else
               new QLearningEDecreasingPolicy(EPSILON, EPSILON_DECAY),
#endif
               BOOSTER_QLEARNING_AGENT_OBSERVATION_DIM,
               &boosterQLearningAgentActionProps,
               LAMBDA, GAMMA,
               false));
}
