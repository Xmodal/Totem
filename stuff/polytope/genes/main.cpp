#include <qualia/core/Qualia.h>

#include "GeneticWorld.h"

// #include "common/PolytopesUpdateClient.h"
#include "../common/PolytopesDefs.h"
#include "../osc/PolytopesOSC.h"

#include <stdio.h>

#include <getopt.h>
#include <iostream>

#include <signal.h>
void doneHandler(int s) {
  printf("Done: stopping\n");
  PolytopeOSC::instance().stop();

//   printf("Done: deregistering all\n");
//   PolytopesNodesClient::instance().cleanup();
  exit(0);
}

static int target_sound_handler( handlerArgs )
{
  GeneticWorld* world = ( GeneticWorld* ) user_data;
	int noSoundParameters = world->N_GENES;
  int size = noSoundParameters + 1;
  if ( size > argc ){
    size = argc;
    std::cout << "GeneOSC: not enough paramaters, sent: " << argc << ", need: " << noSoundParameters << std::endl;
  }
	int targetId = argv[0]->i;
	int targetSoundParameters[noSoundParameters];
  for ( int i=0; i<noSoundParameters; i++ ){
    targetSoundParameters[i] = argv[i+1]->i;
  }
	world->setTargetSoundParameters(targetId, targetSoundParameters);
  return 0;
}

static int mutation_rate_handler( handlerArgs )
{
  GeneticWorld* world = ( GeneticWorld* ) user_data;
  int size = 1;
  if ( size > argc ){
    size = argc;
    std::cout << "GeneOSC: not enough paramaters, sent: " << argc << ", need: 1" << std::endl;
  }

	world->setMutationRate(argv[0]->f);

	std::cout << "Mutation rate changed: " << world->mutationRate << std::endl;
  return 0;
}

static int survival_rate_handler( handlerArgs )
{
  GeneticWorld* world = ( GeneticWorld* ) user_data;
  int size = 1;
  if ( size > argc ){
    size = argc;
    std::cout << "GeneOSC: not enough paramaters, sent: " << argc << ", need: 1" << std::endl;
  }

	world->setSurvivalRate(argv[0]->f);

	std::cout << "Survival rate changed: " << world->survivalRate << std::endl;
  return 0;
}

int main(int argc, char** argv) {

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
//   PolytopesNodesClient::instance(); // this will start the network

  const char * targetip = POLYTOPES_TARGET_IP;
  const char * targetport = POLYTOPES_TARGET_PORT;
  const char * listenport = POLYTOPES_LISTEN_PORT;
  int nonodes = N_NODES;
//   int nolines = N_LINES;
//   int nonodesperline = N_NODES_PER_LINE;


    int c;
    int digit_optind = 0;


    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
// 	    {"nolines", required_argument, 0,  0 },
// 	    {"nonodesperline", required_argument, 0,  0 },
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

//     	case 'N':
// 	    nolines = atoi( optarg );
//             break;
//
// 	case 'M':
// 	    nonodesperline = atoi( optarg );
//             break;

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
    std::cout << "GeneOSC" << std::endl;
    std::cout << "OSC listening port: " << listenport << std::endl;
    std::cout << "OSC target ip: " << targetip << ", target port: " << targetport << std::endl;
    std::cout << "Number of nodes: " << nonodes << std::endl;
//     std::cout << "Number of lines: " << nolines << std::endl;
//     std::cout << "Number of nodes per line: " << nonodesperline << std::endl;
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

  PolytopeOSC::instance().initNodeData( nonodes );

	GeneticWorld world(nonodes, POLYTOPE_GENE_MUTATE_RATE, POLYTOPE_GENE_SURVIVAL_RATE, POLYTOPE_GENE_N_TARGETS);

//   PolytopeOSC::instance().addMethod( "/qualia/target/sound", NULL, target_sound_handler, (void*) this );
  PolytopeOSC::instance().addMethod( "/qualia/target/sound", NULL, target_sound_handler, (void*)&world );
  PolytopeOSC::instance().addMethod( "/qualia/mutation", NULL, mutation_rate_handler, (void*)&world );
  PolytopeOSC::instance().addMethod( "/qualia/survival", NULL, survival_rate_handler, (void*)&world );

  PolytopeOSC::instance().addMethods();
  PolytopeOSC::instance().start();

	world.init();
//	world.start();

  int iter=0;
  while (!PolytopeOSC::instance().hasQuit()) {
    world.step();

// #if is_computer()
//     printf("t=%d\n", iter++);
// #endif
  }

//  if (myAlloc.nLeaks)
//    printf("WARNING: Static Allocator has leaks: %d\n", myAlloc.nLeaks);

  return 0;
}
