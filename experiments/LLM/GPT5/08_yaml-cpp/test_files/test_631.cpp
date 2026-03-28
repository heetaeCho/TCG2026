// File: ./TestProjects/yaml-cpp/test/emitterutils_test_631.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

namespace YAML {
namespace Utils {
// Black-box forward declaration (avoid depending on private/internal headers).
bool WriteLiteralString(ostream_wrapper& out, const char* str, std::size_t size,
                        std::size_t indent);
}  // namespace Utils
}  // namespace YAML

namespace {

class WriteLiteralStringTest_631 : public ::testing::Test {
 protected:
  static std::string CaptureStream(std::ostringstream& oss) { return oss.str(); }

  static std::string Call(const char* data, std::size_t size, std::size_t indent) {
    std::ostringstream oss;
    YAML::ostream_wrapper out(oss);

    const bool ok = YAML::Utils::WriteLiteralString(out, data, size, indent);
    EXPECT_TRUE(ok);

    return CaptureStream(oss);
  }

  static std::string Call(const std::string& s, std::size_t indent) {
    return Call(s.data(), s.size(), indent);
  }
};

TEST_F(WriteLiteralStringTest_631, EmptyString_WritesOnlyHeader_631) {
  const std::string out = Call("", 0);

  // Must begin with a literal block header.
  EXPECT_EQ(out, "|\n");
}

TEST_F(WriteLiteralStringTest_631, SingleLine_IndentZero_PreservesText_631) {
  const std::string out = Call("abc", 0);

  ASSERT_GE(out.size(), std::string("|\n").size());
  EXPECT_EQ(out.substr(0, 2), "|\n");
  EXPECT_NE(out.find("abc"), std::string::npos);
  // With no newline in input, output should not introduce extra newlines
  // beyond the header newline.
  EXPECT_EQ(std::count(out.begin(), out.end(), '\n'), 1);
}

TEST_F(WriteLiteralStringTest_631, MultiLine_PreservesNewlineCount_631) {
  const std::string input = "a\nb\n";
  const std::string out = Call(input, 0);

  // Implementation writes "|\n" and then writes one '\n' per input newline.
  const int input_newlines = static_cast<int>(std::count(input.begin(), input.end(), '\n'));
  const int out_newlines = static_cast<int>(std::count(out.begin(), out.end(), '\n'));
  EXPECT_EQ(out_newlines, 1 + input_newlines);

  EXPECT_EQ(out.substr(0, 2), "|\n");
  EXPECT_NE(out.find('a'), std::string::npos);
  EXPECT_NE(out.find('b'), std::string::npos);
}

TEST_F(WriteLiteralStringTest_631, IndentTwo_AddsLeadingSpacesPerLine_631) {
  const std::string out = Call("a\nb", 2);

  // Expect:
  // "|\n"
  // "  a"
  // "\n"
  // "  b"
  EXPECT_EQ(out, "|\n  a\n  b");
}

TEST_F(WriteLiteralStringTest_631, Utf8Input_IsPreservedInOutput_631) {
  const std::string input = u8"€한";
  const std::string out = Call(input, 0);

  EXPECT_EQ(out.substr(0, 2), "|\n");
  EXPECT_NE(out.find(input), std::string::npos);
}

TEST_F(WriteLiteralStringTest_631, SizeParameter_RespectsProvidedSize_631) {
  const std::string full = "abcdef";
  // Only write first 3 bytes/characters.
  std::ostringstream oss;
  YAML::ostream_wrapper outw(oss);

  const bool ok = YAML::Utils::WriteLiteralString(outw, full.data(), 3, 0);
  ASSERT_TRUE(ok);

  const std::string out = oss.str();
  EXPECT_EQ(out.substr(0, 2), "|\n");
  EXPECT_NE(out.find("abc"), std::string::npos);
  EXPECT_EQ(out.find("def"), std::string::npos);
}

TEST_F(WriteLiteralStringTest_631, ReturnValue_IsTrueForTypicalInputs_631) {
  {
    std::ostringstream oss;
    YAML::ostream_wrapper out(oss);
    EXPECT_TRUE(YAML::Utils::WriteLiteralString(out, "x", 1, 0));
  }
  {
    std::ostringstream oss;
    YAML::ostream_wrapper out(oss);
    const std::string s = "line1\nline2";
    EXPECT_TRUE(YAML::Utils::WriteLiteralString(out, s.data(), s.size(), 4));
  }
}

}  // namespace