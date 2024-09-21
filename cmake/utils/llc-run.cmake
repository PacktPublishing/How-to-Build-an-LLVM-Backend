# Add a custom command to generate the output by running passes with llc.
# PARENT_VAR is used to accumulate the targets that needs to be built.
function(add_run_llc PARENT_VAR LLC_ARGS INPUT)
    set(INPUT_FULL_PATH ${CMAKE_SOURCE_DIR}/${INPUT})
    string(REPLACE ".ll" ".out.mir" OUTPUT ${INPUT})
    # Spaces are escaped in CMake.
    # To issue spaces, we need to use a list of values.
    # Do the translation here so that at the high level it remains natural and
    # we can use spaces to declare our command line llcions.
    string(REPLACE " " ";" LLC_ARGS ${LLC_ARGS})
    if(${ARGC} GREATER 3)
      set(OUTPUT "${ARGV3}_${OUTPUT}")
    endif()
    set(OUTPUT_FULL_PATH ${CMAKE_BINARY_DIR}/${OUTPUT})
    set(REDIRECT "/dev/null")
    if(${ARGC} GREATER 3)
      set(REDIRECT "${OUTPUT_FULL_PATH}.txt")
    endif()
    add_custom_command(
        OUTPUT ${OUTPUT}
        COMMAND ${LLVM_TOOLS_BINARY_DIR}/llc ${LLC_ARGS} ${INPUT_FULL_PATH} -o ${OUTPUT_FULL_PATH} > ${REDIRECT} 2>&1
        DEPENDS ${INPUT}
        COMMENT "Generating code with llc"
    )
    list(APPEND ${PARENT_VAR} ${OUTPUT})
    set(${PARENT_VAR} ${${PARENT_VAR}} PARENT_SCOPE)
endfunction()
