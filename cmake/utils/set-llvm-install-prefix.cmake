# Helper cmake file to set the include and library search paths.
# We could use find_package, but this is something more custom.

if(NOT DEFINED LLVM_INSTALL_PREFIX)
  message(FATAL_ERROR
 "You must set LLVM_INSTALL_PREFIX.\n"
 "This variable must point to your LLVM installation.\n"
 "To build and install LLVM, "
 "Follow Chapter 1's steps, while setting the CMAKE_INSTALL_PREFIX variable.\n"
 "Then build the 'install' target.\n"
 "Finally feed your install prefix pass to this cmake.\n")
endif()

# Setup the search paths for LLVM related things.
# includes.
target_include_directories(${CURR_TARGET} PUBLIC
   ${LLVM_INSTALL_PREFIX}/include
)

# libaries.
target_link_directories(${CURR_TARGET} PUBLIC
   ${LLVM_INSTALL_PREFIX}/lib
)

