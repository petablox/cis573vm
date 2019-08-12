#include "DataflowAnalysis.h"

namespace dataflow {

//===----------------------------------------------------------------------===//
// Abstract Domain Implementation
//===----------------------------------------------------------------------===//

/*
 * Implement your abstract domain. (Lab 1, 5)
 */
class Domain {
};

//===----------------------------------------------------------------------===//
// DivZero Analysis Implementation
//===----------------------------------------------------------------------===//

/**
 * Implement your data-flow analysis. (Lab 1, 5, and 6)
 * 1. Define "doAnalysis" that stores your results in "InMap" and "OutMap".
 * 2. Define "check" that checks if a given instruction is erroneous or not.
 */

void DivZeroAnalysis::doAnalysis(Function &F, PointerAnalysis *PA) {}

bool DivZeroAnalysis::check(Instruction *I) { return false; }

char DivZeroAnalysis::ID = 1;
static RegisterPass<DivZeroAnalysis> X("DivZero", "Divide-by-zero Analysis",
                                       false, false);
//===----------------------------------------------------------------------===//
// Pointer Analysis Implementation
//===----------------------------------------------------------------------===//

/*
 * Implement your pointer analysis. (Lab 6)
 * 1. Define "PointerAnalysis" that stores your results in "PointsTo".
 * 2. Define "alias" that checks whether two pointers may alias each other.
 */

PointerAnalysis::PointerAnalysis(Function &F) {}

bool PointerAnalysis::alias(std::string &Ptr1, std::string &Ptr2) const {
  return false;
}
} // namespace dataflow
