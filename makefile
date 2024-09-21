CC=gcc
OPENGLFLAGS=-lGL -lGLU -lglut -lglfw
MATHLIBFLAGS=-lm
CFLAGS=-O3 -Wall -Wextra -Werror -Wshadow -Wformat -Wreturn-type -Wuninitialized -ggdb -g -pg -march=native -pedantic -std=c23 -fsanitize=address $(MATHLIBFLAGS) $(OPENGLFLAGS)
BINDIR=bin
BUILDDIR=build
SRCDIR=src

all: clean run

main:
	$(CC) $(CFLAGS) -o $(BINDIR)/main $(SRCDIR)/main.c

clean:
	rm -rfv $(BINDIR)/*
	rm -rfv $(BUILDDIR)/*

run: clean main
	$(BINDIR)/main

