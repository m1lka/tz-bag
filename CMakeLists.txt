cmake_minimum_required(VERSION 2.8)
project(tz-bag)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(TARGET_SRC main.cpp)

SET(HEADERS ./Fruit.h
            ./FruitBagProvider.h
            ./helper.h
            ./Console.h
            ./Services/IService.h
            ./Services/FileFruitService.h)

SET(SOURCES ./Fruit.cpp
            ./FruitBagProvider.cpp
            ./Console.cpp
            ./Services/FileFruitService.cpp)

include_directories(./)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fruits.txt ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${TARGET_SRC})
