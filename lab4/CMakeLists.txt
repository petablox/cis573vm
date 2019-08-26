cmake_minimum_required(VERSION 3.10)

find_package(LLVM 8 REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(HandleLLVMOptions)
include(AddLLVM)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

option(USE_REFERENCE "Build with reference solution" OFF)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS} include)
link_directories(${LLVM_LIBRARY_DIRS} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/reference)

if (USE_REFERENCE)
  message(STATUS "Use reference solution")
  add_executable(fuzzer
    src/Fuzzer.cpp
    )
  add_custom_target(RefMutate ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/reference/libMutate.so ${CMAKE_CURRENT_BINARY_DIR}/
  )
  target_link_libraries(fuzzer Mutate)
else (USE_REFERENCE)
  add_executable(fuzzer
    src/Fuzzer.cpp
    src/Mutate.cpp
    )
endif (USE_REFERENCE)

add_custom_target(Instrument ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/reference/InstrumentPass.so ${CMAKE_CURRENT_BINARY_DIR}/
  )

add_library(runtime MODULE
  lib/runtime.c
  )
