# Author: Dmitrii Vekshin
# vekshdmi@fit.cvut.cz




BINARY = ./vekshdmi
DOC = doc
RM = rm -rf
SRC = src/main.cpp src/CMainMenu.h src/CCursor.h src/CFrame.h  src/CMainMenu.cpp src/CCursor.cpp src/CFrame.cpp src/CComand.cpp src/CQuizMenu.cpp src/CQuizMenu.h src/CMenu.h src/CMenu.cpp src/CQuiz.h src/CQuiz.cpp src/CQuestion.h src/CQuestion.cpp

CXX =g++
CXXFLAGS = -std=c++14 -Wall -pedantic -Wno-long-long -O0 -ggdb 
ncurses = -lncurses 

all: compile doc

# Delete binary and created documentation
clean:
	rm -r $(BINARY)
	rm -r $(DOC)

# Compile
compile: 
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BINARY) $(ncurses)  

# Run the program
run:
	$(BINARY)

# Create documentation
doc: 
	doxygen
