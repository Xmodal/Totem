#ifndef POLYTOPESOSC_H
#define	POLYTOPESOSC_H

#include <lo/lo.h>
// #include <lo/lo_cpp.h>

#include "oscin.h"

#include <atomic>

// #include <iostream>
// #include <unistd.h>
// #include <string.h>
#include <vector>


class PolytopeOSC {
  public:
      PolytopeOSC();
//       PolytopeOSC( PolytopeOSC *orig);
      ~PolytopeOSC();

      void initialize( const char *targetip, const char *targetport, const char *listenport );
      void addMethod( const char* path, const char *argsignature, lo_method_handler handler, void * user_data );
      void addMethods();

      void start();
      void stop();

      // sending messages out:
      void sendOutputNode( int id, float value );
      void sendOutputLed( int id, float value );
      void sendOutputAllLeds( std::vector<float> * values );
			void sendOutputSound( int id, std::vector<int> * params);
      // called from osc message
      void doQuit();
      void doBang();

      // getting data
      void initNodeData( int size );
      float * getNodeData(); // get a reference to the node data
      int getNodeDataSize(); // get the size of the node data
//       void getNodeData( float *values );
//       void getNodeData( std::vector<float> * values );
      bool checkBang( int timeout );

      static PolytopeOSC& instance();

      void postInfo();

      bool isInitialized(); // const { return (serverThread != 0); }
      bool hasQuit() const { return (shouldQuit); }

  private:
    BlockingOSCServer * oscServer;
    lo_address destinationAddress;

    std::atomic<bool> shouldQuit;
    std::atomic<bool> hasBanged;

    float * nodeData;
    int nodeDataSize;

    static PolytopeOSC inst;

};

#endif // POLYTOPESOSC_H
