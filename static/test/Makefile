.PRECIOUS: %.ll

all: simple0.out simple1.out branch0.out branch1.out pointer0.out pointer1.out

%.ll: %.c
	clang -emit-llvm -S -fno-discard-value-names -c -o $@ $<

%.out: %.ll
	opt -load ../build/DataflowPass.so -DivZero $< -disable-output > $@ 2> $*.err

clean:
	rm -f *.ll *.out *.err
