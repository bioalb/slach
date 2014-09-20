#this is the command to compile stockfish, from their documentation
set (sf_build_command  make build ARCH=${DETECTEDARCH})
add_custom_target (stockfish_engine ALL
                   COMMAND ${sf_build_command}             
                   WORKING_DIRECTORY ${stockfishdir}                                             
                   COMMENT "building stockfish..."
                   VERBATIM)


