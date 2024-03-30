set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH5
        LANGUAGES CXX C)

include(../../cmake/utils/set-llvm-install-prefix.cmake)

set(CURR_TARGET
  your_first_pipeline
)

set(SRC
  "main.cpp"
  "solution/passPipelineWithNewPM.cpp"
  "solution/passPipelineWithLegacyPM.cpp"
  "your_turn/passPipelineWithNewPM.cpp"
  "your_turn/passPipelineWithLegacyPM.cpp"
)

set(INC
)

set(CMAKE_CXX_FLAGS -fno-rtti)

# Now build our tools
add_executable(${CURR_TARGET} ${SRC} ${INC})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core transformutils passes ipo)

# Link against LLVM libraries
target_link_libraries(${CURR_TARGET} ${llvm_libs})
