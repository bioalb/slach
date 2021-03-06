
ADD_DEFINITIONS(-DSLACH_TESTING)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -pg -g")

include_directories(. ${srcdir}
                    ${CMAKE_SOURCE_DIR}/test/cxxtest
                    ${testfiledir}
                    ${stockfishdir})

SET (source_files ${srcdir}/Exception.cpp
                  ${srcdir}/HelperGlobalFunctions.cpp
                  ${srcdir}/Game.cpp
                  ${srcdir}/Position.cpp
                  ${srcdir}/FenHandler.cpp
                  ${srcdir}/ChessBoard.cpp
                  ${srcdir}/ChessBoardWithBorders.cpp
                  ${srcdir}/Square.cpp
                  ${srcdir}/Move.cpp
                  ${srcdir}/UCIStringsManipulator.cpp
                  ${srcdir}/UCIEngineInterface.cpp
                  ${srcdir}/LegalMoveChecker.cpp)
                 
SET (single_test_to_run ${testfiledir}/TestChessboardWithBorders.hpp)
          
SET (all_test_files ${testfiledir}/TestChessboardWithBorders.hpp 
                    ${testfiledir}/TestChessBoard.hpp
                    ${testfiledir}/TestChessBoardSpecialMoves.hpp
                    ${testfiledir}/TestPosition.hpp
                    ${testfiledir}/TestSquare.hpp
                    ${testfiledir}/TestMove.hpp
                    ${testfiledir}/TestFenHandler.hpp
                    ${testfiledir}/TestGame.hpp
                    ${testfiledir}/TestUCIStringsManipulator.hpp
                    ${testfiledir}/TestUCIEngineInterface.hpp
                    ${testfiledir}/TestHelperGlobalMethod.hpp
                    ${testfiledir}/TestLegalMoveChecker.hpp)

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
            
#FIND_LIBRARY(STOCKFISH_LIB NAMES stockfish PATHS ${stockfishdir})
TARGET_LINK_LIBRARIES(ALL_TESTS -L${stockfishdir} -lm -lgcov -lstockfish)
TARGET_LINK_LIBRARIES(SINGLE_TEST -L${stockfishdir} -lm -lgcov -lstockfish)
