.PRECIOUS: %.ll %.instrumented.ll

TARGETS=simple0 simple1

all: ${TARGETS}

%: %.c
	clang -emit-llvm -S -fno-discard-value-names -c -o $@.ll $<
	opt -load ../build/InstrumentPass.so -Instrument -S $*.ll -o $*.instrumented.ll
	clang -o $@ -L${PWD}/../build -lruntime $*.instrumented.ll

clean:
	rm -f *.ll *.out *.err *.smt2 input.txt branch.txt ${TARGETS}
