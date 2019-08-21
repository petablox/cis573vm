#ifndef DIV_ZERO_ANALYSIS_H
#define DIV_ZERO_ANALYSIS_H

#include "RefDivZeroAnalysis.h"

namespace dataflow {

/* If you do not want to use reference solution, replace the class definition
 * to the following three lines
 */
/*
struct DivZeroAnalysis : public DataflowAnalysis {
  static char ID;
  DivZeroAnalysis() : DataflowAnalysis(ID) {}
*/
struct DivZeroAnalysis : public RefDivZeroAnalysis {
  static char ID;
  DivZeroAnalysis() : RefDivZeroAnalysis(ID) {}

protected:
  void transfer(Instruction *I, const Memory *In, Memory *NOut,
                PointerAnalysis *PA, SetVector<Value *> PointerSet) override;

  void doAnalysis(Function &F, PointerAnalysis *PA) override;

  bool check(Instruction *I) override;

  std::string getAnalysisName() override { return "DivZero"; }
};
} // namespace dataflow

#endif // REF_DIV_ZERO_ANALYSIS_H
