# Makefile for UT
#

CXX = g++
CXXFLAGS += -g -Wall -Werror -Wextra -std=c++1y
LDFLAGS += -DGTEST_HAS_PTHREAD=1

TARGET = clone_detect_test

# Points to source files directory of clone_detect.
SRC_DIR = ../../src
TEST_DIR = ../cases

# Points to directory where project header files is.
SRC_INC = -I../googletest/gtest-1.7.0/include/ \
          -I../googletest/gmock-1.7.0/include/ \
          -I$(SRC_DIR) \
          -I$(TEST_DIR)/mock
          
LIBS = -lpthread \
       -L../googletest/gtest-1.7.0/lib -lgtest -lgtest_main \
       -L../googletest/gmock-1.7.0/lib -lgmock\
       -fexceptions

# Lists of all objects. *.o means an object file of c file, 
# *.oxx means an object file of cpp file. You have to list all object
# files here with directories in prefix.
SRC_OBJ = $(SRC_DIR)/CurlyBracesFormatter.o\
          $(SRC_DIR)/GetCodeFileNames.o\
          $(SRC_DIR)/DuplicatedCodeBlocks.o\
          $(SRC_DIR)/DuplicatedCodeBlocksBuilder.o\
          $(SRC_DIR)/DuplicatedCodeBlocksDetector.o\
          $(SRC_DIR)/FileReader.o\
          $(SRC_DIR)/GetCodeFileNames.o\
          $(SRC_DIR)/SpaceFormatter.o\
          $(SRC_DIR)/Json.o\
          $(SRC_DIR)/RemoveEmptyLine.o\
          $(SRC_DIR)/ClearComments.o\
          $(SRC_DIR)/MainArgsParser.o\
          $(SRC_DIR)/DuplicatedCodeBlocksBuilderFactory.o

TEST_OBJ = $(TEST_DIR)/TestCommon.o\
           $(TEST_DIR)/CurlyBracesFormatterTestSuite.o\
           $(TEST_DIR)/ClearCommentsTestSuite.o\
           $(TEST_DIR)/DuplicatedCodeBlocksTestSuite.o\
           $(TEST_DIR)/DuplicatedCodeBlocksBuilderTestSuite.o\
           $(TEST_DIR)/DuplicatedCodeBlocksDetectorTestSuite.o\
           $(TEST_DIR)/FileReaderTestSuite.o\
           $(TEST_DIR)/GetCodeFileNamesTestSuite.o\
           $(TEST_DIR)/SpaceFormatterTestSuite.o\
           $(TEST_DIR)/RemoveEmptyLinesTestSuite.o
           

# House-keeping build targets.
all: $(TARGET)

$(TARGET):$(SRC_OBJ) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(SRC_INC) $(LDFLAGS)  $^ $(LIBS) -o $@
	./$@
    
# Rules to compile all c/cpp files
%.o:%.c
	@echo compiling SRC files
	$(CXX) $(CXXFLAGS) $(SRC_INC) -I . -c $< -o $@

%.o:%.cpp
	@echo compiling SRC files
	$(CXX) $(CXXFLAGS) $(SRC_INC) -I . -c $< -o $@
clean:
	rm -f $(TEST_OBJ) $(TARGET)
