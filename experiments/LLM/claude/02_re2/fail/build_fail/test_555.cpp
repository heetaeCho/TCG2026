#include <gtest/gtest.h>
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"

namespace re2 {

// Since Prefilter::Info is a private inner class, we test Prefilter through
// its public interface. The Prefilter can be obtained from CompileStatic.
class PrefilterTest_555 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated prefilters
  }
};

// Test that Prefilter can be created from a simple literal regex
TEST_F(PrefilterTest_555, FromLiteralRegex_555) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  // A simple literal should produce an ATOM prefilter
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
  re->Decref();
}

// Test that Prefilter from ".*" produces ALL
TEST_F(PrefilterTest_555, FromDotStarRegex_555) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

// Test that Prefilter from alternation produces OR
TEST_F(PrefilterTest_555, FromAlternationRegex_555) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  // Alternation of two literals should produce OR of ATOMs
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
  re->Decref();
}

// Test that Prefilter from concatenation produces AND or ATOM
TEST_F(PrefilterTest_555, FromConcatenationRegex_555) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abc");
  delete pf;
  re->Decref();
}

// Test Prefilter atom() accessor for a literal
TEST_F(PrefilterTest_555, AtomAccessor_555) {
  Regexp* re = Regexp::Parse("test", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "test");
  delete pf;
  re->Decref();
}

// Test Prefilter from empty string
TEST_F(PrefilterTest_555, FromEmptyString_555) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Empty string may yield ALL or nullptr
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

// Test Prefilter from character class
TEST_F(PrefilterTest_555, FromCharClass_555) {
  Regexp* re = Regexp::Parse("[a-z]foo", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  // Should contain "foo" as an atom somewhere
  delete pf;
  re->Decref();
}

// Test Prefilter from optional (quest) pattern
TEST_F(PrefilterTest_555, FromOptionalPattern_555) {
  Regexp* re = Regexp::Parse("a?hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test Prefilter from star (Kleene star) pattern
TEST_F(PrefilterTest_555, FromStarPattern_555) {
  Regexp* re = Regexp::Parse("a*hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test Prefilter from plus pattern
TEST_F(PrefilterTest_555, FromPlusPattern_555) {
  Regexp* re = Regexp::Parse("a+hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test Prefilter DebugString
TEST_F(PrefilterTest_555, DebugString_555) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  EXPECT_NE(debug.find("hello"), std::string::npos);
  delete pf;
  re->Decref();
}

// Test Prefilter subs() for compound expressions
TEST_F(PrefilterTest_555, SubsForOrExpression_555) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::OR) {
    ASSERT_NE(pf->subs(), nullptr);
    EXPECT_GE(pf->subs()->size(), 2u);
  }
  delete pf;
  re->Decref();
}

// Test Prefilter from complex regex with AND
TEST_F(PrefilterTest_555, ComplexAndPattern_555) {
  Regexp* re = Regexp::Parse("hello.*world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  // Could be AND of "hello" and "world"
  if (pf->op() == Prefilter::AND) {
    ASSERT_NE(pf->subs(), nullptr);
    EXPECT_GE(pf->subs()->size(), 2u);
  }
  delete pf;
  re->Decref();
}

// Test Prefilter op() values correspond to enum
TEST_F(PrefilterTest_555, OpEnumValues_555) {
  EXPECT_EQ(Prefilter::ALL, 0);
  EXPECT_EQ(Prefilter::NONE, 1);
  EXPECT_EQ(Prefilter::ATOM, 2);
  EXPECT_EQ(Prefilter::AND, 3);
  EXPECT_EQ(Prefilter::OR, 4);
}

// Test Prefilter from single character
TEST_F(PrefilterTest_555, FromSingleChar_555) {
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Single char may be too short for atom, could be ALL
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

// Test Prefilter from unicode literal
TEST_F(PrefilterTest_555, FromUnicodeLiteral_555) {
  Regexp* re = Regexp::Parse("café", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test that nullptr regexp is handled (if applicable)
TEST_F(PrefilterTest_555, NullRegexpFromRegexp_555) {
  Prefilter* pf = Prefilter::FromRegexp(nullptr);
  // Should handle nullptr gracefully
  if (pf != nullptr) {
    delete pf;
  }
}

}  // namespace re2
