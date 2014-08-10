set (sf_build_command  make build ARCH=${DETECTEDARCH})

add_custom_target ( stockfish_lib 
                    COMMAND ${sf_build_command}             
                    WORKING_DIRECTORY ${stockfishdir}                                             
                    COMMENT "building stockfish..."
                    VERBATIM)


