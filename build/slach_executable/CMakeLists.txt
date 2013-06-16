

#most of this from the wx widgets documentation
ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 
                -D_LARGE_FILES 
                -D__WXGTK__ 
                 -O0 -std=c++0x -g3 -Wall -Wextra -pedantic -fmessage-length=0 -finstrument-functions)
                 
if (os_bit_number EQUAL 32)             
include_directories(/usr/lib/i386-linux-gnu/wx/include/gtk2-unicode-release-2.8 
                    /usr/include/wx-2.8 
                    /usr/include/wxSVG 
                    ${srcdir} 
                    ${stockfishdir} )
else()
include_directories(/usr/lib/x86_64-linux-gnu/wx/include/gtk2-unicode-release-2.8 
                    /usr/include/wx-2.8 
                    /usr/include/wxSVG 
                    ${srcdir} 
                    ${stockfishdir} )
endif()


                    
link_directories (/usr/lib/i386-linux-gnu ${CMAKE_SOURCE_DIR}/build/lib) 

ADD_EXECUTABLE(slach   ${srcdir}/Exception.cpp
                       ${srcdir}/Game.cpp
                       ${srcdir}/FenHandler.cpp
                       ${srcdir}/Square.cpp
                       ${srcdir}/Move.cpp
                       ${srcdir}/EngineInterface.cpp
                       ${srcdir}/LegalMoveChecker.cpp
                       ${srcdir}/ChessBoard.cpp
                       ${srcdir}/ChessBoardWithBorders.cpp
                       ${srcdir}/GUI/SquarePanel.cpp 
                       ${srcdir}/GUI/DropTargetPanel.cpp 
                       ${srcdir}/GUI/RightPanel.cpp 
                       ${srcdir}/GUI/MainPanel.cpp 
                       ${srcdir}/GUI/MainFrame.cpp 
                       ${srcdir}/GUI/ActualBoardPanel.cpp 
                       ${srcdir}/GUI/ChessboardPanel.cpp 
                       ${srcdir}/GUI/BottomPanel.cpp 
                       ${srcdir}/GUI/slach_main.cpp)

#most of this from the wx widgets documentation
TARGET_LINK_LIBRARIES(slach   -lwx_gtk2u_richtext-2.8 
                              -lwx_gtk2u_aui-2.8 
                              -lwx_gtk2u_xrc-2.8 
                              -lwx_gtk2u_qa-2.8 
                              -lwx_gtk2u_html-2.8 
                              -lwx_gtk2u_adv-2.8 
                              -lwx_gtk2u_core-2.8 
                              -lwx_baseu_xml-2.8 
                              -lwx_baseu_net-2.8 
                              -lwx_baseu-2.8
                              -lwxsvg
                              -lstockfish)



