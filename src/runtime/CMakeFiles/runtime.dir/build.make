# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kim/jitaas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kim/jitaas

# Include any dependencies generated for this target.
include src/runtime/CMakeFiles/runtime.dir/depend.make

# Include the progress variables for this target.
include src/runtime/CMakeFiles/runtime.dir/progress.make

# Include the compile flags for this target's objects.
include src/runtime/CMakeFiles/runtime.dir/flags.make

src/runtime/CMakeFiles/runtime.dir/main.cpp.o: src/runtime/CMakeFiles/runtime.dir/flags.make
src/runtime/CMakeFiles/runtime.dir/main.cpp.o: src/runtime/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/jitaas/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/runtime/CMakeFiles/runtime.dir/main.cpp.o"
	cd /home/kim/jitaas/src/runtime && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runtime.dir/main.cpp.o -c /home/kim/jitaas/src/runtime/main.cpp

src/runtime/CMakeFiles/runtime.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runtime.dir/main.cpp.i"
	cd /home/kim/jitaas/src/runtime && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kim/jitaas/src/runtime/main.cpp > CMakeFiles/runtime.dir/main.cpp.i

src/runtime/CMakeFiles/runtime.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runtime.dir/main.cpp.s"
	cd /home/kim/jitaas/src/runtime && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kim/jitaas/src/runtime/main.cpp -o CMakeFiles/runtime.dir/main.cpp.s

src/runtime/CMakeFiles/runtime.dir/runtime.cpp.o: src/runtime/CMakeFiles/runtime.dir/flags.make
src/runtime/CMakeFiles/runtime.dir/runtime.cpp.o: src/runtime/runtime.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/jitaas/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/runtime/CMakeFiles/runtime.dir/runtime.cpp.o"
	cd /home/kim/jitaas/src/runtime && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runtime.dir/runtime.cpp.o -c /home/kim/jitaas/src/runtime/runtime.cpp

src/runtime/CMakeFiles/runtime.dir/runtime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runtime.dir/runtime.cpp.i"
	cd /home/kim/jitaas/src/runtime && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kim/jitaas/src/runtime/runtime.cpp > CMakeFiles/runtime.dir/runtime.cpp.i

src/runtime/CMakeFiles/runtime.dir/runtime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runtime.dir/runtime.cpp.s"
	cd /home/kim/jitaas/src/runtime && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kim/jitaas/src/runtime/runtime.cpp -o CMakeFiles/runtime.dir/runtime.cpp.s

src/runtime/CMakeFiles/runtime.dir/runtime-envoy.cpp.o: src/runtime/CMakeFiles/runtime.dir/flags.make
src/runtime/CMakeFiles/runtime.dir/runtime-envoy.cpp.o: src/runtime/runtime-envoy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/jitaas/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/runtime/CMakeFiles/runtime.dir/runtime-envoy.cpp.o"
	cd /home/kim/jitaas/src/runtime && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runtime.dir/runtime-envoy.cpp.o -c /home/kim/jitaas/src/runtime/runtime-envoy.cpp

src/runtime/CMakeFiles/runtime.dir/runtime-envoy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runtime.dir/runtime-envoy.cpp.i"
	cd /home/kim/jitaas/src/runtime && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kim/jitaas/src/runtime/runtime-envoy.cpp > CMakeFiles/runtime.dir/runtime-envoy.cpp.i

src/runtime/CMakeFiles/runtime.dir/runtime-envoy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runtime.dir/runtime-envoy.cpp.s"
	cd /home/kim/jitaas/src/runtime && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kim/jitaas/src/runtime/runtime-envoy.cpp -o CMakeFiles/runtime.dir/runtime-envoy.cpp.s

src/runtime/CMakeFiles/runtime.dir/trampoline.S.o: src/runtime/CMakeFiles/runtime.dir/flags.make
src/runtime/CMakeFiles/runtime.dir/trampoline.S.o: src/runtime/trampoline.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/jitaas/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building ASM object src/runtime/CMakeFiles/runtime.dir/trampoline.S.o"
	cd /home/kim/jitaas/src/runtime && /usr/bin/cc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/runtime.dir/trampoline.S.o -c /home/kim/jitaas/src/runtime/trampoline.S

# Object files for target runtime
runtime_OBJECTS = \
"CMakeFiles/runtime.dir/main.cpp.o" \
"CMakeFiles/runtime.dir/runtime.cpp.o" \
"CMakeFiles/runtime.dir/runtime-envoy.cpp.o" \
"CMakeFiles/runtime.dir/trampoline.S.o"

