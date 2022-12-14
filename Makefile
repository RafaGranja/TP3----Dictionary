#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa main.cpp
# Autor		: Rafael Granja (rafaelgranja2003@ufmg.br)
# Histórico	: 2022-12-13 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo   
#			: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
CFLAGS = -pg -Wall 
SRC = src
BIN = bin
OBJ = obj
INC = include
clean:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

all:
	$(CC) -c $(SRC)/main.cpp -o $(OBJ)/main.o
	$(CC) -o $(BIN)/tp3 $(OBJ)/main.o


