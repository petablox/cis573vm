#ifndef DIV_ZERO_ANALYSIS_H
#define DIV_ZERO_ANALYSIS_H

#include "DataflowAnalysis.h"

namespace dataflow {
struct DivZeroAnalysis : public DataflowAnalysis {
  static char ID;
  DivZeroAnalysis() : DataflowAnalysis(ID) {}

protected:
  void transfer(Instruction *I, const Memory *In, Memory *NOut) override;

  void doAnalysis(Function &F) override;

  bool check(Instruction *I) override;

  std::string getAnalysisName() override { return "DivZero"; }
};
} // namespace dataflow

#endif // DIV_ZERO_ANALYSIS_H
