.PHONY: build

CONIFG = Debug

EXE = Survival_Shooter.exe

all: compile run

build:
	cmake -S . -B build -G Ninja

compile: 
	cmake --build build --config ${CONIFG}

run:
	./$(EXE)
