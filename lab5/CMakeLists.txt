cmake_minimum_required(VERSION 3.10)

find_package(LLVM 8 REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(HandleLLVMOptions)
include(AddLLVM)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS} include)
link_directories(${LLVM_LIBRARY_DIRS} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SRC_DIR}/reference)

add_llvm_library(DataflowPass MODULE
  src/DataflowAnalysis.cpp
  src/DivZeroAnalysis.cpp
  src/Domain.cpp
  )

target_link_libraries(DataflowPass RefDomain)

add_custom_target(RefDomain ALL
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/reference/* ${CMAKE_CURRENT_BINARY_DIR}/
)
