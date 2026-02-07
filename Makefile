.PHONY: build

CONIFG = Debug

EXE = Survival_Shooter.exe

all: compile run

build:
	cmake -S . -B build -G Ninja
	cmake --build build --config ${CONIFG}

compile: 
	cmake -S . -B build -G Ninja
	cmake --build build --config ${CONIFG}

run:
	./build/$(EXE)
