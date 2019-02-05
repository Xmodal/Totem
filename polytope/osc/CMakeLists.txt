message( "=== N-Polytope OSC ===" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

# include(FindPkgConfig)
# pkg_check_modules(liblo REQUIRED liblo)

include_directories(
  ${CMAKE_BINARY_DIR}
  ${liblo_INCLUDE_DIRS}
)

set(polytopesOSCExample_SRCS
  PolytopesOSC.cpp
  oscin.cpp
  main.cpp
)

set(polytopesOSC_SRCS
  PolytopesOSC.cpp
  oscin.cpp
)

add_executable( polytopes_osc ${polytopesOSCExample_SRCS} )
target_link_libraries(polytopes_osc ${liblo_LIBRARIES})

add_library( polytopesOSC ${polytopesOSC_SRCS})
target_link_libraries(polytopesOSC ${liblo_LIBRARIES})

