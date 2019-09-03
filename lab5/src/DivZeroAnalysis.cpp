#include "DivZeroAnalysis.h"

namespace dataflow {

//===----------------------------------------------------------------------===//
// DivZero Analysis Implementation
//===----------------------------------------------------------------------===//

/**
 * Implement your data-flow analysis.
 * 1. Define "transfer" that computes the semantics of each instruction.
 * 2. Define "doAnalysis" that stores your results in "InMap" and "OutMap".
 * 3. Define "check" that checks if a given instruction is erroneous or not.
 */

void DivZeroAnalysis::transfer(Instruction *I, const Memory *In, Memory *NOut) {
  /* Add your code here */
}

void DivZeroAnalysis::doAnalysis(Function &F) { /* Add your code here */ }

bool DivZeroAnalysis::check(Instruction *I) {
  /* Add your code here */
  return false;
}

char DivZeroAnalysis::ID = 1;
static RegisterPass<DivZeroAnalysis> X("DivZero", "Divide-by-zero Analysis",
                                       false, false);
} // namespace dataflow
