build:
	gcc process_generator.c -o process_generator.out -fno-stack-protector
	gcc clk.c -o clk.out -fno-stack-protector
	gcc scheduler.c -o scheduler.out -fno-stack-protector
	gcc process.c -o process.out -fno-stack-protector
	gcc test_generator.c -o test_generator.out -fno-stack-protector

clean:
	rm -f *.out  processes.txt

all: clean build

run:
	./process_generator.out
