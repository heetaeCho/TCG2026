#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class CharClassBuilderTest_520 : public ::testing::Test {
 protected:
  void SetUp() override {
    builder_ = new CharClassBuilder();
  }

  void TearDown() override {
    delete builder_;
  }

  CharClassBuilder* builder_;
};

// Test basic AddRangeFlags with no special flags
TEST_F(CharClassBuilderTest_520, AddRangeFlags_BasicRange_NoFlags_520) {
  builder_->AddRangeFlags('a', 'z', Regexp::NoParseFlags);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
  EXPECT_FALSE(builder_->Contains('0'));
}

// Test AddRangeFlags with ClassNL flag - newline should be included
TEST_F(CharClassBuilderTest_520, AddRangeFlags_ClassNL_IncludesNewline_520) {
  builder_->AddRangeFlags(0, 127, Regexp::ClassNL);
  EXPECT_TRUE(builder_->Contains('\n'));
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(127));
}

// Test AddRangeFlags without ClassNL - newline should be excluded
TEST_F(CharClassBuilderTest_520, AddRangeFlags_NoClassNL_ExcludesNewline_520) {
  builder_->AddRangeFlags(0, 127, Regexp::NoParseFlags);
  EXPECT_FALSE(builder_->Contains('\n'));
  EXPECT_TRUE(builder_->Contains('\n' - 1));
  EXPECT_TRUE(builder_->Contains('\n' + 1));
  EXPECT_TRUE(builder_->Contains('a'));
}

// Test AddRangeFlags with NeverNL flag - newline should be excluded even with ClassNL
TEST_F(CharClassBuilderTest_520, AddRangeFlags_NeverNL_ExcludesNewline_520) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::ClassNL | Regexp::NeverNL);
  builder_->AddRangeFlags(0, 127, flags);
  EXPECT_FALSE(builder_->Contains('\n'));
  EXPECT_TRUE(builder_->Contains('\n' - 1));
  EXPECT_TRUE(builder_->Contains('\n' + 1));
}

// Test AddRangeFlags with FoldCase - should include both cases
TEST_F(CharClassBuilderTest_520, AddRangeFlags_FoldCase_520) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::ClassNL);
  builder_->AddRangeFlags('a', 'z', flags);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('Z'));
}

// Test AddRangeFlags with FoldCase and Latin1
TEST_F(CharClassBuilderTest_520, AddRangeFlags_FoldCase_Latin1_520) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::Latin1 | Regexp::ClassNL);
  builder_->AddRangeFlags('a', 'z', flags);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('Z'));
}

// Test single character range
TEST_F(CharClassBuilderTest_520, AddRangeFlags_SingleChar_520) {
  builder_->AddRangeFlags('x', 'x', Regexp::ClassNL);
  EXPECT_TRUE(builder_->Contains('x'));
  EXPECT_FALSE(builder_->Contains('w'));
  EXPECT_FALSE(builder_->Contains('y'));
}

// Test range that is exactly the newline character without ClassNL
TEST_F(CharClassBuilderTest_520, AddRangeFlags_ExactlyNewline_NoClassNL_520) {
  builder_->AddRangeFlags('\n', '\n', Regexp::NoParseFlags);
  EXPECT_FALSE(builder_->Contains('\n'));
}

// Test range that is exactly the newline character with ClassNL
TEST_F(CharClassBuilderTest_520, AddRangeFlags_ExactlyNewline_ClassNL_520) {
  builder_->AddRangeFlags('\n', '\n', Regexp::ClassNL);
  EXPECT_TRUE(builder_->Contains('\n'));
}

