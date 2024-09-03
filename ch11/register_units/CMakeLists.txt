set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH11
        LANGUAGES CXX C)

include(../../cmake/utils/set-llvm-install-prefix.cmake)

# Hook up the TableGen tooling.
set(LLVM_TABLEGEN_EXE ${LLVM_TOOLS_BINARY_DIR}/llvm-tblgen)
include(${LLVM_CMAKE_DIR}/AddLLVM.cmake)
include(${LLVM_CMAKE_DIR}/TableGen.cmake)

# Create the different TableGen outputs.
set(LLVM_TARGET_DEFINITIONS solution-reginfo.td)
tablegen(LLVM SolutionRegisterInfo.inc -gen-register-info)

set(LLVM_TARGET_DEFINITIONS yourTurn-reginfo.td)
tablegen(LLVM YourTurnRegisterInfo.inc -gen-register-info)

# Register a target for all the TableGen outputs.
add_public_tablegen_target(CommonTableGen)

# Make that target part of the `all` target.
set_target_properties(CommonTableGen PROPERTIES EXCLUDE_FROM_ALL 0)
