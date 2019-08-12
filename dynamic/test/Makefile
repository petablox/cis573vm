TARGETS=simple0 simple1 function0 fuzz0 fuzz1

all: ${TARGETS}

%: %.c
	clang -emit-llvm -S -fno-discard-value-names -c -o $@.ll $< -g
	opt -load ../build/Instrument.so -Instrument -S $@.ll > $@.instrumented.ll
	clang -o $@ -L${PWD}/../build -lruntime $@.instrumented.ll

clean:
	rm -f *.ll *.cov *.branch *.return ${TARGETS}
