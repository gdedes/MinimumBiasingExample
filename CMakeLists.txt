#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(MinBiasExample)

#----------------------------------------------------------------------------
# Find boost

#find_package( Boost REQUIRED )
##find_package(Boost REQUIRED COMPONENTS system)

#if (${Boost_VERSION} LESS 106500)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_MATH_DISABLE_FLOAT128")
#endif()

#if(NOT Boost_FOUND)
#    message(FATAL_ERROR "Could not find boost!")
#endif()
#message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
#message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
#message(STATUS "Boost_VERSION: ${Boost_VERSION}")

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available Vis drivers by default
# You can set WITH_GEANT4_VIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#--------------------------------------------
#new visualisation version (fingers crossed)
#--------------------------------------------
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR}
#                    ${BOOST_INCLUDE_DIRS}
#                    ${PROJECT_SOURCE_DIR}/channeling/include
                    )
file(GLOB headers #${PROJECT_SOURCE_DIR}/channeling/include/*.hh
                  ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB sources #${PROJECT_SOURCE_DIR}/channeling/src/*.cc
                  ${PROJECT_SOURCE_DIR}/src/*.cc)


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(MinBiasExample MinBiasExample.cc ${sources} ${headers})
target_link_libraries(MinBiasExample ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory
# This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.

set(SIMULATION_SCRIPTS
        #vis.mac
        #run.mac
        )


foreach(_script ${SIMULATION_SCRIPTS})
  configure_file(
          ${PROJECT_SOURCE_DIR}/${_script}
          ${PROJECT_SOURCE_DIR}/build/${_script}
          COPYONLY
  )
endforeach()


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS MinBiasExample DESTINATION bin)

