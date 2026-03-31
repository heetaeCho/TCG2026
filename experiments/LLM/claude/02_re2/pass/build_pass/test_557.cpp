#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"
#include "gtest/gtest.h"

#include <string>
#include <set>

// Since Prefilter::Info is an internal class defined in prefilter.cc,
// we need to test through the public Prefilter interface.
// We'll test Prefilter::FromRE2 and related public methods that
// exercise the Info class internally.

namespace re2 {

class PrefilterTest_557 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple literal regex produces a non-null prefilter
TEST_F(PrefilterTest_557, SimpleLiteralProducesPrefilter_557) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A literal string should produce a prefilter
  EXPECT_NE(pf, nullptr);
  if (pf) {
    // Should be an ATOM for a simple literal
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
  }
  delete pf;
}

// Test that an empty regex pattern works
TEST_F(PrefilterTest_557, EmptyPatternPrefilter_557) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern may produce ALL or null
  delete pf;
}

// Test alternation
TEST_F(PrefilterTest_557, AlternationPrefilter_557) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  if (pf) {
    // Alternation should produce OR
    EXPECT_EQ(pf->op(), Prefilter::OR);
  }
  delete pf;
}

// Test concatenation
TEST_F(PrefilterTest_557, ConcatenationPrefilter_557) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  if (pf) {
    // Should be AND of atoms or a single merged atom
    EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::ATOM);
  }
  delete pf;
}

// Test dot star (any match)
TEST_F(PrefilterTest_557, DotStarProducesAllMatch_557) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, prefilter should be ALL or null
  if (pf) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
  }
  delete pf;
}

// Test character class
TEST_F(PrefilterTest_557, CharClassPrefilter_557) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test question mark (optional)
TEST_F(PrefilterTest_557, OptionalPrefilter_557) {
  RE2 re("abc?def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test plus
TEST_F(PrefilterTest_557, PlusPrefilter_557) {
  RE2 re("ab+c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test star
TEST_F(PrefilterTest_557, StarPrefilter_557) {
  RE2 re("ab*c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test single character literal
TEST_F(PrefilterTest_557, SingleCharLiteralPrefilter_557) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character may or may not produce useful prefilter
  delete pf;
}

// Test Prefilter debugstring
TEST_F(PrefilterTest_557, DebugStringNotEmpty_557) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test complex pattern
TEST_F(PrefilterTest_557, ComplexPatternPrefilter_557) {
  RE2 re("(foo|bar).*baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test case insensitive
TEST_F(PrefilterTest_557, CaseInsensitivePrefilter_557) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Case insensitive may produce OR of variants or ALL
  delete pf;
}

// Test unicode literal
TEST_F(PrefilterTest_557, UnicodeLiteralPrefilter_557) {
  RE2 re("café");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test Prefilter op values
TEST_F(PrefilterTest_557, PrefilterOpValues_557) {
  // Verify ALL and ATOM and AND and OR are distinct
  EXPECT_NE(Prefilter::ALL, Prefilter::ATOM);
  EXPECT_NE(Prefilter::ALL, Prefilter::AND);
  EXPECT_NE(Prefilter::ALL, Prefilter::OR);
  EXPECT_NE(Prefilter::ATOM, Prefilter::AND);
  EXPECT_NE(Prefilter::ATOM, Prefilter::OR);
  EXPECT_NE(Prefilter::AND, Prefilter::OR);
}

// Test no match pattern
TEST_F(PrefilterTest_557, NoMatchPattern_557) {
  RE2 re("[^\\s\\S]");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // This matches nothing; prefilter could be anything
  delete pf;
}

// Test long literal string
TEST_F(PrefilterTest_557, LongLiteralString_557) {
  RE2 re("abcdefghijklmnopqrstuvwxyz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

// Test nested alternation and concatenation
TEST_F(PrefilterTest_557, NestedAltAndConcat_557) {
  RE2 re("(a|b)(c|d)");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // This is complex; just verify it doesn't crash
  delete pf;
}

// Test Prefilter atom accessor for literal
TEST_F(PrefilterTest_557, AtomAccessor_557) {
  RE2 re("testword");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::ATOM) {
    EXPECT_EQ(pf->atom(), "testword");
  }
  delete pf;
}

// Test Prefilter subs for compound expression
TEST_F(PrefilterTest_557, SubsForCompound_557) {
  RE2 re("foo|bar|baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::OR) {
    EXPECT_NE(pf->subs(), nullptr);
    EXPECT_GT(pf->subs()->size(), 0u);
  }
  delete pf;
}

}  // namespace re2
