#short-hand for the srcdir 
SET(srcdir ${CMAKE_SOURCE_DIR}/src)


ADD_DEFINITIONS(-I${scrdir}
                -I${CMAKE_SOURCE_DIR}/test/cxxtest
                -I.
                -O0 -std=c++0x -g3 -Wall -fmessage-length=0 -finstrument-functions)

ADD_EXECUTABLE(TESTRUNNER test_runner.cpp 
                          ${srcdir}/Square.cpp 
                          ${srcdir}/ChessBoard.cpp)

add_custom_command(OUTPUT test_runner.cpp
                   COMMAND cxxtest/bin/cxxtestgen --error-printer -o test_runner.cpp TestChessboard.hpp
                   DEPENDS 
                   COMMENT "running cxxtestgen now..."
                   VERBATIM)
                   
link_directories (/usr/lib/i386-linux-gnu) 


#most of this from the wx widgets documentation
TARGET_LINK_LIBRARIES(TESTRUNNER -lm)



