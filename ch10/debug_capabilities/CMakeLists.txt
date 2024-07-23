set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH8
        LANGUAGES CXX C)

include(../../cmake/utils/set-llvm-install-prefix.cmake)

set(CURR_TARGET
  hadd_vector_log
)

set(OPT_RUN_DEPENDENCIES)

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

# Normal run.
add_run_opt(OPT_RUN_DEPENDENCIES "-O3" hadd_vector.ll)
# Run with print of the IR after all.
add_run_opt(OPT_RUN_DEPENDENCIES "-O3 -print-after-all" hadd_vector.ll print_after_all)
# Run with print of only the part we want.
add_run_opt(OPT_RUN_DEPENDENCIES "-O3 -print-module-scope -print-before=slp-vectorizer" hadd_vector.ll print_before_slp_vectorizer)
# Run the SLP vectorizer with debug log enabled.
# Note: this works only if the provided LLVM was built with asserts.
add_run_opt(OPT_RUN_DEPENDENCIES "-passes=slp-vectorizer -debug-only=SLP" before_slp_vectorizer_hadd_vector.ll debug_slp_vectorizer)

# Create an executable target that depends on the generated file
add_custom_target(${CURR_TARGET}
    DEPENDS ${OPT_RUN_DEPENDENCIES}
)

set_target_properties(${CURR_TARGET} PROPERTIES EXCLUDE_FROM_ALL 0)
