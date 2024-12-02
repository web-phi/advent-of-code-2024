CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20
TARGET := solution.exe

.PHONY: list
list:
	@echo "Completed problems:"
	@ls -d day*/ | grep 'day'

.PHONY: run
run:
	@if [ -z "$(DIR)" ]; then \
		echo "Usage: make run DIR=dayX"; \
	elif [ ! -f "$(DIR)/solution.cpp" ]; then \
		echo "Error: $(DIR)/solution.cpp not found!"; \
	elif [ ! -f "$(DIR)/input" ]; then \
		echo "Error: $(DIR)/input not found!"; \
	else \
		$(CXX) $(CXXFLAGS) -o $(DIR)/$(TARGET) $(DIR)/solution.cpp && ./$(DIR)/$(TARGET) < $(DIR)/input; \
	fi

.PHONY: clean
clean:
	@rm -f day*/$(TARGET)
	@echo "Removed executables."