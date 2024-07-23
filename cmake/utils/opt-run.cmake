# Add a custom command to generate the output by running passes with opt.
# PARENT_VAR is used to accumulate the targets that needs to be built.
function(add_run_opt PARENT_VAR OPT_ARGS INPUT)
    set(INPUT_FULL_PATH ${CMAKE_SOURCE_DIR}/${INPUT})
    string(REPLACE ".ll" ".out.ll" OUTPUT ${INPUT})
    # Spaces are escaped in CMake.
    # To issue spaces, we need to use a list of values.
    # Do the translation here so that at the high level it remains natural and
    # we can use spaces to declare our command line options.
    string(REPLACE " " ";" OPT_ARGS ${OPT_ARGS})
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
        COMMAND ${LLVM_TOOLS_BINARY_DIR}/opt -S ${OPT_ARGS} ${INPUT_FULL_PATH} -o ${OUTPUT_FULL_PATH} > ${REDIRECT} 2>&1
        DEPENDS ${INPUT}
        COMMENT "Generating code with opt"
    )
    list(APPEND ${PARENT_VAR} ${OUTPUT})
    set(${PARENT_VAR} ${${PARENT_VAR}} PARENT_SCOPE)
endfunction()

function(add_run_passes PARENT_VAR OPT_ARGS INPUT)
  set(OPT_ARGS_W_PASS "-passes=${OPT_ARGS}")
  add_run_opt(${PARENT_VAR} ${OPT_ARGS_W_PASS} ${INPUT})
  # Propagate the result back one level.
  set(${PARENT_VAR} ${${PARENT_VAR}} PARENT_SCOPE)
endfunction()

