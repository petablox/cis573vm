#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"

#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include <fstream>

#include "DummyLLParser.h"
#include "Extractor.h"
#include "Parser.h"

using namespace llvm;

int main(int argc, char **argv) {
  if (argc < 2) {
    errs() << "Expected an argument - IR file name\n";
    exit(1);
  }

  LLVMContext Context;
  SMDiagnostic Err;
  StringRef FileName(argv[1]);

  std::unique_ptr<Module> Mod =
      parseAssemblyFile(FileName, Err, Context, false);

  if (!Mod) {
    Err.print(argv[0], errs());
    return 1;
  }

  Extractor Ext;
  z3::solver *Solver = Ext.getSolver();
  z3::context &C = Ext.getContext();
  z3::func_decl &TypeEnv = Ext.getTypeEnv();

  for (auto &F : *Mod) {
    for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; I++) {
      Ext.extractConstraints(&*I);
    }
  }

  std::ofstream smt2("formula.smt2");
  smt2 << Solver->to_smt2() << std::endl;
  z3::check_result Result = Solver->check();
  std::cout << Result << std::endl;
  if (Result == z3::sat) {
    const z3::model &Model = Solver->get_model();
    for (auto &F : *Mod) {
      std::cout << "  " << F.getName().str() << " : "
                << Model.eval(TypeEnv(C.string_val(F.getName()))) << std::endl;
      for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; I++) {
        if ((*I).getType()->isVoidTy())
          continue;
        std::string Exp = Ext.toString(&*I);
        std::cout << Exp << " : "
                  << Model.eval(TypeEnv(C.string_val(Exp.c_str())))
                  << std::endl;
      }
    }
  }
}
