# Quick and dirty Makefile for qs_parse

ALL = qs_parse.o qs_test qs_example

all: $(ALL)

clean:
	rm -f $(ALL)

qs_test: qs_parse.o qs_test.c
	$(CC) qs_parse.o qs_test.c -o $@

qs_example: qs_parse.o qs_example.c
	$(CC) qs_parse.o qs_example.c -o $@

qs_parse.o: qs_parse.h
