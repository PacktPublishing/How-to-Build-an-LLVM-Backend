set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH8
        LANGUAGES CXX C)

include(../../cmake/utils/set-llvm-install-prefix.cmake)
include(../../cmake/utils/opt-run.cmake)

set(CURR_TARGET
  hadd_vector_log
)

set(OPT_RUN_DEPENDENCIES)
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
