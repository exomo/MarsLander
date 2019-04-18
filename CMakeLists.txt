cmake_minimum_required (VERSION 3.12)
cmake_policy(SET CMP0074 NEW)
project(ExomoMarsLander)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2.1 COMPONENTS audio graphics window system REQUIRED)

SET(CMAKE_CXX_FLAGS "-std=c++14")
if(WIN32 AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

add_subdirectory(src)

include_directories(${SFML_INCLUDE_DIR})
add_executable(marslander Main.cpp)
target_link_libraries(marslander exomo_marslander_lib)

install(TARGETS marslander DESTINATION .)
install(DIRECTORY resources DESTINATION .)

if(WIN32)
install(FILES ${SFML_INCLUDE_DIR}/../bin/openal32.dll
        DESTINATION .)
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
install(FILES ${SFML_AUDIO_DLL_RELEASE}
			  ${SFML_GRAPHICS_DLL_RELEASE}
			  ${SFML_SYSTEM_DLL_RELEASE}
			  ${SFML_WINDOW_DLL_RELEASE}
        DESTINATION .)
else()
install(FILES ${SFML_AUDIO_DLL_DEBUG}
			  ${SFML_GRAPHICS_DLL_DEBUG}
			  ${SFML_SYSTEM_DLL_DEBUG}
			  ${SFML_WINDOW_DLL_DEBUG}
        DESTINATION .)
endif()
endif()
