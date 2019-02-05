message( "=== Firefly OSC ===" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(
  ${CMAKE_BINARY_DIR}
  ${liblo_INCLUDE_DIRS}
)

set(fireflyOSC_SRCS
  main.cpp
  PolytopesFireflyAgent.cpp
  PolytopesOSCFireflyEnvironment.cpp
)

add_executable( firefly_osc ${fireflyOSC_SRCS} )

target_link_libraries(firefly_osc ${liblo_LIBRARIES} ${QUALIA_LIBRARY} polytopesOSC)
