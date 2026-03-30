// File: manifest_parser_parse_test_11.cc

#include "manifest_parser.h"
#include "state.h"

#include "gtest/gtest.h"

#include <string>

// Simple fixture to provide a State instance for each test.
class ManifestParserParseTest_11 : public ::testing::Test {
 protected:
  State state_;
};

// Normal operation: a minimal valid manifest (rule + build) should parse
// successfully and leave the error string empty.
TEST_F(ManifestParserParseTest_11, ParseValidSimpleManifest_11) {
  ManifestParser parser(&state_, /*file_reader=*/nullptr);
  std::string err;

  const std::string input =
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build out: cat in\n";

  EXPECT_TRUE(parser.ParseTest(input, &err));
  EXPECT_EQ("", err);
}

// Error case: top-level text without '=' should fail and report an error.
// This also verifies that ParseTest uses the fixed filename "input" in errors.
TEST_F(ManifestParserParseTest_11, ErrorMissingEqualsAtTopLevel_11) {
  ManifestParser parser(&state_, /*file_reader=*/nullptr);
  std::string err;

  EXPECT_FALSE(parser.ParseTest("foobar", &err));
  EXPECT_EQ("input:1: expected '=', got eof\n", err);
}

// Error case: assignment without a terminating newline / further tokens
// should report an unexpected EOF.
TEST_F(ManifestParserParseTest_11, ErrorUnexpectedEOFInAssignment_11) {
  ManifestParser parser(&state_, /*file_reader=*/nullptr);
  std::string err;

  EXPECT_FALSE(parser.ParseTest("x = 3", &err));
  EXPECT_EQ("input:1: unexpected EOF\n", err);
}

// Error case: build statement referencing a non-existent rule should fail
// and report an unknown build rule error.
TEST_F(ManifestParserParseTest_11, ErrorUnknownBuildRule_11) {
  ManifestParser parser(&state_, /*file_reader=*/nullptr);
  std::string err;

  EXPECT_FALSE(parser.ParseTest("build x: y z\n", &err));
  EXPECT_EQ("input:1: unknown build rule 'y'\n", err);
}
