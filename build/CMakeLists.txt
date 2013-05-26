#short-hand for the srcdir 
SET(srcdir ${CMAKE_SOURCE_DIR}/src)
SET(testfiledir ${CMAKE_SOURCE_DIR}/test)
SET(stockfishdir ${CMAKE_SOURCE_DIR}/src/engines/stockfish_3/src)

#to build the stockfish library
add_subdirectory (lib)
#to build the executable
add_subdirectory (slach_executable)
#to build the executable that runs unit tests
add_subdirectory (test) 