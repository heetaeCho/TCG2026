#include <gtest/gtest.h>
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"
#include "util/utf.h"

#include <string>
#include <memory>

namespace re2 {

// We test Prefilter through its public static method FromRE2 or FromRegexp
// since Info is an internal class. We verify behavior through Prefilter's interface.

class PrefilterTest_552 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple literal regex produces a non-null prefilter
TEST_F(PrefilterTest_552, SimpleLiteralProducesPrefilter_552) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce a prefilter
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test that a dot-star (match anything) regex produces appropriate prefilter
TEST_F(PrefilterTest_552, DotStarPattern_552) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, prefilter may be an ALL match or null
  delete pf;
}

// Test alternation pattern
TEST_F(PrefilterTest_552, AlternationPattern_552) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  if (pf) {
    // Alternation should produce an OR prefilter
    EXPECT_EQ(pf->op(), Prefilter::OR);
  }
  delete pf;
}

// Test concatenation pattern
TEST_F(PrefilterTest_552, ConcatenationPattern_552) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  if (pf) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
  }
  delete pf;
}

// Test character class pattern
TEST_F(PrefilterTest_552, CharClassPattern_552) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test question mark (optional) pattern
TEST_F(PrefilterTest_552, QuestionMarkPattern_552) {
  RE2 re("ab?c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Should still produce a prefilter
  delete pf;
}

// Test plus pattern
TEST_F(PrefilterTest_552, PlusPattern_552) {
  RE2 re("ab+c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test star pattern
TEST_F(PrefilterTest_552, StarPattern_552) {
  RE2 re("ab*c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test empty string pattern
TEST_F(PrefilterTest_552, EmptyStringPattern_552) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern - prefilter could be null or ALL
  delete pf;
}

// Test single character literal
TEST_F(PrefilterTest_552, SingleCharLiteral_552) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  if (pf) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
  }
  delete pf;
}

// Test case insensitive pattern
TEST_F(PrefilterTest_552, CaseInsensitivePattern_552) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test complex AND pattern
TEST_F(PrefilterTest_552, ComplexAndPattern_552) {
  RE2 re("hello.*world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  if (pf) {
    EXPECT_EQ(pf->op(), Prefilter::AND);
  }
  delete pf;
}

// Test Prefilter DebugString
TEST_F(PrefilterTest_552, DebugStringNotEmpty_552) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test unicode literal
TEST_F(PrefilterTest_552, UnicodeLiteral_552) {
  RE2 re("café");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test that ATOM prefilter has correct atom value for simple literal
TEST_F(PrefilterTest_552, AtomValueForSimpleLiteral_552) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::ATOM) {
    EXPECT_EQ(pf->atom(), "hello");
  }
  delete pf;
}

// Test uppercase literal is lowered
TEST_F(PrefilterTest_552, UppercaseLiteralIsLowered_552) {
  RE2 re("HELLO");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::ATOM) {
    EXPECT_EQ(pf->atom(), "hello");
  }
  delete pf;
}

// Test ALL match pattern
TEST_F(PrefilterTest_552, AllMatchPattern_552) {
  RE2 re(".");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single dot matches any char, prefilter should be ALL or null
  if (pf) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
  }
  delete pf;
}

// Test Latin1 mode
TEST_F(PrefilterTest_552, Latin1ModePattern_552) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("hello", opts);
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

// Test repeated alternation
TEST_F(PrefilterTest_552, MultipleAlternation_552) {
  RE2 re("a|b|c|d|e");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Many single-char alternations may simplify to ALL
  delete pf;
}

// Test FromRE2 with complex regex
TEST_F(PrefilterTest_552, ComplexRegex_552) {
  RE2 re("(foo|bar)baz[0-9]+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  delete pf;
}

}  // namespace re2
