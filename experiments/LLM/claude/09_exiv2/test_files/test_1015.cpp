#include <gtest/gtest.h>
#include <string>

// Since trim is a static function in the .cpp file, we include the source
// to access it for testing purposes. This is a common technique for testing
// static/internal functions.
// We need the helper functions ltrim and rtrim which trim is built upon.
// Including the necessary headers from exiv2.
#include "minoltamn_int.hpp"

// For accessing the static function, we may need to include the cpp directly
// or use a test-access pattern. Here we replicate the minimal needed interface.
namespace {

// Helper to access the trim function - include the source file
// This is necessary because trim is static
}

// If direct access isn't possible, we test through any public API that uses trim.
// However, based on the task requirements, we write tests for the trim interface.

// Assuming we can access the function through some mechanism:
namespace Exiv2 {
namespace Internal {
// Forward declaration for testing - the actual implementation is in the .cpp
std::string& trim(std::string& s, const char* t = " \t\n\r\f\v");
std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v");
std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v");
}  // namespace Internal
}  // namespace Exiv2

class TrimTest_1015 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Normal operation tests

TEST_F(TrimTest_1015, TrimRemovesLeadingSpaces_1015) {
  std::string s = "   hello";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimRemovesTrailingSpaces_1015) {
  std::string s = "hello   ";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimRemovesBothLeadingAndTrailingSpaces_1015) {
  std::string s = "   hello   ";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimPreservesInternalSpaces_1015) {
  std::string s = "  hello world  ";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello world");
}

TEST_F(TrimTest_1015, TrimRemovesTabs_1015) {
  std::string s = "\thello\t";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimRemovesNewlines_1015) {
  std::string s = "\nhello\n";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimRemovesCarriageReturns_1015) {
  std::string s = "\rhello\r";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimRemovesFormFeed_1015) {
  std::string s = "\fhello\f";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimRemovesVerticalTab_1015) {
  std::string s = "\vhello\v";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimRemovesMixedWhitespace_1015) {
  std::string s = " \t\n\r\f\vhello \t\n\r\f\v";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimNoOpOnCleanString_1015) {
  std::string s = "hello";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimReturnsReferenceToSameString_1015) {
  std::string s = "  hello  ";
  std::string& result = Exiv2::Internal::trim(s);
  EXPECT_EQ(&result, &s);
}

// Boundary conditions

TEST_F(TrimTest_1015, TrimEmptyString_1015) {
  std::string s = "";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "");
}

TEST_F(TrimTest_1015, TrimAllWhitespaceString_1015) {
  std::string s = "   \t\n\r  ";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "");
}

TEST_F(TrimTest_1015, TrimSingleCharacter_1015) {
  std::string s = "a";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "a");
}

TEST_F(TrimTest_1015, TrimSingleSpace_1015) {
  std::string s = " ";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "");
}

TEST_F(TrimTest_1015, TrimSingleCharWithSpaces_1015) {
  std::string s = " a ";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "a");
}

// Custom trim characters

TEST_F(TrimTest_1015, TrimCustomCharacters_1015) {
  std::string s = "xxxhelloxxx";
  Exiv2::Internal::trim(s, "x");
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimCustomCharactersMultiple_1015) {
  std::string s = "xyzhelloyzx";
  Exiv2::Internal::trim(s, "xyz");
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimCustomCharactersNoMatch_1015) {
  std::string s = "hello";
  Exiv2::Internal::trim(s, "xyz");
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimCustomCharactersAllMatch_1015) {
  std::string s = "xxxx";
  Exiv2::Internal::trim(s, "x");
  EXPECT_EQ(s, "");
}

TEST_F(TrimTest_1015, TrimCustomCharactersPreservesDefaultWhitespace_1015) {
  std::string s = " hello ";
  Exiv2::Internal::trim(s, "x");
  EXPECT_EQ(s, " hello ");
}

TEST_F(TrimTest_1015, TrimCustomEmptyTrimSet_1015) {
  std::string s = "  hello  ";
  Exiv2::Internal::trim(s, "");
  EXPECT_EQ(s, "  hello  ");
}

TEST_F(TrimTest_1015, TrimLongWhitespacePrefix_1015) {
  std::string s = std::string(1000, ' ') + "hello";
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimLongWhitespaceSuffix_1015) {
  std::string s = "hello" + std::string(1000, ' ');
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}

TEST_F(TrimTest_1015, TrimLongWhitespaceBothSides_1015) {
  std::string s = std::string(500, ' ') + "hello" + std::string(500, ' ');
  Exiv2::Internal::trim(s);
  EXPECT_EQ(s, "hello");
}
