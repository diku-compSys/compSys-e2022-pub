%.riscv: %.c lib.c
	./gcc -march=rv32im -mabi=ilp32 -O1 $< lib.c -static -nostartfiles -nostdlib -o $@

%.dis: %.riscv
	./objdump -s -w $< > $@
	./objdump -S $< >> $@
