#include "PolytopesOSC.h"

#include <iostream>
#include <unistd.h>

// osc handlers:

static int quit_handler( handlerArgs )
{
  PolytopeOSC* osc = ( PolytopeOSC* ) user_data;
  osc->doQuit();
  return 0;
}

static int all_mean_handler( handlerArgs )
{
  PolytopeOSC* osc = ( PolytopeOSC* ) user_data;
  float * mydata = osc->getNodeData();
  int size = osc->getNodeDataSize();
  if ( size > argc ){ size = argc; }
  for ( int i=0; i<size; i++ ){
    mydata[i] = argv[i]->f;
  }
  return 0;
}

// static int par_walk_handler( handlerArgs )
// {
//   PolytopeOSC* osc = ( PolytopeOSC* ) user_data;
//   osc->doQuit();
//   return 0;
// }
//
// static int add_chaser_handler( handlerArgs )
// {
//   PolytopeOSC* osc = ( PolytopeOSC* ) user_data;
//   osc->doQuit();
//   return 0;
// }
//
// static int del_chaser_handler( handlerArgs )
// {
//   PolytopeOSC* osc = ( PolytopeOSC* ) user_data;
//   osc->doQuit();
//   return 0;
// }

static int bang_handler( handlerArgs )
{
  PolytopeOSC* osc = ( PolytopeOSC* ) user_data;
  osc->doBang();
  return 0;
}

// void test_handler(const char *path, const char *types, lo_arg **argv, int argc, void *user_data)
// {
//   PolytopeOSC* osc = ( PolytopeOSC* ) user_data;
// //   osc->printTest();
// }

static int default_handler(handlerArgs)
{
    std::cout << "Sorry, but " << path << " " << types << " is not a valid command message...\n";
}


/// class

PolytopeOSC PolytopeOSC::inst;

PolytopeOSC& PolytopeOSC::instance() {
//   if (!inst.isInitialized())
//     inst.initialize(ip, port, id);

  return inst;
}

PolytopeOSC::PolytopeOSC(){
  shouldQuit = false;
  hasBanged = false;
}

PolytopeOSC::~PolytopeOSC(){
  if ( oscServer != NULL ){
    this->stop();
    delete oscServer;
  }
  if ( destinationAddress != NULL ){
    lo_address_free( destinationAddress );
  }
}

// void PolytopeOSC::postInfo(){
//   if ( isInitialized() ){
//     std::cout << "Coming in at: " << serverThread->url() << std::endl;
//     std::cout << "Back at you at: " << address->url() << std::endl;
//   }
// }

bool PolytopeOSC::isInitialized(){
 if ( oscServer == NULL ){ return false; }
 return true;
//  return serverThread->is_valid();
}

void PolytopeOSC::initialize(const char* targetip, const char* targetport, const char* listenport) {
  oscServer = new BlockingOSCServer( listenport );
  destinationAddress = lo_address_new( targetip, targetport );
  shouldQuit = false;
  hasBanged = false;
}

void PolytopeOSC::doQuit(){
  shouldQuit = true;
  std::cout << "OSC server will quit\n" << std::endl;
//   this->stop();
}

void PolytopeOSC::doBang(){
    hasBanged = true;
}

bool PolytopeOSC::checkBang( int timeout ) {

  if (timeout != 0) {
    clock_t begin = clock();
    while ( hasBanged != true &&
            (timeout == -1 ||
            (clock()-begin) < ((unsigned long)timeout)*CLOCKS_PER_SEC/1000)) {

      if (hasQuit()) // check for quit.
        return false;

      usleep(10); // wait 10 microseconds
    }
  }

  if (hasBanged) {
    hasBanged = false;
    if (hasQuit())  // last check for quitting
      return false;
    else
      return true; // new data has arrived!
  }
  else
    return false;
}

// these could be specific methods
//   oscServer->addMethod( "/qualia/parameters/add", "fffff", add_chaser_handler, (void*) this ); // FIXME : parameter values/signature
//   oscServer->addMethod( "/qualia/parameters/remove", "fffff", remove_chaser_handler, (void*) this );  // FIXME : parameter values/signature
//   oscServer->addMethod( "/qualia/parameters/randomwalk", "fffff", par_walk_handler, (void*) this );
void PolytopeOSC::addMethod( const char* path, const char *argsignature, lo_method_handler handler, void * user_data ){
  oscServer->addMethod( path, argsignature, handler, user_data );
}

void PolytopeOSC::addMethods(){
  oscServer->addMethod( "/qualia/input/all/meanvalue", NULL, all_mean_handler, (void*) this );
  oscServer->addMethod( "/qualia/bang", NULL, bang_handler, (void*) this );


  oscServer->addMethod( "/qualia/quit", NULL, quit_handler, (void*) this );
  oscServer->addMethod( NULL, NULL, default_handler, (void*) this );
//   serverThread->add_method("/qualia/quit", NULL, quit_handler, (void*) this );
//   serverThread->add_method(NULL,NULL,default_handler);
}

// start and stop oscserver

void PolytopeOSC::start(){
    oscServer->start();
}

void PolytopeOSC::stop(){
    oscServer->stop();
}

/// node data

void PolytopeOSC::initNodeData( int size ){
    if ( nodeData != NULL ){ free(nodeData); }
    nodeData = (float*) malloc( size * sizeof(float) );
    nodeDataSize = size;
}

int PolytopeOSC::getNodeDataSize(){
    return nodeDataSize;
}

float * PolytopeOSC::getNodeData(){
    return nodeData;
}

void PolytopeOSC::sendOutputNode( int id, float value ){
  lo_message msg = lo_message_new();
  lo_message_add_int32( msg, id );
  lo_message_add_float( msg, value );
  oscServer->sendMessage( destinationAddress, "/qualia/output/node", msg );
  lo_message_free( msg );
}

void PolytopeOSC::sendOutputLed( int id, float value ){
  lo_message msg = lo_message_new();
  lo_message_add_int32( msg, id );
  lo_message_add_float( msg, value );
  oscServer->sendMessage( destinationAddress, "/qualia/output/led", msg );
  lo_message_free( msg );
}

void PolytopeOSC::sendOutputAllLeds( std::vector<float> * values ){
  lo_message msg = lo_message_new();
  std::vector<float>::iterator it;
  for ( it = values->begin(); it != values->end(); it++ ){
    lo_message_add_float( msg, *it );
  }
  oscServer->sendMessage( destinationAddress, "/qualia/output/all/led", msg );
  lo_message_free( msg );
}

void PolytopeOSC::sendOutputSound( int id, std::vector<int> * params)
{
  lo_message msg = lo_message_new();
  lo_message_add_int32( msg, id );
  std::vector<int>::iterator it;
  for ( it = params->begin(); it != params->end(); it++ ){
    lo_message_add_int32( msg, *it );
  }
  oscServer->sendMessage( destinationAddress, "/qualia/output/sound", msg );
  lo_message_free( msg );
}
