# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := exampleB1
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin



include $(G4INSTALL)/config/binmake.gmk
LDLIBS+=`root-config --libs`
INC=$(`root-config --incdir`)
INC_PARAMS=$(foreach d, $(INC), -I$d)
visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*
