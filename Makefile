

OUTS = $(wildcard *.out)

.PHONY: compile clean




compile : 
	@echo "Building the all system.."
	@g++  --std=c++11 *.cpp 
	@echo "Done building.\n"



clean :
	@echo "Deleting non-sources files ...\n"
	@rm -f $(OUTS)