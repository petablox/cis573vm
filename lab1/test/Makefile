.PRECIOUS: %.ll

all: simple0.out simple1.out simple2.out simple3.out simple4.out simple5.out simple6.out simple7.out simple8.out simple9.c simple10.out simple11.out

%.ll: %.c
	clang -emit-llvm -S -fno-discard-value-names -c -o $@ $<

%.out: %.ll
	opt -load ../build/DataflowPass.so -DivZero $< -disable-output > $@ 2> $*.err

clean:
	rm -f *.ll *.out *.err
