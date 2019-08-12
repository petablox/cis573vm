#include "Prereqs.h"

using namespace llvm;

namespace prereqs {
Prereqs::Prereqs() : ModulePass(ID) {}

void Prereqs::print(Module &M) {
  outs() << "Analytics of Module " << M.getName() << "\n";
  outs() << "  # Functions    : " << NumOfFunctions << "\n";
  outs() << "  # Instructions : " << NumOfInstructions << "\n";
}

bool Prereqs::runOnModule(Module &M) {
  /* Implement your pass here */
  print(M);
  return false;
}

char Prereqs::ID = 1;
static RegisterPass<Prereqs> X("Prereqs", "Prereqs", false, false);
} // namespace prereqs
