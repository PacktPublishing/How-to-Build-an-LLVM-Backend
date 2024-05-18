set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH7
        LANGUAGES CXX C)

include(../cmake/utils/set-llvm-install-prefix.cmake)

set(CURR_TARGET
  check_vec_int_ty
)

set(SRC
  "check_vec_int_ty.cpp"
)

set(INC
)

set(CMAKE_CXX_FLAGS -fno-rtti)

# Now build our tools
add_executable(${CURR_TARGET} ${SRC} ${INC})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(${CURR_TARGET} ${llvm_libs})
