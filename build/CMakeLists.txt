#short-hand for the various directories 
SET(srcdir ${CMAKE_SOURCE_DIR}/src)
SET(testfiledir ${CMAKE_SOURCE_DIR}/test)
SET(stockfishdir ${CMAKE_SOURCE_DIR}/src/engines/stockfish_3/src)

set(os_bit_number 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(os_bit_number 64)
endif()

#to build the stockfish library
add_subdirectory (lib)
#to build the executable
add_subdirectory (slach_executable)
#to build the executable that runs unit tests
add_subdirectory (test) 