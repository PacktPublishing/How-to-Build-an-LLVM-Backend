set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.22)

project(CH3
        LANGUAGES CXX)

set(CURR_TARGET
  build_mir
)

set(SRC
  "main.cpp"
  "solution/populate_function.cpp"
  "your_turn/populate_function.cpp"
)

set(INC
)

add_executable(${CURR_TARGET} ${SRC} ${INC})

# I shouldn't need this: fix find_package
target_link_directories(${CURR_TARGET}
PUBLIC
/Users/qcolombet/utils/homebrew/lib/
/Library/Developer/CommandLineTools/SDKs/MacOSX14.2.sdk/usr/lib/
)

# To find the particular dependencies a an llvm library use:
# llvm-config --libs  <lib>
# E.g., llvm-config --libs  core 
target_link_libraries(${CURR_TARGET}
LLVMAArch64AsmParser
LLVMAArch64CodeGen
LLVMAArch64Desc
LLVMAArch64Disassembler
LLVMAArch64Info
LLVMAArch64Utils
LLVMAMDGPUAsmParser
LLVMAMDGPUCodeGen
LLVMAMDGPUDesc
LLVMAMDGPUDisassembler
LLVMAMDGPUInfo
LLVMAMDGPUTargetMCA
LLVMAMDGPUUtils
LLVMAggressiveInstCombine
LLVMAnalysis
LLVMAsmParser
LLVMAsmPrinter
LLVMBinaryFormat
LLVMBitReader
LLVMBitWriter
LLVMBitstreamReader
LLVMCFGuard
LLVMCodeGen
LLVMCodeGenTypes
LLVMCore
LLVMCoroutines
LLVMCoverage
LLVMDWARFLinker
LLVMDWARFLinkerClassic
LLVMDWARFLinkerParallel
LLVMDWP
LLVMDebugInfoBTF
LLVMDebugInfoCodeView
LLVMDebugInfoDWARF
LLVMDebugInfoGSYM
LLVMDebugInfoLogicalView
LLVMDebugInfoMSF
LLVMDebugInfoPDB
LLVMDemangle
LLVMDlltoolDriver
LLVMExecutionEngine
LLVMExtensions
LLVMFileCheck
LLVMFrontendDriver
LLVMFrontendHLSL
LLVMFrontendOffloading
LLVMFrontendOpenACC
LLVMFrontendOpenMP
LLVMFuzzMutate
LLVMFuzzerCLI
LLVMGlobalISel
LLVMHipStdPar
LLVMIRPrinter
LLVMIRReader
LLVMInstCombine
LLVMInstrumentation
LLVMInterfaceStub
LLVMInterpreter
LLVMJITLink
LLVMLTO
LLVMLibDriver
LLVMLineEditor
LLVMLinker
LLVMMC
LLVMMCA
LLVMMCDisassembler
LLVMMCJIT
LLVMMCParser
LLVMMIRParser
LLVMObjCARCOpts
LLVMObjCopy
LLVMObject
LLVMObjectYAML
LLVMOption
LLVMOrcDebugging
LLVMOrcJIT
LLVMOrcShared
LLVMOrcTargetProcess
LLVMPasses
LLVMProfileData
LLVMRemarks
LLVMRuntimeDyld
LLVMScalarOpts
LLVMSelectionDAG
LLVMSupport
LLVMSymbolize
LLVMTableGen
LLVMTarget
LLVMTargetParser
LLVMTextAPI
LLVMTextAPIBinaryReader
LLVMTransformUtils
LLVMVectorize
LLVMWindowsDriver
LLVMWindowsManifest
LLVMX86AsmParser
LLVMX86CodeGen
LLVMX86Desc
LLVMX86Disassembler
LLVMX86Info
LLVMX86TargetMCA
LLVMXRay
LLVMipo
  zstd
  z
  ncurses # LLVMSupport has some dependencies on the terminal
)

# Add the search path for LLVM.
include(../../cmake/utils/set-llvm-install-prefix.cmake)

