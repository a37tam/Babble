cmake_minimum_required(VERSION 3.5)

project(Babble LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Configure Qt.
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Configure Asio.
set(ASIO_INC "/opt/asio/include" CACHE PATH "Path to standalone Asio headers.")

#################################################################################
# Build server executable.

add_executable(BabbleServer
               main.cpp
               babble.cpp
               babble.h
               babble.ui
              )

target_include_directories(BabbleServer
                           PRIVATE
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           "${CMAKE_CURRENT_BUILD_DIR}"
                           "${ASIO_INC}"
                          )

target_link_libraries(BabbleServer
                      PRIVATE
                      Qt5::Widgets
                      pthread
                     )

target_compile_features(BabbleServer
                        PRIVATE
                        cxx_std_14
                       )

target_compile_definitions(BabbleServer
                           PRIVATE
                           -DSERVER
                          )
################################################################################
# Build client executable.

add_executable(BabbleClient
               main.cpp
               babble.cpp
               babble.h
               babble.ui
              )

target_include_directories(BabbleClient
                           PRIVATE
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           "${CMAKE_CURRENT_BUILD_DIR}"
                           "${ASIO_INC}"
                          )

target_link_libraries(BabbleClient
                      PRIVATE
                      Qt5::Widgets
                      pthread
                     )

target_compile_features(BabbleClient
                        PRIVATE
                        cxx_std_14
                       )

target_compile_definitions(BabbleClient
                           PRIVATE
                           -DCLIENT
                          )
