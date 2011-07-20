#
# Makefile
#
# Copyright (C) Tom Spink 2011 <tspink@gmail.com>
# All Rights Reserved
#
SRC := test.cs
DLL := test.dll
OUT := lib$(DLL).so
OBJ := $(DLL).o $(DLL).data.o support.o
HDR := support.h

OUT-TEST := so-gen-test
OBJ-TEST := so-gen-test.o

CFLAGS	:= `pkg-config --cflags mono-2` -g -Wall
LDFLAGS	:= `pkg-config --libs mono-2` -shared

all: $(OUT) $(OUT-TEST)

$(OUT): $(OBJ)
	cc -o $@ $(LDFLAGS) $^

$(OUT-TEST): $(OBJ-TEST) $(OUT)
	cc -o $@ -L. -l$(DLL) $^

$(DLL): $(SRC)
	gmcs -out:$@ -target:library $^

$(DLL).data.o: $(DLL)
	objcopy -I binary -O elf32-i386 -B i386 --rename-section .data=.assembly $< $@ 

%.o: %.c $(HDR)
	cc -c -o $@ $(CFLAGS) $<

clean:
	rm -f $(DLL) $(OUT) $(OBJ) $(OUT-TEST) $(OBJ-TEST)
