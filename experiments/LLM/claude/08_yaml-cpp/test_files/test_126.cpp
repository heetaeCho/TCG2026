#include <gtest/gtest.h>
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class NotPrintableTest_126 : public ::testing::Test {
 protected:
  const RegEx& notPrintable = Exp::NotPrintable();
};

// Test that the function returns a reference to a static object (same address on repeated calls)
TEST_F(NotPrintableTest_126, ReturnsSameStaticInstance_126) {
  const RegEx& first = Exp::NotPrintable();
  const RegEx& second = Exp::NotPrintable();
  EXPECT_EQ(&first, &second);
}

// Test that NUL character (0x00) is matched as not printable
TEST_F(NotPrintableTest_126, MatchesNulCharacter_126) {
  char nul = '\x00';
  EXPECT_TRUE(notPrintable.Matches(nul));
}

// Test that 0x01 through 0x08 are matched as not printable
TEST_F(NotPrintableTest_126, MatchesControlChars_0x01_to_0x08_126) {
  for (char ch = '\x01'; ch <= '\x08'; ++ch) {
    EXPECT_TRUE(notPrintable.Matches(ch)) << "Expected 0x" << std::hex << (int)(unsigned char)ch << " to match";
  }
}

// Test that 0x0B (vertical tab) is matched as not printable
TEST_F(NotPrintableTest_126, Matches_0x0B_126) {
  EXPECT_TRUE(notPrintable.Matches('\x0B'));
}

// Test that 0x0C (form feed) is matched as not printable
TEST_F(NotPrintableTest_126, Matches_0x0C_126) {
  EXPECT_TRUE(notPrintable.Matches('\x0C'));
}

// Test that 0x7F (DEL) is matched as not printable
TEST_F(NotPrintableTest_126, Matches_DEL_0x7F_126) {
  EXPECT_TRUE(notPrintable.Matches('\x7F'));
}

// Test that 0x0E through 0x1F are matched as not printable
TEST_F(NotPrintableTest_126, MatchesControlChars_0x0E_to_0x1F_126) {
  for (int i = 0x0E; i <= 0x1F; ++i) {
    char ch = static_cast<char>(i);
    EXPECT_TRUE(notPrintable.Matches(ch)) << "Expected 0x" << std::hex << i << " to match";
  }
}

// Test that regular printable ASCII characters do NOT match
TEST_F(NotPrintableTest_126, DoesNotMatchPrintableASCII_126) {
  // Space through tilde are printable
  for (char ch = ' '; ch <= '~'; ++ch) {
    EXPECT_FALSE(notPrintable.Matches(ch)) << "Did not expect '" << ch << "' (0x" << std::hex << (int)(unsigned char)ch << ") to match";
  }
}

// Test that 0x09 (TAB) does NOT match (it's printable in YAML)
TEST_F(NotPrintableTest_126, DoesNotMatchTab_126) {
  EXPECT_FALSE(notPrintable.Matches('\x09'));
}

// Test that 0x0A (LF) does NOT match (it's printable/allowed in YAML)
TEST_F(NotPrintableTest_126, DoesNotMatchLineFeed_126) {
  EXPECT_FALSE(notPrintable.Matches('\x0A'));
}

// Test that 0x0D (CR) does NOT match (it's allowed in YAML)
TEST_F(NotPrintableTest_126, DoesNotMatchCarriageReturn_126) {
  EXPECT_FALSE(notPrintable.Matches('\x0D'));
}

// Test matching against a string containing a not-printable character
TEST_F(NotPrintableTest_126, MatchesStringWithNulByte_126) {
  std::string s(1, '\x00');
  EXPECT_TRUE(notPrintable.Matches(s));
}

// Test matching against a string with a control character
TEST_F(NotPrintableTest_126, MatchesStringWithControlChar_126) {
  std::string s(1, '\x01');
  EXPECT_TRUE(notPrintable.Matches(s));
}

// Test that a printable string does not match
TEST_F(NotPrintableTest_126, DoesNotMatchPrintableString_126) {
  std::string s = "A";
  EXPECT_FALSE(notPrintable.Matches(s));
}

