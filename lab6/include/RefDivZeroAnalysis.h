#ifndef REF_DIV_ZERO_ANALYSIS_H
#define REF_DIV_ZERO_ANALYSIS_H

#include "DataflowAnalysis.h"

namespace dataflow {

struct RefDivZeroAnalysis : public DataflowAnalysis {
  static char ID;
  RefDivZeroAnalysis() : DataflowAnalysis(ID) {}
  RefDivZeroAnalysis(char ID) : DataflowAnalysis(ID) {}

protected:
  virtual void transfer(Instruction *I, const Memory *In, Memory *NOut,
                        PointerAnalysis *PA,
                        SetVector<Value *> PointerSet) override = 0;

  void doAnalysis(Function &F, PointerAnalysis *PA) override;

  bool check(Instruction *I) override;

  std::string getAnalysisName() override { return "DivZero"; }
};
} // namespace dataflow

#endif // REF_DIV_ZERO_ANALYSIS_H
