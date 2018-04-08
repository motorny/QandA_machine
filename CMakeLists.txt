cmake_minimum_required(VERSION 2.8)
project(QAMachine)

set(SOURCE_CORE QAMachineCore.cpp QAPairsSet.cpp Stemmer.cpp Vocabulary.cpp)
set(HEADER_CORE QAMachineCore.h QAPairsSet.h Stemmer.h Vocabulary.h)

include_directories(src/core)

add_subdirectory(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W4")
add_executable(QAMachine 
	src/main.cpp
	src/core/$<JOIN:${SOURCE_CORE}, src/core/>
	src/core/$<JOIN:${HEADER_CORE}, src/core/>
)