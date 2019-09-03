#ifndef DOMAIN_H
#define DOMAIN_H

#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace dataflow {

class Domain {
public:
  enum Element { None, NonZero, Zero, MaybeZero };
  Domain();
  Domain(Element V);
  Element Value;

  static Domain *add(Domain *E1, Domain *E2);
  static Domain *sub(Domain *E1, Domain *E2);
  static Domain *mul(Domain *E1, Domain *E2);
  static Domain *div(Domain *E1, Domain *E2);
  static Domain *join(Domain *E1, Domain *E2);
  static bool order(Domain E1, Domain E2);
  void print(raw_ostream &O);
};

raw_ostream &operator<<(raw_ostream &O, Domain V);

}; // namespace dataflow

#endif // DOMAIN_H
