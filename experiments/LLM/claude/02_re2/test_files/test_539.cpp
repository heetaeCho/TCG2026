#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"
#include <string>
#include <memory>

namespace re2 {

class PrefilterTest_539 : public ::testing::Test {
 protected:
  Prefilter* FromRegexp(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == NULL) return NULL;
    Prefilter* pf = Prefilter::FromRegexp(re);
    re->Decref();
    return pf;
  }
};

TEST_F(PrefilterTest_539, SimpleStringLiteral_539) {
  Prefilter* pf = FromRegexp("hello");
  ASSERT_NE(pf, nullptr);
  // A simple literal should produce an ATOM prefilter
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

TEST_F(PrefilterTest_539, EmptyPattern_539) {
  Prefilter* pf = FromRegexp("");
  // Empty pattern may result in ALL or NULL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

TEST_F(PrefilterTest_539, DotStar_539) {
  Prefilter* pf = FromRegexp(".*");
  // .* matches everything, so prefilter should be ALL or NULL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

TEST_F(PrefilterTest_539, Alternation_539) {
  Prefilter* pf = FromRegexp("hello|world");
  ASSERT_NE(pf, nullptr);
  // Alternation of two literals should produce OR
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

TEST_F(PrefilterTest_539, Concatenation_539) {
  Prefilter* pf = FromRegexp("abc.*def");
  ASSERT_NE(pf, nullptr);
  // Should produce AND of atoms "abc" and "def"
  EXPECT_EQ(pf->op(), Prefilter::AND);
  delete pf;
}

TEST_F(PrefilterTest_539, SingleChar_539) {
  Prefilter* pf = FromRegexp("a");
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "a");
  delete pf;
}

TEST_F(PrefilterTest_539, QuestionMark_539) {
  Prefilter* pf = FromRegexp("a?");
  // a? can match empty string, so prefilter should be ALL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

TEST_F(PrefilterTest_539, PlusOperator_539) {
  Prefilter* pf = FromRegexp("hello+");
  ASSERT_NE(pf, nullptr);
  // hello+ requires at least "hello", so should have atom "hell"
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

TEST_F(PrefilterTest_539, CharacterClass_539) {
  Prefilter* pf = FromRegexp("[abc]def");
  ASSERT_NE(pf, nullptr);
  delete pf;
}

TEST_F(PrefilterTest_539, StarOperator_539) {
  Prefilter* pf = FromRegexp("hello*");
  ASSERT_NE(pf, nullptr);
  // hello* requires at least "hell"
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

TEST_F(PrefilterTest_539, DebugString_539) {
  Prefilter* pf = FromRegexp("hello");
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

TEST_F(PrefilterTest_539, ComplexPattern_539) {
  Prefilter* pf = FromRegexp("(foo|bar).*baz");
  ASSERT_NE(pf, nullptr);
  // Should have some AND/OR structure
  EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::OR || pf->op() == Prefilter::ATOM);
  delete pf;
}

TEST_F(PrefilterTest_539, AnyByte_539) {
  Prefilter* pf = FromRegexp("\\C");
  // \\C matches any byte, prefilter should be ALL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

TEST_F(PrefilterTest_539, NullFromAllMatch_539) {
  Prefilter* pf = FromRegexp(".");
  // Single dot matches any char, likely ALL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

TEST_F(PrefilterTest_539, PrefilterOpValues_539) {
  // Test that op enum values exist
  EXPECT_NE(Prefilter::ALL, Prefilter::ATOM);
  EXPECT_NE(Prefilter::AND, Prefilter::OR);
  EXPECT_NE(Prefilter::NONE, Prefilter::ALL);
}

TEST_F(PrefilterTest_539, CaseInsensitiveLiteral_539) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  re->Decref();
  if (pf != nullptr) {
    // Case insensitive should still produce something
    EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::OR || 
                pf->op() == Prefilter::ATOM || pf->op() == Prefilter::ALL);
    delete pf;
  }
}

TEST_F(PrefilterTest_539, LongLiteral_539) {
  Prefilter* pf = FromRegexp("abcdefghijklmnopqrstuvwxyz");
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abcdefghijklmnopqrstuvwxyz");
  delete pf;
}

TEST_F(PrefilterTest_539, MultipleAlternations_539) {
  Prefilter* pf = FromRegexp("aaa|bbb|ccc|ddd");
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

}  // namespace re2
