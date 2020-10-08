cmake_minimum_required(VERSION 3.14)

project(processingTheRegisterOfProhibitedSites LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(processingTheRegisterOfProhibitedSites
  main.cpp
  prohibitedsites.cpp
)
target_link_libraries(processingTheRegisterOfProhibitedSites Qt${QT_VERSION_MAJOR}::Core Qt5::Network)

find_package(Qt5 COMPONENTS Network REQUIRED)

target_link_libraries(processingTheRegisterOfProhibitedSites Qt5::Network)