// Test range starting at newline without ClassNL
TEST_F(CharClassBuilderTest_520, AddRangeFlags_StartAtNewline_NoClassNL_520) {
  builder_->AddRangeFlags('\n', 'z', Regexp::NoParseFlags);
  EXPECT_FALSE(builder_->Contains('\n'));
  EXPECT_TRUE(builder_->Contains('\n' + 1));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test range ending at newline without ClassNL
TEST_F(CharClassBuilderTest_520, AddRangeFlags_EndAtNewline_NoClassNL_520) {
  builder_->AddRangeFlags(0, '\n', Regexp::NoParseFlags);
  EXPECT_FALSE(builder_->Contains('\n'));
  EXPECT_TRUE(builder_->Contains('\n' - 1));
  EXPECT_TRUE(builder_->Contains(0));
}

// Test that range below newline is unaffected when cutting newline
TEST_F(CharClassBuilderTest_520, AddRangeFlags_BelowNewlinePreserved_520) {
  builder_->AddRangeFlags(5, 20, Regexp::NoParseFlags);
  for (Rune r = 5; r <= 20; r++) {
    if (r == '\n')
      EXPECT_FALSE(builder_->Contains(r));
    else
      EXPECT_TRUE(builder_->Contains(r));
  }
}

// Test empty builder initially
TEST_F(CharClassBuilderTest_520, InitiallyEmpty_520) {
  EXPECT_TRUE(builder_->empty());
  EXPECT_EQ(builder_->size(), 0);
}

// Test that AddRangeFlags makes builder non-empty
TEST_F(CharClassBuilderTest_520, AddRangeFlags_MakesNonEmpty_520) {
  builder_->AddRangeFlags('a', 'z', Regexp::ClassNL);
  EXPECT_FALSE(builder_->empty());
}

// Test FoldCase without Latin1 for uppercase range
TEST_F(CharClassBuilderTest_520, AddRangeFlags_FoldCase_UpperToLower_520) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::ClassNL);
  builder_->AddRangeFlags('A', 'Z', flags);
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('Z'));
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test a range that doesn't include newline at all - no cut needed
TEST_F(CharClassBuilderTest_520, AddRangeFlags_RangeAboveNewline_NoCut_520) {
  builder_->AddRangeFlags('A', 'Z', Regexp::NoParseFlags);
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('Z'));
  EXPECT_FALSE(builder_->Contains('a'));
}

// Test a range below newline entirely - no cut needed
TEST_F(CharClassBuilderTest_520, AddRangeFlags_RangeBelowNewline_NoCut_520) {
  builder_->AddRangeFlags(0, '\n' - 1, Regexp::NoParseFlags);
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains('\n' - 1));
  EXPECT_FALSE(builder_->Contains('\n'));
}

// Test multiple calls to AddRangeFlags accumulate ranges
TEST_F(CharClassBuilderTest_520, AddRangeFlags_MultipleCalls_520) {
  builder_->AddRangeFlags('a', 'c', Regexp::ClassNL);
  builder_->AddRangeFlags('x', 'z', Regexp::ClassNL);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('b'));
  EXPECT_TRUE(builder_->Contains('c'));
  EXPECT_TRUE(builder_->Contains('x'));
  EXPECT_TRUE(builder_->Contains('y'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('d'));
  EXPECT_FALSE(builder_->Contains('w'));
}

// Test wide Unicode range with FoldCase (no Latin1)
TEST_F(CharClassBuilderTest_520, AddRangeFlags_UnicodeRange_FoldCase_520) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::ClassNL);
  // Add a small ASCII range and verify folding works
  builder_->AddRangeFlags('k', 'k', flags);
  EXPECT_TRUE(builder_->Contains('k'));
  EXPECT_TRUE(builder_->Contains('K'));
}

// Test with lo == '\n' + 1 (just above newline), no ClassNL - should not cut
TEST_F(CharClassBuilderTest_520, AddRangeFlags_JustAboveNewline_520) {
  builder_->AddRangeFlags('\n' + 1, '\n' + 5, Regexp::NoParseFlags);
  EXPECT_TRUE(builder_->Contains('\n' + 1));
  EXPECT_TRUE(builder_->Contains('\n' + 5));
  EXPECT_FALSE(builder_->Contains('\n'));
}

// Test with hi == '\n' - 1 (just below newline), no ClassNL - should not cut
TEST_F(CharClassBuilderTest_520, AddRangeFlags_JustBelowNewline_520) {
  builder_->AddRangeFlags('\n' - 3, '\n' - 1, Regexp::NoParseFlags);
  EXPECT_TRUE(builder_->Contains('\n' - 3));
  EXPECT_TRUE(builder_->Contains('\n' - 1));
  EXPECT_FALSE(builder_->Contains('\n'));
}

// Test Contains returns false for characters not added
TEST_F(CharClassBuilderTest_520, Contains_NotAdded_520) {
  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(0x10FFFF));
}

// Test FoldCase with Latin1 flag for single character
TEST_F(CharClassBuilderTest_520, AddRangeFlags_FoldCase_Latin1_SingleChar_520) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::Latin1 | Regexp::ClassNL);
  builder_->AddRangeFlags('A', 'A', flags);
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('a'));
}

}  // namespace re2
