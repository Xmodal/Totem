message( "=== Chasers OSC ===" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(
  ${CMAKE_BINARY_DIR}
  ${liblo_INCLUDE_DIRS}
)

set(chaserOSC_SRCS
  main.cpp
  PolytopesChaserGridWorld.cpp
  PolytopesOSCChaserEnvironment.cpp
)

add_executable( chaser_osc ${chaserOSC_SRCS} )

target_link_libraries(chaser_osc ${liblo_LIBRARIES} ${QUALIA_LIBRARY} polytopesOSC)
