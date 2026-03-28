// EscapeSpecialChars_test_2660.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>

// Include GooString definition.
#include "TestProjects/poppler/goo/GooString.h"

// NOTE: EscapeSpecialChars is a file-local (static) function inside HtmlLinks.cc.
// To test it as a black box via its observable behavior, we include the .cc so the
// symbol is visible in this translation unit.
#include "TestProjects/poppler/utils/HtmlLinks.cc"

namespace {

class EscapeSpecialCharsTest_2660 : public ::testing::Test {
protected:
  static std::string ToStdString(const GooString &s) { return s.toStr(); }
};

TEST_F(EscapeSpecialCharsTest_2660, ReturnsNullWhenNoSpecialCharacters_2660) {
  GooString input("hello world 123 _-./");
  auto out = EscapeSpecialChars(&input);

  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(ToStdString(input), "hello world 123 _-./");
}

TEST_F(EscapeSpecialCharsTest_2660, ReturnsNullForEmptyString_2660) {
  GooString input("");
  auto out = EscapeSpecialChars(&input);

  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(ToStdString(input), "");
}

TEST_F(EscapeSpecialCharsTest_2660, EscapesDoubleQuoteOnly_2660) {
  GooString input("\"");
  auto out = EscapeSpecialChars(&input);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(ToStdString(*out), "&quot;");
  // Original should not be modified.
  EXPECT_EQ(ToStdString(input), "\"");
}

TEST_F(EscapeSpecialCharsTest_2660, EscapesAmpersandOnly_2660) {
  GooString input("&");
  auto out = EscapeSpecialChars(&input);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(ToStdString(*out), "&amp;");
  EXPECT_EQ(ToStdString(input), "&");
}

TEST_F(EscapeSpecialCharsTest_2660, EscapesLessThanAndGreaterThan_2660) {
  GooString input("<>");
  auto out = EscapeSpecialChars(&input);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(ToStdString(*out), "&lt;&gt;");
  EXPECT_EQ(ToStdString(input), "<>");
}

TEST_F(EscapeSpecialCharsTest_2660, EscapesAllSupportedCharactersMixed_2660) {
  GooString input("a&b<c>d\"e");
  auto out = EscapeSpecialChars(&input);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(ToStdString(*out), "a&amp;b&lt;c&gt;d&quot;e");
  EXPECT_EQ(ToStdString(input), "a&b<c>d\"e");
}

TEST_F(EscapeSpecialCharsTest_2660, EscapesConsecutiveSpecialCharacters_2660) {
  GooString input("\"\"&&<<>>");
  auto out = EscapeSpecialChars(&input);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(ToStdString(*out), "&quot;&quot;&amp;&amp;&lt;&lt;&gt;&gt;");
  EXPECT_EQ(ToStdString(input), "\"\"&&<<>>");
}

TEST_F(EscapeSpecialCharsTest_2660, EscapesSpecialCharactersAtBoundaries_2660) {
  GooString input("\"start&middle<end>\"");
  auto out = EscapeSpecialChars(&input);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(ToStdString(*out), "&quot;start&amp;middle&lt;end&gt;&quot;");
  EXPECT_EQ(ToStdString(input), "\"start&middle<end>\"");
}

TEST_F(EscapeSpecialCharsTest_2660, EscapesAmpersandEvenIfPartOfExistingEntity_2660) {
  // Boundary/error-ish case: if the input already contains something that looks like an entity,
  // the observable behavior is to escape literal '&' characters as well.
  GooString input("&amp;");
  auto out = EscapeSpecialChars(&input);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(ToStdString(*out), "&amp;amp;");
  EXPECT_EQ(ToStdString(input), "&amp;");
}

} // namespace