#short-hand for the various directories 
set( CMAKE_VERBOSE_MAKEFILE on )
SET(srcdir ${CMAKE_SOURCE_DIR}/src)
SET(testfiledir ${CMAKE_SOURCE_DIR}/test)
SET(stockfishdir ${CMAKE_SOURCE_DIR}/build/stockfish/src_c++11)

set(os_bit_number 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(os_bit_number 64)
endif()

set(DETECTEDARCH x86-32)
set(ARCHITECTURE_LIBRARY_DIR i386-linux-gnu) #used for includes of wx-gtk setup.h
if (os_bit_number EQUAL 64)
	set(DETECTEDARCH x86-64)
	set(ARCHITECTURE_LIBRARY_DIR x86_64-linux-gnu)
endif()

# if gtk3 is present all the include and libraries will be in different directories...
set (GTK_VER gtk2)
if (EXISTS "/usr/lib/i-386-linux-gnu/wx/include/gtk3-unicode-3.0/")
    set (GTK_VER gtk3)
endif()
if (EXISTS "/usr/lib/x86_64-linux-gnu/wx/include/gtk3-unicode-3.0/")
    set (GTK_VER gtk3)
endif()

add_subdirectory (stockfish)
#to build the executable
add_subdirectory (slach_executable)
#to build the executable that runs unit tests
add_subdirectory (test) 