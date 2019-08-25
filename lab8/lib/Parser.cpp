//===- Parser.cpp - Main dispatch module for the Parser library -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This library implements the functionality defined in llvm/AsmParser/Parser.h
//
//===----------------------------------------------------------------------===//

#include "llvm/AsmParser/Parser.h"
#include "DummyLLParser.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/ModuleSummaryIndex.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include <cstring>
#include <system_error>
using namespace llvm;

bool parseAssemblyInto(MemoryBufferRef F, Module *M, ModuleSummaryIndex *Index,
                       SMDiagnostic &Err, bool TypeCheck, SlotMapping *Slots,
                       bool UpgradeDebugInfo, StringRef DataLayoutString) {
  SourceMgr SM;
  std::unique_ptr<MemoryBuffer> Buf = MemoryBuffer::getMemBuffer(F);
  SM.AddNewSourceBuffer(std::move(Buf), SMLoc());
  LLVMContext Context;
  return DummyLLParser(F.getBuffer(), SM, Err, M, Index,
                       M ? M->getContext() : Context, TypeCheck, Slots,
                       UpgradeDebugInfo, DataLayoutString)
      .Run();
}

std::unique_ptr<Module> parseAssembly(MemoryBufferRef F, SMDiagnostic &Err,
                                      LLVMContext &Context, bool TypeCheck,
                                      SlotMapping *Slots, bool UpgradeDebugInfo,
                                      StringRef DataLayoutString) {
  std::unique_ptr<Module> M =
      make_unique<Module>(F.getBufferIdentifier(), Context);

  if (parseAssemblyInto(F, M.get(), nullptr, Err, TypeCheck, Slots,
                        UpgradeDebugInfo, DataLayoutString))
    return nullptr;

  return M;
}

std::unique_ptr<Module> parseAssemblyFile(StringRef Filename, SMDiagnostic &Err,
                                          LLVMContext &Context, bool TypeCheck,
                                          SlotMapping *Slots,
                                          bool UpgradeDebugInfo,
                                          StringRef DataLayoutString) {
  ErrorOr<std::unique_ptr<MemoryBuffer>> FileOrErr =
      MemoryBuffer::getFileOrSTDIN(Filename);
  if (std::error_code EC = FileOrErr.getError()) {
    Err = SMDiagnostic(Filename, SourceMgr::DK_Error,
                       "Could not open input file: " + EC.message());
    return nullptr;
  }

  return parseAssembly(FileOrErr.get()->getMemBufferRef(), Err, Context,
                       TypeCheck, Slots, UpgradeDebugInfo, DataLayoutString);
}

std::unique_ptr<Module>
parseAssemblyString(StringRef AsmString, SMDiagnostic &Err,
                    LLVMContext &Context, SlotMapping *Slots,
                    bool UpgradeDebugInfo, StringRef DataLayoutString) {
  MemoryBufferRef F(AsmString, "<string>");
  return parseAssembly(F, Err, Context, Slots, UpgradeDebugInfo,
                       DataLayoutString);
}

static bool parseSummaryIndexAssemblyInto(MemoryBufferRef F,
                                          ModuleSummaryIndex &Index,
                                          SMDiagnostic &Err) {
  SourceMgr SM;
  std::unique_ptr<MemoryBuffer> Buf = MemoryBuffer::getMemBuffer(F);
  SM.AddNewSourceBuffer(std::move(Buf), SMLoc());

  // The parser holds a reference to a context that is unused when parsing the
  // index, but we need to initialize it.
  LLVMContext unusedContext;
  return DummyLLParser(F.getBuffer(), SM, Err, nullptr, &Index, unusedContext)
      .Run();
}

std::unique_ptr<ModuleSummaryIndex>
parseSummaryIndexAssemblyFile(StringRef Filename, SMDiagnostic &Err) {
  ErrorOr<std::unique_ptr<MemoryBuffer>> FileOrErr =
      MemoryBuffer::getFileOrSTDIN(Filename);
  if (std::error_code EC = FileOrErr.getError()) {
    Err = SMDiagnostic(Filename, SourceMgr::DK_Error,
                       "Could not open input file: " + EC.message());
    return nullptr;
  }

  return parseSummaryIndexAssembly(FileOrErr.get()->getMemBufferRef(), Err);
}

Constant *parseConstantValue(StringRef Asm, SMDiagnostic &Err, const Module &M,
                             const SlotMapping *Slots) {
  SourceMgr SM;
  std::unique_ptr<MemoryBuffer> Buf = MemoryBuffer::getMemBuffer(Asm);
  SM.AddNewSourceBuffer(std::move(Buf), SMLoc());
  Constant *C;
  if (DummyLLParser(Asm, SM, Err, const_cast<Module *>(&M), nullptr,
                    M.getContext())
          .parseStandaloneConstantValue(C, Slots))
    return nullptr;
  return C;
}

Type *parseType(StringRef Asm, SMDiagnostic &Err, const Module &M,
                const SlotMapping *Slots) {
  unsigned Read;
  Type *Ty = parseTypeAtBeginning(Asm, Read, Err, M, Slots);
  if (!Ty)
    return nullptr;
  if (Read != Asm.size()) {
    SourceMgr SM;
    std::unique_ptr<MemoryBuffer> Buf = MemoryBuffer::getMemBuffer(Asm);
    SM.AddNewSourceBuffer(std::move(Buf), SMLoc());
    Err = SM.GetMessage(SMLoc::getFromPointer(Asm.begin() + Read),
                        SourceMgr::DK_Error, "expected end of string");
    return nullptr;
  }
  return Ty;
}
Type *parseTypeAtBeginning(StringRef Asm, unsigned &Read, SMDiagnostic &Err,
                           const Module &M, const SlotMapping *Slots) {
  SourceMgr SM;
  std::unique_ptr<MemoryBuffer> Buf = MemoryBuffer::getMemBuffer(Asm);
  SM.AddNewSourceBuffer(std::move(Buf), SMLoc());
  Type *Ty;
  if (DummyLLParser(Asm, SM, Err, const_cast<Module *>(&M), nullptr,
                    M.getContext())
          .parseTypeAtBeginning(Ty, Read, Slots))
    return nullptr;
  return Ty;
}
