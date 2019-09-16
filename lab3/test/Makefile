TARGETS=sanity easy easy2

all: ${TARGETS}

%: %.c
	clang -emit-llvm -S -fno-discard-value-names -c -o $@.ll $< -g
	opt -load ../build/InstrumentPass.so -Instrument -S $@.ll > $@.instrumented.ll
	clang -o $@ -L${PWD}/../build -lruntime $@.instrumented.ll

clean:
	rm -f *.ll *.cov ${TARGETS}
