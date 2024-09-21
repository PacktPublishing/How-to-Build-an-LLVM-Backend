set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH13
        LANGUAGES CXX C)

include(../cmake/utils/set-llvm-install-prefix.cmake)
include(../cmake/utils/llc-run.cmake)

set(CURR_TARGET
  produce-mir
)

set(LLC_RUN_DEPENDENCIES)

# Args are:
# - llc options
# - input file
# - output file
add_run_llc(LLC_RUN_DEPENDENCIES "-stop-before=peephole-opt" "input.ll" "ssa.mir")
add_run_llc(LLC_RUN_DEPENDENCIES "-stop-after=phi-node-elimination" "input.ll" "no-phi.mir")
add_run_llc(LLC_RUN_DEPENDENCIES "-stop-after=virtregmap" "input.ll" "no-vreg.mir")

# Create an executable target that depends on the generated file
add_custom_target(${CURR_TARGET}
    DEPENDS ${LLC_RUN_DEPENDENCIES}
)

set_target_properties(${CURR_TARGET} PROPERTIES EXCLUDE_FROM_ALL 0)
