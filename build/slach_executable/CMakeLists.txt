

#most of this from the wx widgets documentation
ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 
                -D_LARGE_FILES 
                -D__WXGTK__ 
                 -O0 -Wl,--no-as-needed -pthread -std=c++11 -g3 -Wall -Wextra -pedantic -fmessage-length=0 -finstrument-functions)
                           
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
                       ${srcdir}/EngineInterface.cpp
                       ${srcdir}/LegalMoveChecker.cpp
                       ${srcdir}/ChessBoard.cpp
                       ${srcdir}/ChessBoardWithBorders.cpp
                       ${srcdir}/GUI/Colours.cpp 
                       ${srcdir}/GUI/RightPanel.cpp 
                       ${srcdir}/GUI/MainFrame.cpp 
                       ${srcdir}/GUI/ChessBoardPanel.cpp 
                       ${srcdir}/GUI/CentralPanel.cpp 
                       ${srcdir}/GUI/BottomPanel.cpp 
                       ${srcdir}/GUI/slach_main.cpp)

#most of this from the wx widgets documentation
TARGET_LINK_LIBRARIES(slach   -lwx_${GTK_VER}u_richtext-3.0 
                              -lwx_${GTK_VER}u_aui-3.0 
                              -lwx_${GTK_VER}u_xrc-3.0 
                              -lwx_${GTK_VER}u_qa-3.0
                              -lwx_${GTK_VER}u_html-3.0 
                              -lwx_${GTK_VER}u_adv-3.0
                              -lwx_${GTK_VER}u_core-3.0 
                              -lwx_baseu_xml-3.0
                              -lwx_baseu_net-3.0 
                              -lwx_baseu-3.0)


