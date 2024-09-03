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
tablegen(LLVM SolutionGenRegisterInfo.inc -gen-register-info)

set(LLVM_TARGET_DEFINITIONS yourTurn-reginfo.td)
tablegen(LLVM YourTurnGenRegisterInfo.inc -gen-register-info)

# Register a target for all the TableGen outputs.
add_public_tablegen_target(CommonTableGen)

# Make that target part of the `all` target.
set_target_properties(CommonTableGen PROPERTIES EXCLUDE_FROM_ALL 0)

set(CURR_TARGET
  print_regunit
)

set(SRC
  "main.cpp"
  "SolutionRegisterInfo.cpp"
  "YourTurnRegisterInfo.cpp"
)

set(INC
  "SolutionRegisterInfo.h"
  "YourTurnRegisterInfo.h"
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

# Now build our tools
add_executable(${CURR_TARGET} ${SRC} ${INC})
add_dependencies(${CURR_TARGET} CommonTableGen)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core mc codegen)

# Link against LLVM libraries
target_link_libraries(${CURR_TARGET} ${llvm_libs})

# To find the generated files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR})
