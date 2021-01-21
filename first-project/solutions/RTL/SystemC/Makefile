DESIGN_NAME=multiplier

EXECUTABLE=bin/$(DESIGN_NAME).x

SYSTEMC=$$SYSTEMC_HOME

PLATFORM= $(shell uname -s)
ARCH=$(shell getconf LONG_BIT)

ifeq ($(PLATFORM),Darwin)
SYSC_LIBDIR := $(SYSTEMC)/lib-macosx
endif
ifeq ($(PLATFORM),Linux)
SYSC_LIBDIR := $(SYSTEMC)/lib-linux
endif

ifeq ($(ARCH),64)
SYSC_LIBDIR := $(SYSC_LIBDIR)64
endif

INCDIR = -I./include/ -I. -I$(SYSTEMC)/include/
LIBDIR = $(SYSC_LIBDIR)

CXX=g++
CFLAGS= -c
LD=g++

all: $(EXECUTABLE)

$(EXECUTABLE): obj/main_$(DESIGN_NAME).o obj/$(DESIGN_NAME)_testbench.o obj/$(DESIGN_NAME)_toplevel.o obj/$(DESIGN_NAME).o 
	@echo Building $@
	$(CXX) -g $(INCDIR) -o $@ $^ $(LIBDIR)/libsystemc.a -lpthread

obj/main_$(DESIGN_NAME).o: src/main_$(DESIGN_NAME).cpp
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $< 

obj/$(DESIGN_NAME)_testbench.o: src/$(DESIGN_NAME)_testbench.cpp include/$(DESIGN_NAME)_testbench.h
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $< 

obj/$(DESIGN_NAME)_toplevel.o: src/$(DESIGN_NAME)_toplevel.cpp include/$(DESIGN_NAME)_toplevel.h
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(DESIGN_NAME).o: src/$(DESIGN_NAME).cpp include/$(DESIGN_NAME).h
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $<


clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f $(EXECUTABLE)

.PHONY: all clean
