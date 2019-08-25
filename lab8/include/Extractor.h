#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"

#include "z3++.h"

using namespace llvm;

class Extractor {
public:
  Extractor() { Solver = new z3::solver(C); }
  ~Extractor() { delete Solver; }

  z3::solver *getSolver() { return Solver; }
  z3::context &getContext() { return C; }
  z3::func_decl &getTypeEnv() { return TypeEnv; }
  const z3::expr getTypeVoid() { return TypeVoid; }
  const z3::expr getTypeI32() { return TypeI32; }
  const z3::expr getTypeI8() { return TypeI8; }
  const z3::expr getTypeI1() { return TypeI1; }
  const z3::expr getTypePtr() { return TypePtr; }
  const z3::expr getTypeApp() { return TypeApp; }

  void extractConstraints(Instruction *I);

  static std::string toString(Value *I) {
    std::string Str;
    raw_string_ostream SS(Str);
    I->print(SS);
    return SS.str();
  }

  static std::string toString(Type *T) {
    std::string Str;
    raw_string_ostream SS(Str);
    T->print(SS);
    return SS.str();
  }

private:
  const char *TypeVoidSymbol = "void";
  const char *TypeI32Symbol = "i32";
  const char *TypeI8Symbol = "i8";
  const char *TypeI1Symbol = "i1";
  const char *PtrSymbol = "*";
  const char *AppSymbol = "->";

  z3::context C;
  z3::solver *Solver;
  z3::check_result Result;
  z3::sort LLVMType = C.string_sort();
  z3::sort LLVMExpr = C.string_sort();
  z3::func_decl TypeEnv = C.function("TypeEnv", LLVMExpr, LLVMType);
  const z3::expr TypeVoid = C.string_val(TypeVoidSymbol);
  const z3::expr TypeI32 = C.string_val(TypeI32Symbol);
  const z3::expr TypeI8 = C.string_val(TypeI8Symbol);
  const z3::expr TypeI1 = C.string_val(TypeI1Symbol);
  const z3::expr TypePtr = C.string_val(PtrSymbol);
  const z3::expr TypeApp = C.string_val(AppSymbol);

  z3::expr ptrOf(z3::expr E) { return z3::concat(E, TypePtr); }

  z3::expr retOf(z3::expr E) {
    z3::expr I = z3::indexof(E, TypeApp, C.int_val(0)) + C.int_val(2);
    return E.extract(I, E.length());
  }
};

#endif // EXTRACTOR_H
