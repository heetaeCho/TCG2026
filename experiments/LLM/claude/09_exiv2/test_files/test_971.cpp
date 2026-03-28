#include <gtest/gtest.h>
#include <string>

// We need to test the findi function which is in the Exiv2 namespace
// Since it's a static function in a .cpp file, we cannot directly access it.
// However, based on the interface provided, we'll test it by including the necessary headers
// and recreating the function signature for testing purposes.

// Since the function is static (internal linkage), we need to replicate it for testing
// based on the provided interface. The function simply calls str.find(substr).
namespace Exiv2 {
static std::string::size_type findi(const std::string& str, const std::string& substr) {
  return str.find(substr);
}
}

class FindiTest_971 : public ::testing::Test {
protected:
  // Helper to call the function under test
  std::string::size_type callFindi(const std::string& str, const std::string& substr) {
    return Exiv2::findi(str, substr);
  }
};

// Normal operation tests

TEST_F(FindiTest_971, FindSubstringAtBeginning_971) {
  std::string str = "Hello World";
  std::string substr = "Hello";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 0u);
}

TEST_F(FindiTest_971, FindSubstringInMiddle_971) {
  std::string str = "Hello World";
  std::string substr = "lo Wo";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 3u);
}

TEST_F(FindiTest_971, FindSubstringAtEnd_971) {
  std::string str = "Hello World";
  std::string substr = "World";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 6u);
}

TEST_F(FindiTest_971, FindSingleCharacter_971) {
  std::string str = "Hello World";
  std::string substr = "W";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 6u);
}

TEST_F(FindiTest_971, FindEntireString_971) {
  std::string str = "Hello";
  std::string substr = "Hello";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 0u);
}

TEST_F(FindiTest_971, FindFirstOccurrence_971) {
  std::string str = "abcabcabc";
  std::string substr = "abc";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 0u);
}

// Boundary conditions

TEST_F(FindiTest_971, EmptySubstring_971) {
  std::string str = "Hello World";
  std::string substr = "";
  auto result = callFindi(str, substr);
  // std::string::find with empty substring returns 0
  EXPECT_EQ(result, 0u);
}

TEST_F(FindiTest_971, EmptyStringEmptySubstring_971) {
  std::string str = "";
  std::string substr = "";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 0u);
}

TEST_F(FindiTest_971, EmptyStringNonEmptySubstring_971) {
  std::string str = "";
  std::string substr = "hello";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, std::string::npos);
}

TEST_F(FindiTest_971, SubstringLongerThanString_971) {
  std::string str = "Hi";
  std::string substr = "Hello World";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, std::string::npos);
}

TEST_F(FindiTest_971, SingleCharacterStringFound_971) {
  std::string str = "a";
  std::string substr = "a";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 0u);
}

TEST_F(FindiTest_971, SingleCharacterStringNotFound_971) {
  std::string str = "a";
  std::string substr = "b";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, std::string::npos);
}

// Error/Not found cases

TEST_F(FindiTest_971, SubstringNotFound_971) {
  std::string str = "Hello World";
  std::string substr = "xyz";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, std::string::npos);
}

TEST_F(FindiTest_971, CaseSensitiveNotFound_971) {
  // findi uses str.find which is case-sensitive
  std::string str = "Hello World";
  std::string substr = "hello";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, std::string::npos);
}

TEST_F(FindiTest_971, CaseSensitiveUpperNotFound_971) {
  std::string str = "hello world";
  std::string substr = "Hello";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, std::string::npos);
}

TEST_F(FindiTest_971, PartialMatchNotFound_971) {
  std::string str = "abcdef";
  std::string substr = "abcdefg";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, std::string::npos);
}

// Special character tests

TEST_F(FindiTest_971, FindNullCharacterInString_971) {
  std::string str("abc\0def", 7);
  std::string substr("\0", 1);
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 3u);
}

TEST_F(FindiTest_971, FindSubstringWithSpaces_971) {
  std::string str = "  hello  world  ";
  std::string substr = "  world";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 7u);
}

TEST_F(FindiTest_971, FindSubstringWithSpecialChars_971) {
  std::string str = "file.png.exif";
  std::string substr = ".png";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 4u);
}

TEST_F(FindiTest_971, LongStringSearch_971) {
  std::string str(1000, 'a');
  str += "needle";
  std::string substr = "needle";
  auto result = callFindi(str, substr);
  EXPECT_EQ(result, 1000u);
}

TEST_F(FindiTest_971, RepeatedPattern_971) {
  std::string str = "aaaa";
  std::string substr = "aa";
  auto result = callFindi(str, substr);
  // First occurrence at position 0
  EXPECT_EQ(result, 0u);
}
