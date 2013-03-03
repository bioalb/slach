#short-hand for the srcdir 
SET(srcdir ${CMAKE_SOURCE_DIR}/src)

#most of this from the wx widgets documentation
ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 
                -D_LARGE_FILES 
                -D__WXGTK__ 
                -I/usr/lib/i386-linux-gnu/wx/include/gtk2-unicode-release-2.8 
                -I/usr/include/wx-2.8
                -I/usr/include/wxSVG 
                 -O0 -g3 -Wall -fmessage-length=0 -finstrument-functions)

ADD_EXECUTABLE(slach ${srcdir}/ChessBoard.cpp
                       ${srcdir}/Square.cpp
                       ${srcdir}/GUI/SquarePanel.cpp 
                       ${srcdir}/GUI/RightPanel.cpp 
                       ${srcdir}/GUI/MainPanel.cpp 
                       ${srcdir}/GUI/MainFrame.cpp 
                       ${srcdir}/GUI/ChessboardPanel.cpp 
                       ${srcdir}/GUI/BottomPanel.cpp 
                       ${srcdir}/GUI/slach.cpp)

link_directories (/usr/lib/i386-linux-gnu) 

#most of this from the wx widgets documentation
TARGET_LINK_LIBRARIES(slach -lwx_gtk2u_richtext-2.8 
                              -lwx_gtk2u_aui-2.8 
                              -lwx_gtk2u_xrc-2.8 
                              -lwx_gtk2u_qa-2.8 
                              -lwx_gtk2u_html-2.8 
                              -lwx_gtk2u_adv-2.8 
                              -lwx_gtk2u_core-2.8 
                              -lwx_baseu_xml-2.8 
                              -lwx_baseu_net-2.8 
                              -lwx_baseu-2.8
                              -lwxsvg)



