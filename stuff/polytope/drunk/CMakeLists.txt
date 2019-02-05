message( "=== Drunk OSC ===" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(
  ${CMAKE_BINARY_DIR}
  ${liblo_INCLUDE_DIRS}
)

set(drunkOSC_SRCS
  main.cpp
  PolytopesDrunkAgent.cpp
  PolytopesOSCDrunkEnvironment.cpp
)

add_executable( drunk_osc ${drunkOSC_SRCS} )

target_link_libraries(drunk_osc ${liblo_LIBRARIES} ${QUALIA_LIBRARY} polytopesOSC)
