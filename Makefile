CC := g++
CFLAGS := -O2 -Wall -Wextra -Wno-maybe-uninitialized -std=c++20
SRC_FOLDER := ./source
SOURCES := $(wildcard ./source/*.cpp)
INCLUDES := $(wildcard ./include/*.hpp)
BIN_FOLDER := ./bin
BINARIES := $(addprefix $(BIN_FOLDER)/lib, $(addsuffix .a, $(basename $(notdir $(SOURCES)))))
BINARIES_DEBUG := $(addprefix $(BIN_FOLDER)/lib, $(addsuffix dbg.a, $(basename $(notdir $(SOURCES)))))
IFLAGS := -I./include/
# LDFLAGS := -I./include/ -ldaytime
# LDFLAGS := -I./include/ $(addprefix -l, $(basename $(notdir $(SOURCES))))
LDFLAGS := -I./include/ -lnetimpl -ldaytime
# LDFLAGS_DEBUG := -I./include/ -ldaytimedbg
LDFLAGS_DEBUG := -I./include/ $(addsuffix dbg, $(addprefix -l, $(basename $(notdir $(SOURCES)))))
LINKDIR := -L./bin/

all: tetosocket

debug: ./tetosocket.cpp $(INCLUDES) $(BINARIES_DEBUG)
	$(CC) $(CFLAGS) -g $< -o $(basename $<) $(LINKDIR) $(LDFLAGS_DEBUG)

tetosocket: ./tetosocket.cpp $(INCLUDES) $(BINARIES)
	$(CC) $(CFLAGS) $< -o $@ $(LINKDIR) $(LDFLAGS)

tests_datetime: ./test.cpp $(INCLUDES) $(BINARIES)
	$(CC) $(CFLAGS) $< -o $@ $(LINKDIR) $(LDFLAGS) -lgtest -lgmock -pthread

tests_datetime_dbg: ./test.cpp $(INCLUDES) $(BINARIES_DEBUG)
	$(CC) $(CFLAGS) -g $< -o $@ $(LINKDIR) $(LDFLAGS_DEBUG) -lgtest -lgmock -pthread

$(BIN_FOLDER):
	mkdir $(BIN_FOLDER)

$(BIN_FOLDER)/libdaytime.a: ./source/daytime.cpp ./include/daytime.hpp
	if [ -d $(BIN_FOLDER) ]; then : ; else mkdir $(BIN_FOLDER); fi
	rm -f $@
	$(CC) $(CFLAGS) $< -c -o $(basename $@).o $(IFLAGS)
	ar rcs $@ $(basename $@).o
	rm -f $(basename $@).o

$(BIN_FOLDER)/libnetimpl.a: ./source/netimpl.cpp ./include/netimpl.hpp
	if [ -d $(BIN_FOLDER) ]; then : ; else mkdir $(BIN_FOLDER); fi
	rm -f $@
	$(CC) $(CFLAGS) $< -c -o $(basename $@).o $(IFLAGS)
	ar rcs $@ $(basename $@).o
	rm -f $(basename $@).o

$(BIN_FOLDER)/libdaytimedbg.a: ./source/daytime.cpp ./include/daytime.hpp
	if [ -d $(BIN_FOLDER) ]; then : ; else mkdir $(BIN_FOLDER); fi
	rm -f $@
	$(CC) $(CFLAGS) -g $< -c -o $(basename $@).o $(IFLAGS)
	ar rcs $@ $(basename $@).o
	rm -f $(basename $@).o

$(BIN_FOLDER)/libnetimpldbg.a: ./source/netimpl.cpp ./include/netimpl.hpp
	if [ -d $(BIN_FOLDER) ]; then : ; else mkdir $(BIN_FOLDER); fi
	rm -f $@
	$(CC) $(CFLAGS) -g $< -c -o $(basename $@).o $(IFLAGS)
	ar rcs $@ $(basename $@).o
	rm -f $(basename $@).o

.PHONY: run test qcPerf qcRead clean

run: tetosocket
	./tetosocket

test: tests_datetime
	./tests_datetime

test_dbg: tests_datetime_dbg
	./tests_datetime_dbg

qcPerf:
	clang-tidy -checks="-*,boost-*,clang-analyzer-*,modernize-*,performance-*,cppcoreguidelines-*,-cppcoreguidelines-avoid-magic-numbers" tetosocket.cpp ./source/* ./include/* -- -I./include/ -std=c++20

qcRead:
	clang-tidy -checks="-*,boost-*,clang-analyzer-*,readability-*,-readability-magic-numbers" tetosocket.cpp ./source/* ./include/* -- -I./include/ -std=c++20

clean:
	rm -f ./tetosocket
	rm -rf $(BIN_FOLDER)