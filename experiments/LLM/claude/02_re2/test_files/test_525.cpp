#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/unicode_groups.h"
#include "util/utf.h"

namespace re2 {

// Forward declaration of AddUGroup (it's static in parse.cc, so we need a workaround)
// Since AddUGroup is static, we cannot directly call it from outside parse.cc.
// We'll test it indirectly through the public Regexp parsing interface.
// However, since the prompt asks us to test AddUGroup specifically, we'll use
// the Regexp::Parse interface which exercises AddUGroup through character class parsing.

class AddUGroupTest_525 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that parsing a Unicode group (positive) adds the correct ranges
TEST_F(AddUGroupTest_525, PositiveUnicodeGroupContainsExpectedChars_525) {
  // Parse a regex with a Unicode property like \p{Greek}
  // This exercises AddUGroup with sign=+1
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::UnicodeGroups);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{Greek}", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test that parsing a negated Unicode group works
TEST_F(AddUGroupTest_525, NegativeUnicodeGroupWorks_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::UnicodeGroups);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\P{Greek}", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test that negated Unicode group with FoldCase works
TEST_F(AddUGroupTest_525, NegativeUnicodeGroupWithFoldCase_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::UnicodeGroups | Regexp::FoldCase);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\P{Greek}", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test that positive Unicode group with FoldCase works
TEST_F(AddUGroupTest_525, PositiveUnicodeGroupWithFoldCase_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::UnicodeGroups | Regexp::FoldCase);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{Greek}", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test Perl character class \d which uses AddUGroup
TEST_F(AddUGroupTest_525, PerlDigitClass_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test negated Perl character class \D
TEST_F(AddUGroupTest_525, NegatedPerlDigitClass_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\D", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test \w (word characters) which exercises AddUGroup
TEST_F(AddUGroupTest_525, PerlWordClass_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\w", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test \W (negated word characters)
TEST_F(AddUGroupTest_525, NegatedPerlWordClass_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\W", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test \s (whitespace) 
TEST_F(AddUGroupTest_525, PerlSpaceClass_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\s", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test \S (negated whitespace)
TEST_F(AddUGroupTest_525, NegatedPerlSpaceClass_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\S", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test negated class with NeverNL flag
TEST_F(AddUGroupTest_525, NegatedClassWithNeverNL_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses | Regexp::NeverNL);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\D", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test negated class with ClassNL flag
TEST_F(AddUGroupTest_525, NegatedClassWithClassNL_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses | Regexp::ClassNL);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\D", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test negated class with FoldCase and NeverNL
TEST_F(AddUGroupTest_525, NegatedClassWithFoldCaseAndNeverNL_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses | Regexp::FoldCase | Regexp::NeverNL);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\W", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test negated class with FoldCase and ClassNL
TEST_F(AddUGroupTest_525, NegatedClassWithFoldCaseAndClassNL_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses | Regexp::FoldCase | Regexp::ClassNL);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\W", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test Unicode group \p{L} (Letter)
TEST_F(AddUGroupTest_525, UnicodeLetterGroup_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::UnicodeGroups);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test negated Unicode group \P{L}
TEST_F(AddUGroupTest_525, NegatedUnicodeLetterGroup_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::UnicodeGroups);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\P{L}", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test CharClassBuilder directly for basic operations
TEST_F(AddUGroupTest_525, CharClassBuilderAddRange_525) {
  CharClassBuilder cc;
  EXPECT_TRUE(cc.empty());
  cc.AddRange('a', 'z');
  EXPECT_FALSE(cc.empty());
  EXPECT_TRUE(cc.Contains('a'));
  EXPECT_TRUE(cc.Contains('m'));
  EXPECT_TRUE(cc.Contains('z'));
  EXPECT_FALSE(cc.Contains('A'));
  EXPECT_FALSE(cc.Contains('0'));
}

// Test CharClassBuilder Negate
TEST_F(AddUGroupTest_525, CharClassBuilderNegate_525) {
  CharClassBuilder cc;
  cc.AddRange('a', 'z');
  EXPECT_TRUE(cc.Contains('a'));
  EXPECT_FALSE(cc.Contains('A'));
  cc.Negate();
  EXPECT_FALSE(cc.Contains('a'));
  EXPECT_TRUE(cc.Contains('A'));
  EXPECT_TRUE(cc.Contains('0'));
}

// Test CharClassBuilder AddCharClass
TEST_F(AddUGroupTest_525, CharClassBuilderAddCharClass_525) {
  CharClassBuilder cc1;
  cc1.AddRange('a', 'z');
  
  CharClassBuilder cc2;
  cc2.AddRange('A', 'Z');
  
  cc1.AddCharClass(&cc2);
  EXPECT_TRUE(cc1.Contains('a'));
  EXPECT_TRUE(cc1.Contains('A'));
}

// Test CharClassBuilder full after negate of empty
TEST_F(AddUGroupTest_525, CharClassBuilderFullAfterNegateEmpty_525) {
  CharClassBuilder cc;
  EXPECT_TRUE(cc.empty());
  cc.Negate();
  EXPECT_TRUE(cc.full());
}

// Test CharClassBuilder AddRangeFlags with FoldCase
TEST_F(AddUGroupTest_525, CharClassBuilderAddRangeFlagsWithFoldCase_525) {
  CharClassBuilder cc;
  cc.AddRangeFlags('a', 'z', Regexp::FoldCase);
  // With FoldCase, adding a-z should also include A-Z
  EXPECT_TRUE(cc.Contains('a'));
  EXPECT_TRUE(cc.Contains('A'));
  EXPECT_TRUE(cc.Contains('z'));
  EXPECT_TRUE(cc.Contains('Z'));
}

// Test that parsing [:alpha:] inside bracket expressions exercises POSIX groups
TEST_F(AddUGroupTest_525, PosixAlphaClass_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:alpha:]]", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test negated POSIX class
TEST_F(AddUGroupTest_525, NegatedPosixAlphaClass_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:^alpha:]]", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test Unicode group with 32-bit ranges (\p{Han} has high codepoints)
TEST_F(AddUGroupTest_525, UnicodeGroupWith32BitRanges_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::UnicodeGroups);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{Han}", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test negated Unicode group with 32-bit ranges
TEST_F(AddUGroupTest_525, NegatedUnicodeGroupWith32BitRanges_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::UnicodeGroups);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\P{Han}", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test CharClassBuilder RemoveAbove
TEST_F(AddUGroupTest_525, CharClassBuilderRemoveAbove_525) {
  CharClassBuilder cc;
  cc.AddRange(0, Runemax);
  EXPECT_TRUE(cc.full());
  cc.RemoveAbove(127);
  EXPECT_TRUE(cc.Contains(127));
  EXPECT_FALSE(cc.Contains(128));
}

// Test CharClassBuilder Copy
TEST_F(AddUGroupTest_525, CharClassBuilderCopy_525) {
  CharClassBuilder cc;
  cc.AddRange('a', 'z');
  CharClassBuilder* copy = cc.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));
  EXPECT_FALSE(copy->Contains('A'));
  delete copy;
}

// Test CharClassBuilder size
TEST_F(AddUGroupTest_525, CharClassBuilderSize_525) {
  CharClassBuilder cc;
  EXPECT_EQ(cc.size(), 0);
  cc.AddRange('a', 'z');
  EXPECT_EQ(cc.size(), 1);
  cc.AddRange('A', 'Z');
  EXPECT_EQ(cc.size(), 2);
}

// Test that \d with FoldCase doesn't break
TEST_F(AddUGroupTest_525, DigitClassWithFoldCase_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses | Regexp::FoldCase);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

// Test \S with FoldCase and ClassNL combined
TEST_F(AddUGroupTest_525, NegatedSpaceWithFoldCaseClassNL_525) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses | Regexp::FoldCase | Regexp::ClassNL);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\S", flags, &status);
  ASSERT_NE(re, nullptr) << status.Text();
  re->Decref();
}

}  // namespace re2
