## Filename: Makefile
## Description: 
## Author: LIU Yi
## Copyright (C) 2014, LIU Yi, all rights reserved.
## Created: Fri Sep 12 18:01:55 2014 (+0800)
## Version: 
## Package-Requires: ()
## Last-Updated: Thu Jul  2 16:15:06 2015 (+0800)
##           By: LIU Yi
##     Update #: 10
## 
######################################################################
## 
### Commentary: 
## 
## 
## 
######################################################################
## 
### Change Log:
## 
## 
######################################################################
TARGET = aptmotor

INC_SELETED := AptMotor.hh
INC_LINK := LinkDef.hh



TARGET_LIB = lib$(TARGET).so
TARGET_DICT := lib$(TARGET).cc

SRC_DIR := src/
INC_DIR := include/
OBJ_DIR := obj/
SHA_DIR := share/


SRCS         := $(wildcard $(SRC_DIR)*.cc)
SRCS         := $(notdir $(SRCS))
SRCS         += $(TARGET_DICT)
OBJS         := $(patsubst %.cc,%.o,$(SRCS))

DEBUG        := # -g
CXX          := g++
LD           := g++
CXXFLAGS     := $(DEBUG) -Wall -fPIC
LDFLAGS      := $(DEBUG)
SOFLAGS      := -shared
SYSLIBS      := -lpython2.7

# ROOTCINT     := rootcint
ROOTCINT     := rootcling
ROOTCONFIG   := root-config
ROOTCFLAGS   := $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS  := $(shell $(ROOTCONFIG) --ldflags)
ROOTLIBS     := $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS    := $(shell $(ROOTCONFIG) --glibs)
HASTHREAD    := $(shell $(ROOTCONFIG) --has-thread)

LIBS         := $(ROOTLIBS) $(SYSLIBS)
GLIBS        := $(ROOTGLIBS) $(SYSLIBS)

CXXFLAGS     += $(ROOTCFLAGS) -I$(SRC_DIR) -I$(INC_DIR)
LDFLAGS      += $(ROOTLDFLAGS)

vpath %.cc $(SRC_DIR)
vpath %.hh $(INC_DIR)
vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)
vpath %.o $(OBJ_DIR)


$(TARGET_LIB): $(OBJS)
	$(LD) $(SOFLAGS) $(LDFLAGS) $(addprefix $(OBJ_DIR),$(notdir $^)) $(GLIBS) -o $@


$(TARGET_DICT):  $(INC_SELETED) $(INC_LINK)
	$(ROOTCINT)  -f $@ -c $^


.SUFFIXES:
%.o:%.cc
	$(CXX)  $(CXXFLAGS) -c $< -o $(OBJ_DIR)$@

.PHONY: clean
clean:
	@ rm -f lib$(TARGET)*
	@ rm -f ./obj/*
