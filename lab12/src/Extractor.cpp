#include "Extractor.h"

#include "llvm/IR/CFG.h"
#include "llvm/IR/Instruction.h"

#include "Utils.h"

/* Implement your extractor */
void Extractor::extractConstraints(Instruction *I,
                                   z3::expr_vector &Assertions) {}

void Extractor::initialize(Function &F) {
}

z3::expr_vector Extractor::transition(BasicBlock *BB, BasicBlock *Succ) {
  z3::expr_vector Vec(C);
  return Vec;
}

void Extractor::extractConstraints(BasicBlock *BB) {
}
