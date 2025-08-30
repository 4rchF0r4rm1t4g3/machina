cc := cc
bld := build
src := src

compile:
	$(cc) -c -o $(bld)/main.o $(src)/main.c
	$(cc) -o $(bld)/machina $(bld)/*.o

clean:
	rm -rf $(bld)/*