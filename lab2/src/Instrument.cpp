#include "Instrument.h"

using namespace llvm;

namespace instrument {

static const char *SanitizerFunctionName = "__dbz_sanitizer__";
static const char *CoverageFunctionName = "__coverage__";

/*
 * Implement divide-by-zero sanitizer.
 */
void instrumentSanitizer(Module *M, Function &F, Instruction &I) {}

/*
 * Implement code coverage instrumentation.
 */
void instrumentCoverage(Module *M, Function &F, Instruction &I) {}

bool Instrument::runOnFunction(Function &F) { return true; }

char Instrument::ID = 1;
static RegisterPass<Instrument>
    X("Instrument", "Instrumentations for Dynamic Analysis", false, false);

} // namespace instrument
