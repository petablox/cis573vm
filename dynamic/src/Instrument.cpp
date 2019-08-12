#include "Sanitizer.h"

using namespace llvm;

namespace sanitizer {

static const char *SanitizerFunctionName = "__dbz_sanitizer__";
static const char *CoverageFunctionName = "__coverage__";
static const char *CBIBranchFunctionName = "__cbi_branch__";
static const char *CBIReturnFunctionName = "__cbi_return__";

/*
 * Implement divide-by-zero sanitizer. (Lab 2)
 */
void instrumentSanitizer(Module *M, Function &F, Instruction &I) {
}

/*
 * Implement code coverage instrumentation. (Lab 2)
 */
void instrumentCoverage(Module *M, Function &F, Instruction &I) {
}

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

bool Sanitizer::runOnFunction(Function &F) {
  return true;
}

char Sanitizer::ID = 1;
static RegisterPass<Sanitizer>
    X("Instrument", "Instrumentations for Dynamic Analysis", false, false);

} // namespace sanitizer
