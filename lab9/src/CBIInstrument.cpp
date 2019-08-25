#include "CBIInstrument.h"

using namespace llvm;

namespace instrument {

static const char *CBIBranchFunctionName = "__cbi_branch__";
static const char *CBIReturnFunctionName = "__cbi_return__";

/*
 * Implement instrumentation for the branch scheme of CBI. (Lab 9)
 */
void instrumentCBIBranches(Module *M, Function &F, BranchInst &I) {
}

/*
 * Implement instrumentation for the return scheme of CBI. (Lab 9)
 */
void instrumentCBIReturns(Module *M, Function &F, CallInst &I) {
}

bool CBIInstrument::runOnFunction(Function &F) { return true; }

char CBIInstrument::ID = 1;
static RegisterPass<CBIInstrument> X("CBIInstrument",
                                     "Instrumentations for CBI", false, false);

} // namespace instrument
