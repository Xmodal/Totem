
#include "PolytopesOSC.h"
//#include "RepClassifier.cpp"

#include <iostream>
#include <atomic>
#include <unistd.h>
#include <string.h>
#include <vector>


// Objects
PolytopeOSC* osc;

int main(int argc, char** argv)
{
    char *myport = "9005";
    char *dest_port = "9006";
    char *dest_ip = "127.0.0.1";

    if ( argc > 3 )
        dest_ip = argv[3];
    if ( argc > 2 )
        myport = argv[2];
    if ( argc > 1 )
        dest_port = argv[1];


    osc = new PolytopeOSC();
    osc->initialize( dest_ip, dest_port, myport );

    if (!osc->isInitialized())
    {
        std::cout << "Could not initialize OSC server" << std::endl;
        return 1;
    } else {
	std::cout << "OSC server is initialized, listening at: " << myport << ", sending to: " << dest_ip << ":" << dest_port << std::endl;
    }
    
//     osc->postInfo();

//     std::cout << "Press h for Help\n";
//     std::cout << "Want to quit? Hit 'q' and Enter\n\n";
    
    osc->addMethods();
    osc->start();

    char s[10];
    
//     shouldQuit = false;

//     std::cout << "If you want to quit, enter 'q'\n";
    while ( !osc->hasQuit() )
    {
      usleep(100000);
//       st->recv(100);
//       std::cin.getline(s,10);
//       if(strcmp(s,"q")==0)
// 	break;
// 	shouldQuit = true;
//       else if(strcmp(s, "h")==0)
//             help();
    }
    osc->stop();

    std::cout << "\nShutting down...\n";
}
