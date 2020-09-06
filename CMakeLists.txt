cmake_minimum_required(VERSION 3.5)

project(Babble LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Configure Qt.
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Configure Asio.
set(ASIO_INC "/opt/asio/include" CACHE PATH "Path to standalone Asio headers.")

add_executable(Babble
               main.cpp
               babble.cpp
               session.cpp
               babble.h
               session.h
               babble.ui
              )

target_include_directories(Babble
                           PRIVATE
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           "${CMAKE_CURRENT_BUILD_DIR}"
                           "${ASIO_INC}"
                          )

target_link_libraries(Babble
                      PRIVATE
                      Qt5::Widgets
                      pthread
                     )

target_compile_features(Babble
                        PRIVATE
                        cxx_std_11
                       )
