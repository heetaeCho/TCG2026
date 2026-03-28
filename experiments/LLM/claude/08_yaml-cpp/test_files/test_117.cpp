#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test that Tab() returns a RegEx that matches the tab character
TEST(ExpTabTest_117, TabMatchesTabCharacter_117) {
  const RegEx& tab = Exp::Tab();
  EXPECT_TRUE(tab.Matches('\t'));
}

// Test that Tab() does not match a space character
TEST(ExpTabTest_117, TabDoesNotMatchSpace_117) {
  const RegEx& tab = Exp::Tab();
  EXPECT_FALSE(tab.Matches(' '));
}

// Test that Tab() does not match a newline character
TEST(ExpTabTest_117, TabDoesNotMatchNewline_117) {
  const RegEx& tab = Exp::Tab();
  EXPECT_FALSE(tab.Matches('\n'));
}

// Test that Tab() does not match a null character
TEST(ExpTabTest_117, TabDoesNotMatchNullChar_117) {
  const RegEx& tab = Exp::Tab();
  EXPECT_FALSE(tab.Matches('\0'));
}

// Test that Tab() does not match a regular letter
TEST(ExpTabTest_117, TabDoesNotMatchLetter_117) {
  const RegEx& tab = Exp::Tab();
  EXPECT_FALSE(tab.Matches('a'));
}

// Test that Tab() does not match a digit
TEST(ExpTabTest_117, TabDoesNotMatchDigit_117) {
  const RegEx& tab = Exp::Tab();
  EXPECT_FALSE(tab.Matches('0'));
}

// Test that Tab() returns the same reference on multiple calls (static instance)
TEST(ExpTabTest_117, TabReturnsSameInstance_117) {
  const RegEx& tab1 = Exp::Tab();
  const RegEx& tab2 = Exp::Tab();
  EXPECT_EQ(&tab1, &tab2);
}

// Test that Tab() matches a string containing just a tab
TEST(ExpTabTest_117, TabMatchesTabString_117) {
  const RegEx& tab = Exp::Tab();
  std::string tabStr("\t");
  EXPECT_TRUE(tab.Matches(tabStr));
}

// Test that Tab() Match returns 1 for a tab string (matches one character)
TEST(ExpTabTest_117, TabMatchReturnsOneForTabString_117) {
  const RegEx& tab = Exp::Tab();
  std::string tabStr("\t");
  EXPECT_EQ(1, tab.Match(tabStr));
}

// Test that Tab() Match returns -1 for a non-tab string
TEST(ExpTabTest_117, TabMatchReturnsNegativeForNonTab_117) {
  const RegEx& tab = Exp::Tab();
  std::string str("a");
  EXPECT_EQ(-1, tab.Match(str));
}

// Test that Tab() does not match an empty string
TEST(ExpTabTest_117, TabDoesNotMatchEmptyString_117) {
  const RegEx& tab = Exp::Tab();
  std::string empty;
  EXPECT_FALSE(tab.Matches(empty));
}

// Test that Tab() Match returns -1 for an empty string
TEST(ExpTabTest_117, TabMatchReturnsNegativeForEmptyString_117) {
  const RegEx& tab = Exp::Tab();
  std::string empty;
  EXPECT_EQ(-1, tab.Match(empty));
}

// Test that Tab() does not match carriage return
TEST(ExpTabTest_117, TabDoesNotMatchCarriageReturn_117) {
  const RegEx& tab = Exp::Tab();
  EXPECT_FALSE(tab.Matches('\r'));
}

// Test Tab() Match on a string starting with tab followed by other characters
TEST(ExpTabTest_117, TabMatchReturnsOneForStringStartingWithTab_117) {
  const RegEx& tab = Exp::Tab();
  std::string str("\tabc");
  EXPECT_EQ(1, tab.Match(str));
}

// Test Tab() does not match vertical tab
TEST(ExpTabTest_117, TabDoesNotMatchVerticalTab_117) {
  const RegEx& tab = Exp::Tab();
  EXPECT_FALSE(tab.Matches('\v'));
}

}  // namespace
}  // namespace YAML
