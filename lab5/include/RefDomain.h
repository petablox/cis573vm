#ifndef REF_DOMAIN_H
#define REF_DOMAIN_H

#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace dataflow {

class RefDomain {
public:
  enum Element { None, NonZero, Zero, MaybeZero };
  RefDomain();
  RefDomain(Element V);
  Element Value;

  static RefDomain *add(RefDomain *E1, RefDomain *E2);
  static RefDomain *sub(RefDomain *E1, RefDomain *E2);
  static RefDomain *mul(RefDomain *E1, RefDomain *E2);
  static RefDomain *div(RefDomain *E1, RefDomain *E2);
  static RefDomain *join(RefDomain *E1, RefDomain *E2);
  static bool order(RefDomain E1, RefDomain E2);
  void print(raw_ostream &O);
};

raw_ostream &operator<<(raw_ostream &O, RefDomain V);

}; // namespace dataflow

#endif // REF_DOMAIN_H
