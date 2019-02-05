message( "=== Genes OSC ===" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(
  ${CMAKE_BINARY_DIR}
  ${liblo_INCLUDE_DIRS}
)

set(geneOSC_SRCS
  main.cpp
  GeneticWorld.cpp
)

add_executable( gene_osc ${geneOSC_SRCS} )

target_link_libraries(gene_osc ${liblo_LIBRARIES} ${QUALIA_LIBRARY} polytopesOSC)
