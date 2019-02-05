message( "=== Booster OSC ===" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

# include(FindPkgConfig)
# pkg_check_modules(liblo REQUIRED liblo)
# 
# 
# find_library(QUALIA_LIBRARY
#     NAMES qualia
# #     HINTS "${CMAKE_PREFIX_PATH}/curl/lib"
# )
# 
# # message(${QUALIA_LIBRARY} )

include_directories(
  ${CMAKE_BINARY_DIR}
  ${liblo_INCLUDE_DIRS}
)

set(boosterOSC_SRCS
  main.cpp
  PolytopesBoosterAgent.cpp
  PolytopesOSCBoosterEnvironment.cpp
)

add_executable( booster_osc ${boosterOSC_SRCS} )

target_link_libraries(booster_osc ${liblo_LIBRARIES} ${QUALIA_LIBRARY} polytopesOSC)
