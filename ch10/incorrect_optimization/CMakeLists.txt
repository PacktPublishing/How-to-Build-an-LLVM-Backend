set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH4
        LANGUAGES CXX C)

include(../../cmake/utils/set-llvm-install-prefix.cmake)

set(CURR_TARGET
  buggy_cst_propagation
)

set(SRC
  "main.cpp"
  "populate_function.cpp"
)

set(INC
)

set(CMAKE_CXX_FLAGS -fno-rtti)

# Now build our tools
add_executable(${CURR_TARGET} ${SRC} ${INC})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core transformutils)

# Link against LLVM libraries
target_link_libraries(${CURR_TARGET} ${llvm_libs})
