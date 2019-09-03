#include "DataflowAnalysis.h"

using namespace llvm;

namespace dataflow {

//===----------------------------------------------------------------------===//
// Memory Access
//===----------------------------------------------------------------------===//

const char *WhiteSpaces = " \t\n\r";

std::string deref(Value *V) {
  std::string Code;
  raw_string_ostream SS(Code);
  V->print(SS);
  Code.erase(0, Code.find_first_not_of(WhiteSpaces));
  Code = "*(" + Code + ")";
  return Code;
}

std::string variable(Value *V) {
  std::string Code;
  raw_string_ostream SS(Code);
  V->print(SS);
  Code.erase(0, Code.find_first_not_of(WhiteSpaces));
  return Code;
}

std::string address(Value *V) {
  std::string Code;
  raw_string_ostream SS(Code);
  V->print(SS);
  Code.erase(0, Code.find_first_not_of(WhiteSpaces));
  Code = "@(" + Code + ")";
  return Code;
}

//===----------------------------------------------------------------------===//
// Dataflow Analysis Implementation
//===----------------------------------------------------------------------===//

DataflowAnalysis::DataflowAnalysis(char ID) : FunctionPass(ID) {}

void DataflowAnalysis::collectErrorInsts(Function &F) {
  for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
    if (check(&*I))
      ErrorInsts.insert(&*I);
  }
}

bool DataflowAnalysis::runOnFunction(Function &F) {
  outs() << "Running " << getAnalysisName() << " on " << F.getName() << "\n";
  for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
    InMap[&(*I)] = new Memory;
    OutMap[&(*I)] = new Memory;
  }

  doAnalysis(F);

  collectErrorInsts(F);
  outs() << "Instructions that potentially divide by zero: \n";
  for (auto I : ErrorInsts) {
    outs() << *I << "\n";
  }

  for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
    delete InMap[&(*I)];
    delete OutMap[&(*I)];
  }
  return false;
}
} // namespace dataflow
