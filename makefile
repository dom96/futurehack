CC	:= g++
IFLAGS 	:= -I include/
CFLAGS	:= -Wall -Wextra -Wno-switch-enum
DFLAGS	:= -g -DDEBUG

LNFLAGS	:= -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -lm
EXE 	:= futurehack

.SUFFIXES=.cpp

SRC 	:= $(shell find 'src' -name '*.cpp' )
HPPFILES := $(shell find 'include' -name '*.hpp' )
OBJ 	:= $(SRC:.cpp=.o)

TESTSRC := $(shell find 'tests' -name '*.cpp' )
TESTSRC += $(HPPFILES:include/%.hpp=src/%.cpp)
TESTOBJ := $(TESTSRC:.cpp=.o)
TESTEXE := test

all: $(EXE)

tests: $(TESTEXE)

$(TESTEXE): $(TESTOBJ)
	$(CC) $(TESTOBJ) $(CFLAGS) $(IFLAGS) $(LNFLAGS) -o$(TESTEXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(IFLAGS) $(LNFLAGS) -o$(EXE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(EXE)

debug:
	@$(MAKE) $(MFLAGS) CFLAGS="$(CFLAGS) $(DFLAGS)"

.PHONY= all clean debug tests
