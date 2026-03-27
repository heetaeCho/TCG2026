// File: prefilter_tolowerrune_latin1_test.cc

#include <gtest/gtest.h>

// Include the implementation so we can test the TU-local (static) function.
// This keeps us from re-implementing or peeking into any private state.
#include "re2/prefilter.cc"

namespace {

using re2::ToLowerRuneLatin1;

// Fixture kept minimal for clarity and consistency
class ToLowerRuneLatin1Test_538 : public ::testing::Test {};

TEST_F(ToLowerRuneLatin1Test_538, UppercaseBasicMapping_538) {
  EXPECT_EQ(ToLowerRuneLatin1('A'), 'a');
  EXPECT_EQ(ToLowerRuneLatin1('B'), 'b');
  EXPECT_EQ(ToLowerRuneLatin1('Z'), 'z');
}

TEST_F(ToLowerRuneLatin1Test_538, LowercaseUnchanged_538) {
  EXPECT_EQ(ToLowerRuneLatin1('a'), 'a');
  EXPECT_EQ(ToLowerRuneLatin1('m'), 'm');
  EXPECT_EQ(ToLowerRuneLatin1('z'), 'z');
}

TEST_F(ToLowerRuneLatin1Test_538, NonLettersAsciiUnchanged_538) {
  EXPECT_EQ(ToLowerRuneLatin1('0'), '0');
  EXPECT_EQ(ToLowerRuneLatin1('9'), '9');
  EXPECT_EQ(ToLowerRuneLatin1('@'), '@');  // just before 'A'
  EXPECT_EQ(ToLowerRuneLatin1('['), '[');  // just after 'Z'
}

TEST_F(ToLowerRuneLatin1Test_538, BoundaryLetters_538) {
  EXPECT_EQ(ToLowerRuneLatin1('A'), 'a');  // lower bound of range
  EXPECT_EQ(ToLowerRuneLatin1('Z'), 'z');  // upper bound of range
}

TEST_F(ToLowerRuneLatin1Test_538, ExtendedLatin1Unchanged_538) {
  // Characters outside 'A'..'Z' should be returned as-is by the observable API
  // (e.g., common Latin-1 letters that aren't ASCII uppercase).
  EXPECT_EQ(ToLowerRuneLatin1(static_cast<int>('Ä')), static_cast<int>('Ä'));   // 0xC4
  EXPECT_EQ(ToLowerRuneLatin1(0xDF), 0xDF);  // 'ß'
  EXPECT_EQ(ToLowerRuneLatin1(0xFF), 0xFF);  // 'ÿ'
}

TEST_F(ToLowerRuneLatin1Test_538, NonAsciiCodepointsUnchanged_538) {
  // Use a few representative non-ASCII code points to verify no transformation.
  EXPECT_EQ(ToLowerRuneLatin1(0x0100), 0x0100);  // Latin Capital A with macron
  EXPECT_EQ(ToLowerRuneLatin1(0x07FF), 0x07FF);
  EXPECT_EQ(ToLowerRuneLatin1(0x20AC), 0x20AC);  // Euro sign
}

TEST_F(ToLowerRuneLatin1Test_538, IdempotentOnResult_538) {
  // Applying the function twice should not change the output further.
  int once = ToLowerRuneLatin1('T');
  int twice = ToLowerRuneLatin1(once);
  EXPECT_EQ(once, twice);

  // Also holds for inputs that are not transformed.
  once = ToLowerRuneLatin1('@');
  twice = ToLowerRuneLatin1(once);
  EXPECT_EQ(once, twice);
}

TEST_F(ToLowerRuneLatin1Test_538, MapsAllAsciiUppercaseRange_538) {
  // Verify every ASCII uppercase letter maps to its lowercase counterpart.
  for (int r = 'A'; r <= 'Z'; ++r) {
    int expected = r - 'A' + 'a';
    EXPECT_EQ(ToLowerRuneLatin1(r), expected) << "Failed at r=" << r;
  }
}

}  // namespace
