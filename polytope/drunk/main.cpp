#include "PolytopesDrunkAgent.h"
#include <qualia/core/Qualia.h>

// #if SIMULATION_MODE
// #include <qualia/plugins/mapper/MapperBasicEnvironment.h>
// #define QUALIA_DEVICE_NAME "qualia"
// #define PEER_DEVICE_NAME "/polytopes.1"
// #else
// #include "common/PolytopesUpdateClient.h"
// #include "PolytopesDataNetworkDrunkEnvironment.h"
#include "PolytopesOSCDrunkEnvironment.h"

#include "../common/PolytopesDefs.h"
#include "../osc/PolytopesOSC.h"
// #endif

#define N_HIDDEN 3
#define DIM_OBSERVATIONS 1
#define DIM_ACTIONS 1

#include <getopt.h>
#include <iostream>
#include <stdio.h>

#include "../osc/oscin.h"

bool hasNewParameters = false;
float newparameters[5];

static int drunk_parameters_handler( handlerArgs )
{
  int size = argc;
  if ( size > 5 ){ size = 5; }
  for ( int i=0; i<size; i++ ){
      newparameters[i] = argv[i]->f;
  }
  hasNewParameters = true;
//   world->queueChaser( parameters );
  return 0;
}

#include <signal.h>
void doneHandler(int s) {
    printf("Done: stopping\n");
//   osc->stop();
  PolytopeOSC::instance().stop();
// printf("Done: deregistering all\n");
//   PolytopesNodesClient::instance().cleanup();
  exit(0);
}

int main(int argc, char** argv) {
  PolytopesDrunkAgent agent(POLYTOPES_DRUNK_MAX_LED_INC);
  
  signal(SIGABRT, &doneHandler);
  signal(SIGTERM, &doneHandler);
  signal(SIGINT,  &doneHandler);

//   int arg=0;
//   if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
//     printf("Usage: %s [ip=%s] [port=%s] [id=%s]\n",
//            argv[0], POLYTOPES_DATANETWORK_IP, POLYTOPES_DATANETWORK_NODES_CLIENT_PORT, POLYTOPES_DATANETWORK_NODES_CLIENT_ID);
//     exit(0);
//   }
//   const char* ip   =      ( ++arg < argc ? argv[arg] : POLYTOPES_DATANETWORK_IP );
//   const char* port =      ( ++arg < argc ? argv[arg] : POLYTOPES_DATANETWORK_NODES_CLIENT_PORT );
//   const char* clientId =  ( ++arg < argc ? argv[arg] : POLYTOPES_DATANETWORK_NODES_CLIENT_ID );
//   PolytopesNodesClient::setup(ip, port, clientId);
//   PolytopeOSC::instance(); // this will start the network

  const char * targetip = POLYTOPES_TARGET_IP;
  const char * targetport = POLYTOPES_TARGET_PORT;
  const char * listenport = POLYTOPES_LISTEN_PORT;
  int nonodes = N_NODES;
  int nolines = N_LINES;
  int nonodesperline = N_NODES_PER_LINE;
  

    int c;
    int digit_optind = 0;
    

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
	    {"nolines", required_argument, 0,  0 },
	    {"nonodesperline", required_argument, 0,  0 },
            {"nonodes", required_argument, 0,  0 },
            {"listenport", no_argument,       0,  0 },
            {"targetport", no_argument,       0,  0 },
            {"targetip",   no_argument,       0,  0 },
            {0,            0,             0,  0 }
        };

       c = getopt_long(argc, argv, "N:M:n:l:p:i", long_options, &option_index);
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

    int noleds = nonodes * N_LEDS_PER_NODE;

    std::cout << "=============================================================" << std::endl;
    std::cout << "DrunkOSC" << std::endl;
    std::cout << "OSC listening port: " << listenport << std::endl;
    std::cout << "OSC target ip: " << targetip << ", target port: " << targetport << std::endl;
    std::cout << "Number of nodes: " << nonodes << std::endl;
    std::cout << "Number of lines: " << nolines << std::endl;
    std::cout << "Number of nodes per line: " << nonodesperline << std::endl;
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

  PolytopeOSC::instance().addMethod( "/qualia/parameters/drunk", "fffff", drunk_parameters_handler, NULL );
  PolytopeOSC::instance().addMethods();
  PolytopeOSC::instance().start();

//   PolytopeOSC::instance().initNodeData( nonodes );  
  
  PolytopesOSCDrunkEnvironment env;
  
  agent.initValues( nolines, nonodes, noleds, nonodesperline );

  env.setNoLeds( noleds );
  
  Qualia qualia(&agent, &env);
  
  qualia.init();
  qualia.start();

  while (!PolytopeOSC::instance().hasQuit()) {
    if ( hasNewParameters ){
      agent.updateParameters( newparameters );
      hasNewParameters = false;
    }
    qualia.step();

//     printf("Current agent action: %d\n", (int)agent.currentAction->conflated());
//    printf("Current environment observation: %f %f\n", (double)env.currentObservation.observations[0], (double)env.currentObservation.observations[1]);
  }

  return 0;
}
