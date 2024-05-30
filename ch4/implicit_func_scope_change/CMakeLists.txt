set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH3
        LANGUAGES CXX)

set(CURR_TARGET
  implicit_change_of_scope
)

set(SRC
  "main.cpp"
)

set(INC
)

add_executable(${CURR_TARGET} ${SRC} ${INC})

# To find the particular dependencies a an llvm library use:
# llvm-config --libs  <lib>
# E.g., llvm-config --libs  core 
target_link_libraries(${CURR_TARGET}
  LLVMAsmParser # parseAssemblyString
  LLVMBinaryFormat # dep from core
  LLVMBitstreamReader # dep from core
  LLVMCore # IR and co.
  LLVMDemangle # dep for core
  LLVMSupport # errs
  LLVMRemarks # dep for core
  LLVMTargetParser # dep for core
  ncurses # LLVMSupport has some dependencies on the terminal
)

# Add the search path for LLVM.
include(../../cmake/utils/set-llvm-install-prefix.cmake)

