// File: ./TestProjects/yaml-cpp/test/indentation_test_512.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"
#include "TestProjects/yaml-cpp/src/indentation.h"

namespace {

class IndentationOperatorTest_512 : public ::testing::Test {
 protected:
  static std::string ToString(const YAML::ostream_wrapper& out) {
    const char* s = out.str();
    return s ? std::string(s) : std::string();
  }

  static std::string Spaces(std::size_t n) { return std::string(n, ' '); }
};

TEST_F(IndentationOperatorTest_512, IndentsFromColumn0ToN_512) {
  YAML::ostream_wrapper out;

  out << YAML::IndentTo(5);

  EXPECT_EQ(ToString(out), Spaces(5));
  EXPECT_EQ(out.col(), 5u);
  EXPECT_EQ(out.row(), 0u);
}

TEST_F(IndentationOperatorTest_512, IndentsAddsOnlyMissingSpaces_512) {
  YAML::ostream_wrapper out;

  out.write("ab");  // col should now be 2
  ASSERT_EQ(out.col(), 2u);

  out << YAML::IndentTo(6);

  EXPECT_EQ(ToString(out), std::string("ab") + Spaces(4));
  EXPECT_EQ(out.col(), 6u);
  EXPECT_EQ(out.row(), 0u);
}

TEST_F(IndentationOperatorTest_512, IndentDoesNothingWhenAlreadyPastTargetColumn_512) {
  YAML::ostream_wrapper out;

  out.write("abcdef");  // col should now be 6
  ASSERT_EQ(out.col(), 6u);

  out << YAML::IndentTo(3);

  EXPECT_EQ(ToString(out), "abcdef");
  EXPECT_EQ(out.col(), 6u);
  EXPECT_EQ(out.row(), 0u);
}

TEST_F(IndentationOperatorTest_512, IndentAfterNewlineUsesCurrentColumn_512) {
  YAML::ostream_wrapper out;

  out.write("x\n");  // after newline, column should reset (commonly 0)
  // We don't assume exact row/col rules beyond being observable; we assert typical behavior:
  EXPECT_EQ(ToString(out), "x\n");
  EXPECT_EQ(out.row(), 1u);
  EXPECT_EQ(out.col(), 0u);

  out << YAML::IndentTo(4);

  EXPECT_EQ(ToString(out), std::string("x\n") + Spaces(4));
  EXPECT_EQ(out.row(), 1u);
  EXPECT_EQ(out.col(), 4u);
}

}  // namespace