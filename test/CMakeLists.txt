cmake_minimum_required(VERSION 2.8.11)
project(test)

########################
#Change path to your's
# <youtpath>/bin/qmake.exe must be valid!
set(CMAKE_PREFIX_PATH E:/Nikita/Coding/Qt/5.7/msvc2015)
########################

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(SOURCE tst_qaunittests.cpp)
set(HEADER tst_qaunittests.h)

set(SOURCE_CORE QAMachineCore.cpp QAPairsSet.cpp Stemmer.cpp Vocabulary.cpp)
set(HEADER_CORE QAMachineCore.h QAPairsSet.h Stemmer.h Vocabulary.h)

include_directories(../src/core)
find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

add_executable(test 
	${SOURCE}
	${HEADER}
	../src/core/$<JOIN:${SOURCE_CORE}, ../src/core/>
	../src/core/$<JOIN:${HEADER_CORE}, ../src/core/>
)
target_link_libraries(test Qt5::Core Qt5::Test)


