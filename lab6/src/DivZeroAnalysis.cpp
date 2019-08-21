#include "DivZeroAnalysis.h"

namespace dataflow {

//===----------------------------------------------------------------------===//
// Dataflow Analysis Implementation
//===----------------------------------------------------------------------===//

/**
 * Implement your transfer function.
 */

void DivZeroAnalysis::transfer(Instruction *I, const Memory *In, Memory *NOut,
                               PointerAnalysis *PA,
                               SetVector<Value *> PointerSet) {}

void DivZeroAnalysis::doAnalysis(Function &F, PointerAnalysis *PA) {
  /**
   * If you want to use your own implementation replace this line.
   */
  RefDivZeroAnalysis::doAnalysis(F, PA);
}

bool DivZeroAnalysis::check(Instruction *I) {
  /**
   * If you want to use your own implementation replace this line.
   */
  return RefDivZeroAnalysis::check(I);
}

char DivZeroAnalysis::ID = 1;
static RegisterPass<DivZeroAnalysis> X("DivZero", "Divide-by-zero Analysis",
                                       false, false);
} // namespace dataflow
