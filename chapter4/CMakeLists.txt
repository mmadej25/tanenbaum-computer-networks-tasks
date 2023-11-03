
add_library(Simulator EthernetSimulator.cpp)

add_executable(chapter4 main.cpp)
target_link_libraries(chapter4 PRIVATE Simulator)
