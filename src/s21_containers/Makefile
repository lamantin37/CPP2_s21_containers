CC = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17
HEADERS = $(wildcard s21_*.h)
TESTS = tests/test_s21_
ADD_LIB = -lgtest
TARGETS = map set vector list queue stack

_UNAME_ := $(shell uname -s)

ifeq ($(_UNAME_), Linux)
	OPEN_CMD = xdg-open
	BREW = .
	BROWSER_APP = firefox 
endif

ifeq ($(_UNAME_), Darwin) # MacOS
	OPEN_CMD = open
	BREW = ${HOME}/homebrew
	BROWSER_APP = /Applications/Google\ Chrome.app
endif

PATH := $(PATH):$(BREW)/bin
GCOV = --coverage

.PHONY: test $(TARGETS) lcov

all: clean style gcov_report

test: $(TARGETS)

$(TARGETS):
	$(info                                         )
	$(info ----------------------------------------)
	$(info Build $@ tests                          )
	$(info ----------------------------------------)
	$(CC) $(TESTS)$@.cc $(ADD_LIB) $(CPPFLAGS) -o $@
	./$@

%:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Build $@ other                          )
	$(info ----------------------------------------)
	$(CC) $(HEADERS) $(OTHER)$@.cc $(ADD_LIB) $(CPPFLAGS) -o $@

style:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Check for code style and formatting     )
	$(info ----------------------------------------)
	clang-format -style=Google -i tests/*.cc containers/*.h

clean:
	-rm -rf $(TARGETS)
	-rm -rf *.gch