#Compiling stockfish executable

ADD_DEFINITIONS(-I${stockfishdir} 
                -Wall -Wcast-qual -fno-exceptions -fno-rtti -std=c++11 -pedantic -Wno-long-long -Wextra -Wshadow -DNDEBUG -O3 -DNO_PREFETCH -flto
                -Wl,--no-as-needed -lpthread )

add_executable(stockfish  ${stockfishdir}/benchmark.cpp 
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
#TARGET_LINK_LIBRARIES(stockfish  -lm)



