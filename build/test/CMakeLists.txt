
ADD_DEFINITIONS(-I${srcdir}
                -I${CMAKE_SOURCE_DIR}/test/cxxtest
                -I${testfiledir}
                -I${stockfishdir}
                -O0 -std=c++0x -g3 -Wall -fmessage-length=0 -finstrument-functions)

link_directories (/usr/lib/i386-linux-gnu ${CMAKE_SOURCE_DIR}/build/lib) 

ADD_EXECUTABLE(TESTRUNNER ${testfiledir}/test_runner.cpp
                          ${srcdir}/Exception.cpp
                          ${srcdir}/Game.cpp
                          ${srcdir}/FenHandler.cpp
                          ${srcdir}/ChessBoard.cpp
                          ${srcdir}/ChessBoardWithBorders.cpp
                          ${srcdir}/Square.cpp
                          ${srcdir}/EngineInterface.cpp)

add_custom_command(OUTPUT ${testfiledir}/test_runner.cpp
                   COMMAND ${testfiledir}/cxxtest/bin/cxxtestgen --error-printer -o ${testfiledir}/test_runner.cpp 
                                                                                    ${testfiledir}/TestChessboardWithBorders.hpp 
                                                                                    ${testfiledir}/TestChessBoard.hpp
                                                                                    ${testfiledir}/TestSquare.hpp
                                                                                    ${testfiledir}/TestFenHandler.hpp
                                                                                    ${testfiledir}/TestGame.hpp
                                                                                    ${testfiledir}/TestEngineInterface.hpp
                   DEPENDS 
                   COMMENT "running cxxtestgen now..."
                   VERBATIM)
                   


TARGET_LINK_LIBRARIES(TESTRUNNER -lm  -lstockfish -pthread)