// Test Match() returns appropriate value for matching character
TEST_F(NotPrintableTest_126, MatchReturnsPositiveForNotPrintable_126) {
  std::string s(1, '\x01');
  int result = notPrintable.Match(s);
  EXPECT_GE(result, 1);
}

// Test Match() returns -1 or 0 for non-matching character
TEST_F(NotPrintableTest_126, MatchReturnsNonPositiveForPrintable_126) {
  std::string s = "A";
  int result = notPrintable.Match(s);
  EXPECT_LE(result, 0);
}

// Test the two-byte UTF-8 sequence \xC2\x80 (U+0080) matches as not printable
TEST_F(NotPrintableTest_126, MatchesTwoByteUTF8_C280_126) {
  std::string s = "\xC2\x80";
  int result = notPrintable.Match(s);
  EXPECT_EQ(result, 2);
}

// Test the two-byte UTF-8 sequence \xC2\x84 (U+0084) matches as not printable
TEST_F(NotPrintableTest_126, MatchesTwoByteUTF8_C284_126) {
  std::string s = "\xC2\x84";
  int result = notPrintable.Match(s);
  EXPECT_EQ(result, 2);
}

// Test the two-byte UTF-8 sequence \xC2\x85 (U+0085, NEL) does NOT match (it's allowed)
TEST_F(NotPrintableTest_126, DoesNotMatchTwoByteUTF8_C285_126) {
  std::string s = "\xC2\x85";
  int result = notPrintable.Match(s);
  EXPECT_LE(result, 0);
}

// Test the two-byte UTF-8 sequence \xC2\x86 (U+0086) matches as not printable
TEST_F(NotPrintableTest_126, MatchesTwoByteUTF8_C286_126) {
  std::string s = "\xC2\x86";
  int result = notPrintable.Match(s);
  EXPECT_EQ(result, 2);
}

// Test the two-byte UTF-8 sequence \xC2\x9F (U+009F) matches as not printable
TEST_F(NotPrintableTest_126, MatchesTwoByteUTF8_C29F_126) {
  std::string s = "\xC2\x9F";
  int result = notPrintable.Match(s);
  EXPECT_EQ(result, 2);
}

// Test the two-byte UTF-8 sequence \xC2\xA0 (U+00A0) does NOT match
TEST_F(NotPrintableTest_126, DoesNotMatchTwoByteUTF8_C2A0_126) {
  std::string s = "\xC2\xA0";
  int result = notPrintable.Match(s);
  EXPECT_LE(result, 0);
}

// Test empty string does not match
TEST_F(NotPrintableTest_126, DoesNotMatchEmptyString_126) {
  std::string s;
  int result = notPrintable.Match(s);
  EXPECT_LE(result, 0);
}

// Test all control chars in the range used in the string constructor
TEST_F(NotPrintableTest_126, MatchesAllExplicitControlChars_126) {
  const char explicitChars[] = {'\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x0B', '\x0C', '\x7F'};
  for (char ch : explicitChars) {
    EXPECT_TRUE(notPrintable.Matches(ch)) << "Expected 0x" << std::hex << (int)(unsigned char)ch << " to match";
  }
}

// Test digits are not matched
TEST_F(NotPrintableTest_126, DoesNotMatchDigits_126) {
  for (char ch = '0'; ch <= '9'; ++ch) {
    EXPECT_FALSE(notPrintable.Matches(ch));
  }
}

// Test lowercase letters are not matched
TEST_F(NotPrintableTest_126, DoesNotMatchLowercaseLetters_126) {
  for (char ch = 'a'; ch <= 'z'; ++ch) {
    EXPECT_FALSE(notPrintable.Matches(ch));
  }
}

// Test uppercase letters are not matched
TEST_F(NotPrintableTest_126, DoesNotMatchUppercaseLetters_126) {
  for (char ch = 'A'; ch <= 'Z'; ++ch) {
    EXPECT_FALSE(notPrintable.Matches(ch));
  }
}

}  // namespace
}  // namespace YAML
