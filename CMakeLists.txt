cmake_minimum_required(VERSION 3.16)

set(DATA_PROCESSOR_LIBRARY_NAME psr)
project(${DATA_PROCESSOR_LIBRARY_NAME} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core)

set(INCLUDE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB HEADERS ${INCLUDE_ROOT}/*.h ${INCLUDE_ROOT}/*/*.h)

add_library(${PROJECT_NAME} STATIC ${HEADERS})
if (${Qt6_FOUND})
  target_link_libraries(${PROJECT_NAME} Qt6::Core)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC
  ${INCLUDE_ROOT}
  ${INCLUDE_ROOT}/filters
  ${INCLUDE_ROOT}/relation
  ${INCLUDE_ROOT}/statistics
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
  ${INCLUDE_ROOT}
  ${INCLUDE_ROOT}/filters
  ${INCLUDE_ROOT}/relation
  ${INCLUDE_ROOT}/statistics
)
