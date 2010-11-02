# Quick and dirty Makefile for qs_parse

ALL = qs.o qs_test qs_example

all: $(ALL)

clean:
	rm -f $(ALL)

qs_test: qs.o qs_test.c
	$(CC) $^ -o $@

qs_example: qs.o qs_example.c
	$(CC) $^ -o $@

qs.o: qs.h
