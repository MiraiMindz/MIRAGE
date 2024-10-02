LIBDIR=lib
BINDIR=bin
BUILDDIR=build
SRCDIR=src
INTERNALLIBS=$(LIBDIR)/internal
CC=gcc
OPENGLFLAGS=-lGL -lGLU -lglut -lglfw -lGLEW
MATHLIBFLAGS=-lm
WARNINGFLAGS=-Wextra -Werror -Wshadow -Wformat -Wreturn-type -Wuninitialized -Wno-missing-braces -pedantic
INCLUDEFLAGS=-I./lib/internal/renderer -I./lib/internal/gl_helpers -I./lib/internal/types -I./lib/GLAD
CFLAGS=-O3 -ggdb -g -pg -march=native -std=c23 -fsanitize=address $(MATHLIBFLAGS) $(OPENGLFLAGS) $(INCLUDEFLAGS)
SOURCES = $(SRCDIR)/main.c $(INTERNALLIBS)/renderer/renderer.c $(INTERNALLIBS)/gl_helpers/gl_helpers.c $(INTERNALLIBS)/types/matrix.c $(LIBDIR)/GLAD/glad.c 
TARGET = main


all: clean run

main:
	$(CC) $(CFLAGS) -o $(BINDIR)/$(TARGET) $(SOURCES)

clean:
	rm -rfv $(BINDIR)/*
	rm -rfv $(BUILDDIR)/*

run: clean main
	$(BINDIR)/main

