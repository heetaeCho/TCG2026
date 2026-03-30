#include <gtest/gtest.h>

#include "exp.h"  // YAML::Exp::NotPrintable()
#include <string>

namespace {

using YAML::Exp::NotPrintable;

class NotPrintableExpTest_126 : public ::testing::Test {
 protected:
  const YAML::RegEx& ex() const { return NotPrintable(); }
};

TEST_F(NotPrintableExpTest_126, ReturnsSameInstanceAcrossCalls_126) {
  const YAML::RegEx* p1 = &NotPrintable();
  const YAML::RegEx* p2 = &NotPrintable();
  const YAML::RegEx* p3 = &NotPrintable();

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

TEST_F(NotPrintableExpTest_126, DoesNotMatchEmptyString_126) {
  EXPECT_FALSE(ex().Matches(std::string()));
}

TEST_F(NotPrintableExpTest_126, MatchesExplicitSingleByteControlCharacters_126) {
  // These bytes are explicitly included.
  EXPECT_TRUE(ex().Matches(std::string(1, '\x00')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x01')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x02')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x03')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x04')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x05')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x06')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x07')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x08')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x0B')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x0C')));
  EXPECT_TRUE(ex().Matches(std::string(1, '\x7F')));
}

TEST_F(NotPrintableExpTest_126, DoesNotMatchSomeCommonWhitespaceControlsNotIncluded_126) {
  // These are notably not present in the explicit set/ranges.
  EXPECT_FALSE(ex().Matches(std::string(1, '\x09')));  // TAB
  EXPECT_FALSE(ex().Matches(std::string(1, '\x0A')));  // LF
  EXPECT_FALSE(ex().Matches(std::string(1, '\x0D')));  // CR
}

TEST_F(NotPrintableExpTest_126, MatchesRange0ETo1FInclusive_126) {
  for (int b = 0x0E; b <= 0x1F; ++b) {
    SCOPED_TRACE(b);
    EXPECT_TRUE(ex().Matches(std::string(1, static_cast<char>(b))));
  }
}

TEST_F(NotPrintableExpTest_126, DoesNotMatchBoundaryOutside0ETo1FRange_126) {
  EXPECT_FALSE(ex().Matches(std::string(1, '\x0D')));  // just below range
  EXPECT_FALSE(ex().Matches(std::string(1, '\x20')));  // just above range (space)
}

TEST_F(NotPrintableExpTest_126, DoesNotMatchTypicalPrintableASCII_126) {
  EXPECT_FALSE(ex().Matches(std::string(1, 'A')));
  EXPECT_FALSE(ex().Matches(std::string(1, 'z')));
  EXPECT_FALSE(ex().Matches(std::string(1, '0')));
  EXPECT_FALSE(ex().Matches(std::string(1, ' ')));
  EXPECT_FALSE(ex().Matches(std::string(1, '~')));
}

TEST_F(NotPrintableExpTest_126, MatchesTwoByteC2SequencesInFirstSubrange_126) {
  // UTF-8: 0xC2 followed by 0x80..0x84 should match.
  EXPECT_TRUE(ex().Matches(std::string("\xC2\x80", 2)));
  EXPECT_TRUE(ex().Matches(std::string("\xC2\x81", 2)));
  EXPECT_TRUE(ex().Matches(std::string("\xC2\x82", 2)));
  EXPECT_TRUE(ex().Matches(std::string("\xC2\x83", 2)));
  EXPECT_TRUE(ex().Matches(std::string("\xC2\x84", 2)));

  // Boundary checks around that subrange.
  EXPECT_FALSE(ex().Matches(std::string("\xC2\x7F", 2)));
  EXPECT_FALSE(ex().Matches(std::string("\xC2\x85", 2)));
}

TEST_F(NotPrintableExpTest_126, MatchesTwoByteC2SequencesInSecondSubrange_126) {
  // UTF-8: 0xC2 followed by 0x86..0x9F should match.
  EXPECT_TRUE(ex().Matches(std::string("\xC2\x86", 2)));
  EXPECT_TRUE(ex().Matches(std::string("\xC2\x9F", 2)));

  // Boundary checks around that subrange.
  EXPECT_FALSE(ex().Matches(std::string("\xC2\x85", 2)));
  EXPECT_FALSE(ex().Matches(std::string("\xC2\xA0", 2)));
}

TEST_F(NotPrintableExpTest_126, DoesNotMatchWithWrongLeadingByteForTwoByteSequence_126) {
  // Same trailing bytes, but wrong lead byte should not match this specific sequence.
  EXPECT_FALSE(ex().Matches(std::string("\xC3\x80", 2)));
  EXPECT_FALSE(ex().Matches(std::string("\x00\x80", 2)));
}

}  // namespace
