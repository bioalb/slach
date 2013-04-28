#short-hand for the srcdir 
SET(srcdir ${CMAKE_SOURCE_DIR}/src)
SET(testfiledir ${CMAKE_SOURCE_DIR}/test)

ADD_DEFINITIONS(-I${srcdir}
                -I${CMAKE_SOURCE_DIR}/test/cxxtest
                -I${testfiledir}
                -O0 -std=c++0x -g3 -Wall -fmessage-length=0 -finstrument-functions)

ADD_EXECUTABLE(TESTRUNNER ${testfiledir}/test_runner.cpp
                          ${srcdir}/Exception.cpp 
                          ${srcdir}/Square.cpp 
                          ${srcdir}/ChessBoard.cpp)

add_custom_command(OUTPUT ${testfiledir}/test_runner.cpp
                   COMMAND ${testfiledir}/cxxtest/bin/cxxtestgen --error-printer -o ${testfiledir}/test_runner.cpp ${testfiledir}/TestChessboard.hpp ${testfiledir}/TestPosition.hpp
                   DEPENDS 
                   COMMENT "running cxxtestgen now..."
                   VERBATIM)
                   
link_directories (/usr/lib/i386-linux-gnu) 

TARGET_LINK_LIBRARIES(TESTRUNNER -lm)