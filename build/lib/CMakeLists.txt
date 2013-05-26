#Compiling stockfish as a library

ADD_DEFINITIONS(-I${stockfishdir} 
                -O0 -pedantic -Wno-long-long -Wextra -Wshadow -std=c++0x -g3 -Wall)

add_library(stockfish  ${stockfishdir}/benchmark.cpp 
                       ${stockfishdir}/bitbase.cpp 
                       ${stockfishdir}/bitboard.cpp 
                       ${stockfishdir}/book.cpp 
                       ${stockfishdir}/endgame.cpp 
                       ${stockfishdir}/evaluate.cpp 
                       ${stockfishdir}/main.cpp
                       ${stockfishdir}/material.cpp
                       ${stockfishdir}/misc.cpp
                       ${stockfishdir}/movegen.cpp
                       ${stockfishdir}/movepick.cpp 
                       ${stockfishdir}/notation.cpp 
                       ${stockfishdir}/pawns.cpp 
                       ${stockfishdir}/position.cpp
                       ${stockfishdir}/search.cpp
                       ${stockfishdir}/thread.cpp
                       ${stockfishdir}/timeman.cpp
                       ${stockfishdir}/tt.cpp 
                       ${stockfishdir}/uci.cpp 
                       ${stockfishdir}/ucioption.cpp)

link_directories (/usr/lib/i386-linux-gnu) 

#
TARGET_LINK_LIBRARIES(stockfish  -lm)



