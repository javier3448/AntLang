# @TODO: Document it as much as possible, you will forget all this makefile nonsense
# in a day
# Mark the things that are "magical enchantments" you copy pasted
# video where we got it all from: https://www.youtube.com/watch?v=PiFUuQqW-v8&t=190s&ab_channel=Competer

# @TODO: * Add a recipe and flags for release build
#        * Add a ""recipe"" that builds and runs
#        * dont print all commands, or maybe print a nice custom message per object file


target  := antlang
# everytime we add a new cpp just add the .o and .cpp

# @TODO: Write some kind of script that automatically updates in a fool-proof way the `objs` variable.
# It should also create the directories where the .o files will be, for example: `build/Debug/objs/AntQbeGen`
# i.e copy the directory structure of `src/`
objs := build/Debug/objs/AntLlvmGen/antLlvmGen.o build/Debug/objs/AntQbeGen/qbeValue.o build/Debug/objs/AntQbeGen/qbeBuffer.o build/Debug/objs/AntQbeGen/qbeInstruction.o build/Debug/objs/AntQbeGen/antQbeGen.o build/Debug/objs/mystring.o build/Debug/objs/Parser/astexpression.o build/Debug/objs/Parser/lexer.o build/Debug/objs/Parser/tokencache.o build/Debug/objs/Parser/grapher.o build/Debug/objs/Parser/parser.o build/Debug/objs/Parser/token.o build/Debug/objs/Parser/aststatement.o build/Debug/objs/main.o build/Debug/objs/TypeChecker/typechecker.o

CC     := clang++
CFLAGS := -Wall -std=c++17 -g

all: $(target)

deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)
# I don't like this = instead of := here, can we generate the dependency files
# in less confussing way?
# Does it even work? what if: `build/Debug/objs/%.o: src/%.cpp` doesn't run because `src/%.cpp` didn't change?
# what if we change the `src/%.h`?? fuck all of this :(

antlang: $(objs)
	$(CC) $(CFLAGS) -o build/Debug/$@ $^

build/Debug/objs/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< $(DEPFLAGS) -o $@

clean:
	rm -f $(target) $(objs) $(deps)