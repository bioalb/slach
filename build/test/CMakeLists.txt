
ADD_DEFINITIONS(-O0 -std=c++0x -g3 -Wall -fmessage-length=0 -finstrument-functions -fprofile-arcs -ftest-coverage -g -pg)

include_directories(. ${srcdir}
                    ${CMAKE_SOURCE_DIR}/test/cxxtest
                    ${testfiledir}
                    ${stockfishdir})
                    
link_directories (/usr/lib/i386-linux-gnu ${CMAKE_SOURCE_DIR}/build/lib) 

ADD_EXECUTABLE(TESTRUNNER ${testfiledir}/test_runner.cpp
                          ${srcdir}/Exception.cpp
                          ${srcdir}/Game.cpp
                          ${srcdir}/FenHandler.cpp
                          ${srcdir}/ChessBoard.cpp
                          ${srcdir}/ChessBoardWithBorders.cpp
                          ${srcdir}/Square.cpp
                          ${srcdir}/EngineInterface.cpp
                          ${srcdir}/LegalMoveChecker.cpp)

add_custom_command(OUTPUT ${testfiledir}/test_runner.cpp
                   COMMAND ${testfiledir}/cxxtest/bin/cxxtestgen --error-printer -o ${testfiledir}/test_runner.cpp 
                                                                                    ${testfiledir}/TestChessboardWithBorders.hpp 
                                                                                    ${testfiledir}/TestChessBoard.hpp
                                                                                    ${testfiledir}/TestSquare.hpp
                                                                                    ${testfiledir}/TestFenHandler.hpp
                                                                                    ${testfiledir}/TestGame.hpp
                                                                                    ${testfiledir}/TestEngineInterface.hpp
                                                                                    ${testfiledir}/TestHelperGlobalMethod.hpp
                                                                                    ${testfiledir}/TestLegalMoveChecker.hpp
                   DEPENDS 
                   COMMENT "running cxxtestgen now..."
                   VERBATIM)
                   

set(CMAKE_EXE_LINKER_FLAGS "-pthread -pg")
TARGET_LINK_LIBRARIES(TESTRUNNER -lm  -lstockfish -lgcov)