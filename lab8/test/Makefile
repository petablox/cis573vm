TARGETS=simple0 branch0 function0

all: ${TARGETS}

%: %.c
	clang -emit-llvm -S -fno-discard-value-names -c -o $@.ll $<

clean:
	rm -f *.ll formula.smt2 ${TARGETS}
