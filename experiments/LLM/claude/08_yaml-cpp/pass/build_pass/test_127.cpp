#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for Utf8_ByteOrderMark tests
class Utf8ByteOrderMarkTest_127 : public ::testing::Test {
 protected:
  const RegEx& bom = Exp::Utf8_ByteOrderMark();
};

// Test that the BOM regex matches the exact UTF-8 BOM sequence
TEST_F(Utf8ByteOrderMarkTest_127, MatchesExactBOM_127) {
  std::string bomStr = "\xEF\xBB\xBF";
  EXPECT_TRUE(bom.Matches(bomStr));
}

// Test that Match returns the correct length (3 bytes) for a valid BOM
TEST_F(Utf8ByteOrderMarkTest_127, MatchReturnsCorrectLengthForBOM_127) {
  std::string bomStr = "\xEF\xBB\xBF";
  int result = bom.Match(bomStr);
  EXPECT_EQ(3, result);
}

// Test that the BOM regex matches a BOM followed by additional characters
TEST_F(Utf8ByteOrderMarkTest_127, MatchReturnsBOMLengthWithTrailingChars_127) {
  std::string bomPlusExtra = "\xEF\xBB\xBF" "hello";
  int result = bom.Match(bomPlusExtra);
  EXPECT_EQ(3, result);
}

// Test that the BOM regex does not match an empty string
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchEmptyString_127) {
  std::string empty = "";
  EXPECT_FALSE(bom.Matches(empty));
}

// Test that Match returns -1 (or non-positive) for empty string
TEST_F(Utf8ByteOrderMarkTest_127, MatchReturnsNegativeForEmptyString_127) {
  std::string empty = "";
  int result = bom.Match(empty);
  EXPECT_LT(result, 1);
}

// Test that the BOM regex does not match a partial BOM (only first byte)
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchPartialBOM_OneByte_127) {
  std::string partial = "\xEF";
  EXPECT_FALSE(bom.Matches(partial));
}

// Test that the BOM regex does not match a partial BOM (first two bytes)
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchPartialBOM_TwoBytes_127) {
  std::string partial = "\xEF\xBB";
  EXPECT_FALSE(bom.Matches(partial));
}

// Test that the BOM regex does not match regular ASCII text
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchRegularASCII_127) {
  std::string ascii = "hello";
  EXPECT_FALSE(bom.Matches(ascii));
}

// Test that Match returns -1 for non-matching string
TEST_F(Utf8ByteOrderMarkTest_127, MatchReturnsNegativeForNonMatch_127) {
  std::string ascii = "hello";
  int result = bom.Match(ascii);
  EXPECT_LT(result, 1);
}

// Test that the BOM regex does not match a wrong first byte
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchWrongFirstByte_127) {
  std::string wrong = "\xEE\xBB\xBF";
  EXPECT_FALSE(bom.Matches(wrong));
}

// Test that the BOM regex does not match a wrong second byte
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchWrongSecondByte_127) {
  std::string wrong = "\xEF\xBA\xBF";
  EXPECT_FALSE(bom.Matches(wrong));
}

// Test that the BOM regex does not match a wrong third byte
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchWrongThirdByte_127) {
  std::string wrong = "\xEF\xBB\xBE";
  EXPECT_FALSE(bom.Matches(wrong));
}

// Test that calling Utf8_ByteOrderMark() multiple times returns the same object (static)
TEST_F(Utf8ByteOrderMarkTest_127, ReturnsSameStaticInstance_127) {
  const RegEx& bom1 = Exp::Utf8_ByteOrderMark();
  const RegEx& bom2 = Exp::Utf8_ByteOrderMark();
  EXPECT_EQ(&bom1, &bom2);
}

// Test that the BOM regex does not match a single character
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchSingleChar_127) {
  EXPECT_FALSE(bom.Matches('a'));
}

// Test that the BOM regex does not match first byte of BOM as single char
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchFirstBOMByteAsChar_127) {
  EXPECT_FALSE(bom.Matches('\xEF'));
}

// Test that a string with BOM bytes in wrong order does not match
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchReversedBOM_127) {
  std::string reversed = "\xBF\xBB\xEF";
  EXPECT_FALSE(bom.Matches(reversed));
}

// Test that a string with only null bytes does not match
TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchNullBytes_127) {
  std::string nulls(3, '\0');
  EXPECT_FALSE(bom.Matches(nulls));
}

// Test Match on partial BOM returns negative
TEST_F(Utf8ByteOrderMarkTest_127, MatchReturnsNegativeForPartialBOM_127) {
  std::string partial = "\xEF\xBB";
  int result = bom.Match(partial);
  EXPECT_LT(result, 1);
}

}  // namespace
}  // namespace YAML
