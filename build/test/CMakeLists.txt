
ADD_DEFINITIONS(-O0 -std=c++0x -g3 -Wall -Wextra -Weffc++ -pedantic -fmessage-length=0 -finstrument-functions -fprofile-arcs -ftest-coverage -g -pg)

include_directories(. ${srcdir}
                    ${CMAKE_SOURCE_DIR}/test/cxxtest
                    ${testfiledir}
                    ${stockfishdir})

SET (source_files ${srcdir}/Exception.cpp
                  ${srcdir}/Game.cpp
                  ${srcdir}/FenHandler.cpp
                  ${srcdir}/ChessBoard.cpp
                  ${srcdir}/ChessBoardWithBorders.cpp
                  ${srcdir}/Square.cpp
                  ${srcdir}/Move.cpp
                  ${srcdir}/EngineInterface.cpp
                  ${srcdir}/LegalMoveChecker.cpp)
                 
SET (single_test_to_run ${testfiledir}/TestChessBoard.hpp)
          
SET (all_test_files ${testfiledir}/TestChessboardWithBorders.hpp 
                    ${testfiledir}/TestChessBoard.hpp
                    ${testfiledir}/TestChessBoardSpecialMoves.hpp
                    ${testfiledir}/TestSquare.hpp
                    ${testfiledir}/TestMove.hpp
                    ${testfiledir}/TestFenHandler.hpp
                    ${testfiledir}/TestGame.hpp
                    ${testfiledir}/TestEngineInterface.hpp
                    ${testfiledir}/TestHelperGlobalMethod.hpp
                    ${testfiledir}/TestLegalMoveChecker.hpp)

link_directories (/usr/lib/i386-linux-gnu ${CMAKE_SOURCE_DIR}/build/lib) 

ADD_EXECUTABLE(ALL_TESTS ${testfiledir}/test_runner.cpp ${source_files})

ADD_EXECUTABLE(SINGLE_TEST ${testfiledir}/single_test_runner.cpp ${source_files})
                      
add_custom_command(OUTPUT ${testfiledir}/test_runner.cpp
                   COMMAND ${testfiledir}/cxxtest/bin/cxxtestgen --error-printer -o ${testfiledir}/test_runner.cpp ${all_test_files}
                   DEPENDS ${all_test_files}
                   COMMENT "running cxxtestgen now for all tests..."
                   VERBATIM)

add_custom_command(OUTPUT ${testfiledir}/single_test_runner.cpp
                   COMMAND ${testfiledir}/cxxtest/bin/cxxtestgen --error-printer -o ${testfiledir}/single_test_runner.cpp ${single_test_to_run}
                   DEPENDS ${all_test_files}                                                            
                   COMMENT "running cxxtestgen now for single file..."
                   VERBATIM)              

set(CMAKE_EXE_LINKER_FLAGS "-pthread -pg")
TARGET_LINK_LIBRARIES(ALL_TESTS -lm  -lstockfish -lgcov)
TARGET_LINK_LIBRARIES(SINGLE_TEST -lm  -lstockfish -lgcov)