

#most of this from the wx widgets documentation
ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 
                -D_LARGE_FILES 
                -D__WXGTK__ 
                 -O0 -std=c++0x -g3 -Wall -Wextra -pedantic -fmessage-length=0 -finstrument-functions)
                           
include_directories(/usr/local/lib/wx/include/${GTK_VER}-unicode-2.9
                    /usr/local/include/wx-2.9 
                    ${srcdir} 
                    ${stockfishdir} )
link_directories (${CMAKE_SOURCE_DIR}/build/lib) 


ADD_EXECUTABLE(slach   ${srcdir}/Exception.cpp
                       ${srcdir}/HelperGlobalFunctions.cpp
                       ${srcdir}/Game.cpp
                       ${srcdir}/Position.cpp
                       ${srcdir}/FenHandler.cpp
                       ${srcdir}/Square.cpp
                       ${srcdir}/Move.cpp
                       ${srcdir}/EngineInterface.cpp
                       ${srcdir}/LegalMoveChecker.cpp
                       ${srcdir}/ChessBoard.cpp
                       ${srcdir}/ChessBoardWithBorders.cpp
                       ${srcdir}/GUI/DropTargetPanel.cpp 
                       ${srcdir}/GUI/RightPanel.cpp 
                       ${srcdir}/GUI/MainFrame.cpp 
                       ${srcdir}/GUI/ChessBoardPanel.cpp 
                       ${srcdir}/GUI/BottomPanel.cpp 
                       ${srcdir}/GUI/slach_main.cpp)

#most of this from the wx widgets documentation
TARGET_LINK_LIBRARIES(slach   -lwx_${GTK_VER}u_richtext-2.9 
                              -lwx_${GTK_VER}u_aui-2.9 
                              -lwx_${GTK_VER}u_xrc-2.9 
                              -lwx_${GTK_VER}u_qa-2.9 
                              -lwx_${GTK_VER}u_html-2.9 
                              -lwx_${GTK_VER}u_adv-2.9 
                              -lwx_${GTK_VER}u_core-2.9 
                              -lwx_baseu_xml-2.9 
                              -lwx_baseu_net-2.9 
                              -lwx_baseu-2.9
                              -lstockfish)



