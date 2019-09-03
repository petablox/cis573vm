#include "PointerAnalysis.h"

#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"

#include "DataflowAnalysis.h"

namespace dataflow {

//===----------------------------------------------------------------------===//
// Pointer Analysis Implementation
//===----------------------------------------------------------------------===//

/*
 * Implement your pointer analysis. (Lab 6)
 * 1. Define "PointerAnalysis" that stores your results in "PointsTo".
 * 2. Define "alias" that checks whether two pointers may alias each other.
 */

PointerAnalysis::PointerAnalysis(Function &F) { /* Add your code here */ }

bool PointerAnalysis::alias(std::string &Ptr1, std::string &Ptr2) const {
  /* Add your code here */
  return false;
}
}; // namespace dataflow
