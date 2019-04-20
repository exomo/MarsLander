

file(GLOB common_source_files *.cpp)
file(GLOB graphics_source_files graphics/*.cpp)
file(GLOB simulation_source_files simulation/*.cpp)
file(GLOB statemachine_source_files statemachine/*.cpp)

set(source_files 
    ${common_source_files} 
    ${graphics_source_files} 
    ${simulation_source_files} 
    ${statemachine_source_files} )
    
add_library(exomo_marslander_lib ${source_files})
include_directories(${SFML_INCLUDE_DIR})
target_include_directories(exomo_marslander_lib PUBLIC ../include)
target_link_libraries(exomo_marslander_lib ${SFML_LIBRARIES})
