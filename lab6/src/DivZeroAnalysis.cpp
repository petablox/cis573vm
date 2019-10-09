#include "DivZeroAnalysis.h"

namespace dataflow {

//===----------------------------------------------------------------------===//
// Dataflow Analysis Implementation
//===----------------------------------------------------------------------===//

/**
 * Implement your data-flow analysis.
 * 1. Define "join" that joins the memory state of two flows.
 * 2. Define "order" which states if two memory sets are ordered
 * 3. Define "flowIn" that joins the memory set of all incomming flows
 * 4. Define "transfer" that computes the semantics of each instruction.
 * 5. Define "flowOut" that flows the memory set to all outgoing flows
 * 6. Define "doAnalysis" that stores your results in "InMap" and "OutMap".
 * 7. Define "check" that checks if a given instruction is erroneous or not.
 */


void join(Memory *Result, Memory *M1, Memory *M2) {
  /* Add your code here */
}

bool order(Memory *M1, Memory *M2) {
  /* Add your code here */
}


void DivZeroAnalysis::flowIn(Instruction *I, Memory *In) {
  /* Add your code here */
}


void DivZeroAnalysis::transfer(Instruction *I, const Memory *In, Memory *NOut,
                               PointerAnalysis *PA,
                               SetVector<Value *> PointerSet) {
  /* Add your code here */
}

void DivZeroAnalysis::flowOut(Instruction *I, Memory *Pre, Memory *Post,  SetVector <Instruction *> &WorkSet) {
  /* Add your code here */
}

void DivZeroAnalysis::doAnalysis(Function &F, PointerAnalysis *PA) {
  /* Add your code here */
  SetVector<Instruction *> WorkSet;
  SetVector<Value *> PointerSet;
  for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
    WorkSet.insert(&(*I));
    PointerSet.insert(&(*I));
  }


}

bool DivZeroAnalysis::check(Instruction *I) {
  /* Add your code here */
  return false;
}

char DivZeroAnalysis::ID = 1;
static RegisterPass<DivZeroAnalysis> X("DivZero", "Divide-by-zero Analysis",
                                       false, false);
} // namespace dataflow
