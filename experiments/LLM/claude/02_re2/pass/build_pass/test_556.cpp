#include "re2/prefilter.h"
#include "re2/re2.h"
#include "gtest/gtest.h"

#include <memory>
#include <string>

namespace re2 {

// Test Prefilter creation from simple regex patterns
TEST(PrefilterTest_556, FromSimpleLiteral_556) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
  // A simple literal should produce an ATOM prefilter
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
}

TEST(PrefilterTest_556, FromAllMatch_556) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // .* matches everything, should be ALL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
  }
  // pf could be nullptr meaning match all
}

TEST(PrefilterTest_556, FromAlternation_556) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
  // Alternation should produce OR prefilter
  EXPECT_EQ(pf->op(), Prefilter::OR);
}

TEST(PrefilterTest_556, FromConcatenation_556) {
  RE2 re("hello.*world");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
  // Could be AND or ATOM depending on implementation
  EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::ATOM ||
              pf->op() == Prefilter::OR || pf->op() == Prefilter::ALL);
}

TEST(PrefilterTest_556, FromEmptyPattern_556) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Empty pattern matches everything
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
  }
}

TEST(PrefilterTest_556, FromCharacterClass_556) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
}

TEST(PrefilterTest_556, FromQuestionMark_556) {
  RE2 re("ab?c");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Should still produce something valid
  ASSERT_NE(pf, nullptr);
}

TEST(PrefilterTest_556, FromPlus_556) {
  RE2 re("ab+c");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
}

TEST(PrefilterTest_556, FromStar_556) {
  RE2 re("ab*c");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
}

TEST(PrefilterTest_556, DebugString_556) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
  std::string s = pf->DebugString();
  EXPECT_FALSE(s.empty());
}

TEST(PrefilterTest_556, AtomHasNonEmptyAtom_556) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::ATOM) {
    EXPECT_FALSE(pf->atom().empty());
  }
}

TEST(PrefilterTest_556, OrHasSubs_556) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::OR) {
    ASSERT_NE(pf->subs(), nullptr);
    EXPECT_GE(pf->subs()->size(), 2u);
  }
}

TEST(PrefilterTest_556, FromComplexPattern_556) {
  RE2 re("(foo|bar).*baz");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
}

TEST(PrefilterTest_556, FromDotPattern_556) {
  RE2 re(".");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Single dot matches any char - likely ALL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
  }
}

TEST(PrefilterTest_556, FromLatin1Literal_556) {
  RE2::Options opt;
  opt.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("hello", opt);
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
}

TEST(PrefilterTest_556, NoneOpDefault_556) {
  // Construct a prefilter with NONE
  std::unique_ptr<Prefilter> pf(new Prefilter(Prefilter::NONE));
  EXPECT_EQ(pf->op(), Prefilter::NONE);
}

TEST(PrefilterTest_556, AllOpDefault_556) {
  std::unique_ptr<Prefilter> pf(new Prefilter(Prefilter::ALL));
  EXPECT_EQ(pf->op(), Prefilter::ALL);
}

TEST(PrefilterTest_556, MultipleAlternations_556) {
  RE2 re("aaa|bbb|ccc|ddd");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::OR) {
    EXPECT_GE(pf->subs()->size(), 2u);
  }
}

TEST(PrefilterTest_556, UnicodePattern_556) {
  RE2 re("café");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(pf, nullptr);
}

}  // namespace re2
