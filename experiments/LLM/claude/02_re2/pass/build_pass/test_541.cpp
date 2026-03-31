#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prefilter_tree.h"
#include <string>
#include <vector>

namespace re2 {

class PrefilterTest_541 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that FromRE2 returns a non-null prefilter for a simple literal pattern
TEST_F(PrefilterTest_541, FromRE2SimpleLiteral_541) {
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce a prefilter
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

// Test that FromRE2 with a dot-star pattern returns ALL or null
TEST_F(PrefilterTest_541, FromRE2DotStar_541) {
  RE2 re(".*");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test alternation pattern produces OR prefilter
TEST_F(PrefilterTest_541, FromRE2Alternation_541) {
  RE2 re("hello|world");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

// Test concatenation of literals produces AND or ATOM
TEST_F(PrefilterTest_541, FromRE2Concatenation_541) {
  RE2 re("abc.*def");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Could be AND of two atoms
  delete pf;
}

// Test single character literal
TEST_F(PrefilterTest_541, FromRE2SingleChar_541) {
  RE2 re("a");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character might be too short for prefilter
  // Behavior depends on min atom length
  delete pf;
}

// Test empty pattern
TEST_F(PrefilterTest_541, FromRE2EmptyPattern_541) {
  RE2 re("");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern should likely produce ALL or null
  delete pf;
}

// Test question mark (optional)
TEST_F(PrefilterTest_541, FromRE2Optional_541) {
  RE2 re("hello?");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // "hello?" - the 'o' is optional
  delete pf;
}

// Test plus (one or more)
TEST_F(PrefilterTest_541, FromRE2Plus_541) {
  RE2 re("hel+o");
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

// Test star (zero or more)
TEST_F(PrefilterTest_541, FromRE2Star_541) {
  RE2 re("hel*o");
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

// Test character class
TEST_F(PrefilterTest_541, FromRE2CharClass_541) {
  RE2 re("[abc]def");
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

// Test Prefilter DebugString
TEST_F(PrefilterTest_541, DebugStringAtom_541) {
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test complex pattern
TEST_F(PrefilterTest_541, FromRE2ComplexPattern_541) {
  RE2 re("(foo|bar).*baz");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test case-insensitive pattern
TEST_F(PrefilterTest_541, FromRE2CaseInsensitive_541) {
  RE2 re("(?i)hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

// Test Prefilter op values
TEST_F(PrefilterTest_541, PrefilterOpValues_541) {
  EXPECT_EQ(Prefilter::ALL, 0);
  EXPECT_EQ(Prefilter::NONE, 1);
  EXPECT_EQ(Prefilter::ATOM, 2);
  EXPECT_EQ(Prefilter::AND, 3);
  EXPECT_EQ(Prefilter::OR, 4);
}

// Test that a NONE pattern (impossible match) is handled
TEST_F(PrefilterTest_541, FromRE2ImpossibleMatch_541) {
  RE2 re("[^\\s\\S]");  // matches nothing
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

// Test long literal string
TEST_F(PrefilterTest_541, FromRE2LongLiteral_541) {
  RE2 re("abcdefghijklmnopqrstuvwxyz");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abcdefghijklmnopqrstuvwxyz");
  delete pf;
}

// Test subs() for AND/OR nodes
TEST_F(PrefilterTest_541, SubsForAlternation_541) {
  RE2 re("hello|world");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::OR) {
    EXPECT_FALSE(pf->subs()->empty());
  }
  delete pf;
}

// Test FromRE2 with Unicode pattern
TEST_F(PrefilterTest_541, FromRE2Unicode_541) {
  RE2 re("café");
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

}  // namespace re2
