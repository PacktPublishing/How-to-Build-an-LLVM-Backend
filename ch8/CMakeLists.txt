set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH8
        LANGUAGES CXX C)

include(../cmake/utils/set-llvm-install-prefix.cmake)
include(../cmake/utils/opt-run.cmake)

set(CURR_TARGET
  produce-ir
)

set(OPT_RUN_DEPENDENCIES)

# Add the canonicalization examples.
add_run_passes(OPT_RUN_DEPENDENCIES "instcombine" canonical_form.ll)
add_run_passes(OPT_RUN_DEPENDENCIES "instcombine" xor.ll)
# Add the value tracking examples.
add_run_passes(OPT_RUN_DEPENDENCIES "instcombine" value_tracking.ll)

# Add all the examples which have the same filename as the pass name.
set(standard_passes
    lcssa
    argpromotion
    dce
    deadargelim
    indvars
    inline
    licm
    load-store-vectorizer
    loop-reduce
    loop-unroll
    loop-vectorize
    reassociate
    simplifycfg
    slp-vectorizer
)

foreach(standard_pass IN LISTS standard_passes)
  add_run_passes(OPT_RUN_DEPENDENCIES "${standard_pass}" ${standard_pass}.ll)
endforeach()

# Create an executable target that depends on the generated file
add_custom_target(${CURR_TARGET}
    DEPENDS ${OPT_RUN_DEPENDENCIES}
)

set_target_properties(${CURR_TARGET} PROPERTIES EXCLUDE_FROM_ALL 0)
