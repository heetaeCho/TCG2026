#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <set>
#include "clparser.h"
#include "msvc_helper.h"

// Tests for CLParser which is a key dependency used in MSVCHelperMain
class CLParserTest_109 : public ::testing::Test {
 protected:
  CLParser parser_;
};

TEST_F(CLParserTest_109, FilterShowIncludesWithMatchingPrefix_109) {
  std::string line = "Note: including file: foo.h";
  std::string result = CLParser::FilterShowIncludes(line, "Note: including file:");
  // Should extract the include path
  EXPECT_FALSE(result.empty());
}

TEST_F(CLParserTest_109, FilterShowIncludesWithNonMatchingPrefix_109) {
  std::string line = "some random output line";
  std::string result = CLParser::FilterShowIncludes(line, "Note: including file:");
  EXPECT_TRUE(result.empty());
}

TEST_F(CLParserTest_109, FilterShowIncludesEmptyLine_109) {
  std::string line = "";
  std::string result = CLParser::FilterShowIncludes(line, "Note: including file:");
  EXPECT_TRUE(result.empty());
}

TEST_F(CLParserTest_109, FilterShowIncludesEmptyPrefix_109) {
  std::string line = "Note: including file: foo.h";
  std::string result = CLParser::FilterShowIncludes(line, "");
  // With empty prefix, behavior depends on implementation
  // Just verify it doesn't crash
  (void)result;
}

TEST_F(CLParserTest_109, IsSystemIncludeForSystemPath_109) {
  // Typical system include paths on Windows
  bool result = CLParser::IsSystemInclude("c:\\program files (x86)\\microsoft visual studio\\include\\vector");
  EXPECT_TRUE(result);
}

TEST_F(CLParserTest_109, IsSystemIncludeForUserPath_109) {
  bool result = CLParser::IsSystemInclude("c:\\users\\myproject\\src\\foo.h");
  EXPECT_FALSE(result);
}

TEST_F(CLParserTest_109, FilterInputFilenameWithSourceFile_109) {
  bool result = CLParser::FilterInputFilename("foo.cc");
  EXPECT_TRUE(result);
}

TEST_F(CLParserTest_109, FilterInputFilenameWithNonSourceLine_109) {
  bool result = CLParser::FilterInputFilename("some compiler warning text");
  EXPECT_FALSE(result);
}

TEST_F(CLParserTest_109, FilterInputFilenameWithCppFile_109) {
  bool result = CLParser::FilterInputFilename("foo.cpp");
  EXPECT_TRUE(result);
}

TEST_F(CLParserTest_109, FilterInputFilenameWithCFile_109) {
  bool result = CLParser::FilterInputFilename("foo.c");
  EXPECT_TRUE(result);
}

TEST_F(CLParserTest_109, ParseEmptyOutput_109) {
  std::string filtered_output;
  std::string err;
  bool result = parser_.Parse("", "", &filtered_output, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(filtered_output.empty());
}

TEST_F(CLParserTest_109, ParseOutputWithIncludes_109) {
  std::string output = "Note: including file: foo.h\nsome output\n";
  std::string filtered_output;
  std::string err;
  bool result = parser_.Parse(output, "Note: including file:", &filtered_output, &err);
  EXPECT_TRUE(result);
  // The include line should be filtered out, remaining output kept
  EXPECT_NE(std::string::npos, filtered_output.find("some output"));
  EXPECT_EQ(std::string::npos, filtered_output.find("Note: including file:"));
  EXPECT_FALSE(parser_.includes_.empty());
}

// Tests for CLWrapper
class CLWrapperTest_109 : public ::testing::Test {
 protected:
  CLWrapper cl_;
};

TEST_F(CLWrapperTest_109, DefaultConstructorSetsNullEnvBlock_109) {
  // env_block_ is public, should be NULL after construction
  EXPECT_EQ(nullptr, cl_.env_block_);
}

TEST_F(CLWrapperTest_109, SetEnvBlockStoresPointer_109) {
  char env_data[] = "FOO=BAR\0";
  cl_.SetEnvBlock(env_data);
  EXPECT_EQ(static_cast<void*>(env_data), cl_.env_block_);
}

TEST_F(CLWrapperTest_109, SetEnvBlockToNull_109) {
  char env_data[] = "FOO=BAR\0";
  cl_.SetEnvBlock(env_data);
  cl_.SetEnvBlock(nullptr);
  EXPECT_EQ(nullptr, cl_.env_block_);
}
