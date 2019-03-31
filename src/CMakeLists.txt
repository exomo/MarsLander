

file(GLOB source_files *.cpp)
add_library(exomo_marslander_lib ${source_files})
include_directories(${SFML_INCLUDE_DIR})
target_include_directories(exomo_marslander_lib PUBLIC ../include)
target_link_libraries(exomo_marslander_lib ${SFML_LIBRARIES})