# External object files for target runtime
runtime_EXTERNAL_OBJECTS =

exe/runtime: src/runtime/CMakeFiles/runtime.dir/main.cpp.o
exe/runtime: src/runtime/CMakeFiles/runtime.dir/runtime.cpp.o
exe/runtime: src/runtime/CMakeFiles/runtime.dir/runtime-envoy.cpp.o
exe/runtime: src/runtime/CMakeFiles/runtime.dir/trampoline.S.o
exe/runtime: src/runtime/CMakeFiles/runtime.dir/build.make
exe/runtime: src/proto/libjacaranda_grpc_proto.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSupport.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMCore.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMPasses.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMOrcJIT.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRuntimeDyld.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMDebugInfoDWARF.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64AsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBPFAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMHexagonAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMLanaiAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMipsAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMSP430AsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMPowerPCAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRISCVAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSparcAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSystemZAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMWebAssemblyAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMX86AsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAVRAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64CodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64AsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64Desc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64Disassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64Info.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64Utils.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUUtils.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMUtils.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBPFCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBPFAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBPFDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBPFDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBPFInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMHexagonCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMHexagonAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMHexagonDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMHexagonDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMHexagonInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMLanaiCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMLanaiAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMLanaiDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMLanaiDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMLanaiInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMipsCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMipsAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMipsDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMipsDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMipsInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMSP430CodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMSP430AsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMSP430Desc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMSP430Disassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMSP430Info.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMNVPTXCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMNVPTXDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMNVPTXInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMPowerPCCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMPowerPCAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMPowerPCDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMPowerPCDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMPowerPCInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRISCVCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRISCVAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRISCVDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRISCVDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRISCVInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRISCVUtils.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSparcCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSparcAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSparcDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSparcDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSparcInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSystemZCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSystemZAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSystemZDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSystemZDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSystemZInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMWebAssemblyCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMWebAssemblyAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMWebAssemblyDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMWebAssemblyDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMWebAssemblyInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMX86CodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMX86AsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMX86Desc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMX86Disassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMX86Info.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMX86Utils.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMXCoreCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMXCoreDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMXCoreDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMXCoreInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAVRCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAVRAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAVRDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAVRDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAVRInfo.a
exe/runtime: /home/kim/.local/lib/libgrpc++_reflection.a
exe/runtime: /home/kim/.local/lib/libgrpc++.a
exe/runtime: /home/kim/.local/lib/libgrpc.a
exe/runtime: /home/kim/.local/lib/libz.a
exe/runtime: /home/kim/.local/lib/libcares.a
exe/runtime: /home/kim/.local/lib/libaddress_sorting.a
exe/runtime: /home/kim/.local/lib/libre2.a
exe/runtime: /home/kim/.local/lib/libabsl_raw_hash_set.a
exe/runtime: /home/kim/.local/lib/libabsl_hashtablez_sampler.a
exe/runtime: /home/kim/.local/lib/libabsl_hash.a
exe/runtime: /home/kim/.local/lib/libabsl_city.a
exe/runtime: /home/kim/.local/lib/libabsl_low_level_hash.a
exe/runtime: /home/kim/.local/lib/libabsl_statusor.a
exe/runtime: /home/kim/.local/lib/libabsl_bad_variant_access.a
exe/runtime: /home/kim/.local/lib/libgpr.a
exe/runtime: /home/kim/.local/lib/libupb.a
exe/runtime: /home/kim/.local/lib/libabsl_status.a
exe/runtime: /home/kim/.local/lib/libabsl_random_distributions.a
exe/runtime: /home/kim/.local/lib/libabsl_random_seed_sequences.a
exe/runtime: /home/kim/.local/lib/libabsl_random_internal_pool_urbg.a
exe/runtime: /home/kim/.local/lib/libabsl_random_internal_randen.a
exe/runtime: /home/kim/.local/lib/libabsl_random_internal_randen_hwaes.a
exe/runtime: /home/kim/.local/lib/libabsl_random_internal_randen_hwaes_impl.a
exe/runtime: /home/kim/.local/lib/libabsl_random_internal_randen_slow.a
exe/runtime: /home/kim/.local/lib/libabsl_random_internal_platform.a
exe/runtime: /home/kim/.local/lib/libabsl_random_internal_seed_material.a
exe/runtime: /home/kim/.local/lib/libabsl_random_seed_gen_exception.a
exe/runtime: /home/kim/.local/lib/libabsl_cord.a
exe/runtime: /home/kim/.local/lib/libabsl_bad_optional_access.a
exe/runtime: /home/kim/.local/lib/libabsl_cordz_info.a
exe/runtime: /home/kim/.local/lib/libabsl_cord_internal.a
exe/runtime: /home/kim/.local/lib/libabsl_cordz_functions.a
exe/runtime: /home/kim/.local/lib/libabsl_exponential_biased.a
exe/runtime: /home/kim/.local/lib/libabsl_cordz_handle.a
exe/runtime: /home/kim/.local/lib/libabsl_str_format_internal.a
exe/runtime: /home/kim/.local/lib/libabsl_synchronization.a
exe/runtime: /home/kim/.local/lib/libabsl_stacktrace.a
exe/runtime: /home/kim/.local/lib/libabsl_symbolize.a
exe/runtime: /home/kim/.local/lib/libabsl_debugging_internal.a
exe/runtime: /home/kim/.local/lib/libabsl_demangle_internal.a
exe/runtime: /home/kim/.local/lib/libabsl_graphcycles_internal.a
exe/runtime: /home/kim/.local/lib/libabsl_malloc_internal.a
exe/runtime: /home/kim/.local/lib/libabsl_time.a
exe/runtime: /home/kim/.local/lib/libabsl_strings.a
exe/runtime: /home/kim/.local/lib/libabsl_throw_delegate.a
exe/runtime: /home/kim/.local/lib/libabsl_int128.a
exe/runtime: /home/kim/.local/lib/libabsl_strings_internal.a
exe/runtime: /home/kim/.local/lib/libabsl_base.a
exe/runtime: /home/kim/.local/lib/libabsl_spinlock_wait.a
exe/runtime: /home/kim/.local/lib/libabsl_raw_logging_internal.a
exe/runtime: /home/kim/.local/lib/libabsl_log_severity.a
exe/runtime: /home/kim/.local/lib/libabsl_civil_time.a
exe/runtime: /home/kim/.local/lib/libabsl_time_zone.a
exe/runtime: /home/kim/.local/lib/libssl.a
exe/runtime: /home/kim/.local/lib/libcrypto.a
exe/runtime: /home/kim/.local/lib/libprotobuf.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMPasses.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMExecutionEngine.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRuntimeDyld.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMJITLink.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64Desc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64Info.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAArch64Utils.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMIRParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAMDGPUUtils.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMARMUtils.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMHexagonDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMHexagonInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMLanaiDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMLanaiInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMipo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMInstrumentation.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMVectorize.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMIRReader.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAsmParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMLinker.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSystemZDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSystemZInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMWebAssemblyDesc.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMWebAssemblyInfo.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMGlobalISel.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAsmPrinter.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMDebugInfoDWARF.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSelectionDAG.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMCodeGen.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMScalarOpts.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAggressiveInstCombine.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMInstCombine.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBitWriter.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMTarget.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMTransformUtils.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMAnalysis.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMObject.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBitReader.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBitstreamReader.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMCParser.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMProfileData.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMCore.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMRemarks.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMCDisassembler.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMMC.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMBinaryFormat.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMDebugInfoCodeView.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMDebugInfoMSF.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMSupport.a
exe/runtime: /usr/lib/llvm-9/lib/libLLVMDemangle.a
exe/runtime: src/runtime/CMakeFiles/runtime.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kim/jitaas/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../../exe/runtime"
	cd /home/kim/jitaas/src/runtime && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runtime.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/runtime/CMakeFiles/runtime.dir/build: exe/runtime

.PHONY : src/runtime/CMakeFiles/runtime.dir/build

src/runtime/CMakeFiles/runtime.dir/clean:
	cd /home/kim/jitaas/src/runtime && $(CMAKE_COMMAND) -P CMakeFiles/runtime.dir/cmake_clean.cmake
.PHONY : src/runtime/CMakeFiles/runtime.dir/clean

src/runtime/CMakeFiles/runtime.dir/depend:
	cd /home/kim/jitaas && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kim/jitaas /home/kim/jitaas/src/runtime /home/kim/jitaas /home/kim/jitaas/src/runtime /home/kim/jitaas/src/runtime/CMakeFiles/runtime.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/runtime/CMakeFiles/runtime.dir/depend

