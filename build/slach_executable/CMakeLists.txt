

#these are from the wx widgets documentation
ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -D__WXGTK__)

include_directories(/usr/lib/${ARCHITECTURE_LIBRARY_DIR}/wx/include/${GTK_VER}-unicode-3.0
                    /usr/include/wx-3.0 
                    ${srcdir}
                    ${stockfishdir})

ADD_EXECUTABLE(slach   ${srcdir}/Exception.cpp
                       ${srcdir}/HelperGlobalFunctions.cpp
                       ${srcdir}/Game.cpp
                       ${srcdir}/Position.cpp
                       ${srcdir}/FenHandler.cpp
                       ${srcdir}/Square.cpp
                       ${srcdir}/Move.cpp
                       ${srcdir}/UCIStringsManipulator.cpp
                       ${srcdir}/UCIEngineInterface.cpp
                       ${srcdir}/LegalMoveChecker.cpp
                       ${srcdir}/ChessBoard.cpp
                       ${srcdir}/ChessBoardWithBorders.cpp
                       ${srcdir}/GUI/Colours.cpp 
                       ${srcdir}/GUI/MainFrame.cpp 
                       ${srcdir}/GUI/ChessBoardPanel.cpp 
                       ${srcdir}/GUI/CentralPanel.cpp 
                       ${srcdir}/GUI/BottomPanel.cpp 
                       ${srcdir}/GUI/slach_main.cpp)

LINK_DIRECTORIES(/usr/lib/${ARCHITECTURE_LIBRARY_DIR})
#most of this from the wx widgets documentation
FIND_LIBRARY(STOCKFISH_LIB NAMES stockfish PATHS ${stockfishdir})
TARGET_LINK_LIBRARIES(slach   -lwx_${GTK_VER}u_richtext-3.0 
                              -lwx_${GTK_VER}u_aui-3.0 
                              -lwx_${GTK_VER}u_xrc-3.0 
                              -lwx_${GTK_VER}u_qa-3.0
                              -lwx_${GTK_VER}u_html-3.0 
                              -lwx_${GTK_VER}u_adv-3.0
                              -lwx_${GTK_VER}u_core-3.0 
                              -lwx_baseu_xml-3.0
                              -lwx_baseu_net-3.0 
                              -lwx_baseu-3.0
                              ${STOCKFISH_LIB})


