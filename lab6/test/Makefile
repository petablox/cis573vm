.PRECIOUS: %.ll

all: simple0.out simple1.out branch0.out branch1.out branch2.out loop0.out input0.out pointer0.out pointer1.out pointer2.out

%.opt.ll: %.c
	clang -emit-llvm -S -fno-discard-value-names -Xclang -disable-O0-optnone -c -o $@ $<
	opt -mem2reg -S $@ -o $*.opt.ll

%.out: %.opt.ll
	opt -load ../build/DataflowPass.so -DivZero $< -disable-output > $@ 2> $*.err

clean:
	rm -f *.ll *.out *.err
