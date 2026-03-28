#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <memory>

namespace re2 {

class PrefilterTest_551 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that FromRE2 returns a non-null Prefilter for a simple literal pattern
TEST_F(PrefilterTest_551, FromRE2SimpleLiteral_551) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // A simple literal should produce a prefilter
  EXPECT_NE(nullptr, pf.get());
}

// Test that FromRE2 returns a prefilter for a pattern with alternation
TEST_F(PrefilterTest_551, FromRE2Alternation_551) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  EXPECT_NE(nullptr, pf.get());
}

// Test Prefilter op types - ALL
TEST_F(PrefilterTest_551, PrefilterOpALL_551) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  EXPECT_EQ(Prefilter::ALL, pf->op());
  delete pf;
}

// Test Prefilter op types - NONE
TEST_F(PrefilterTest_551, PrefilterOpNONE_551) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  EXPECT_EQ(Prefilter::NONE, pf->op());
  delete pf;
}

// Test Prefilter for a dot-star pattern (matches everything)
TEST_F(PrefilterTest_551, FromRE2DotStar_551) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // .* matches everything, prefilter may be ALL or null
  if (pf != nullptr) {
    EXPECT_EQ(Prefilter::ALL, pf->op());
  }
}

// Test Prefilter for a single character pattern
TEST_F(PrefilterTest_551, FromRE2SingleChar_551) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  EXPECT_NE(nullptr, pf.get());
}

// Test Prefilter for complex regex
TEST_F(PrefilterTest_551, FromRE2ComplexPattern_551) {
  RE2 re("(foo|bar)baz[0-9]+");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  EXPECT_NE(nullptr, pf.get());
}

// Test Prefilter DebugString is non-empty for a literal
TEST_F(PrefilterTest_551, DebugStringNonEmpty_551) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  ASSERT_NE(nullptr, pf.get());
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test Prefilter for empty string pattern
TEST_F(PrefilterTest_551, FromRE2EmptyPattern_551) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Empty pattern should match everything
  if (pf != nullptr) {
    EXPECT_EQ(Prefilter::ALL, pf->op());
  }
}

// Test Prefilter for character class pattern
TEST_F(PrefilterTest_551, FromRE2CharacterClass_551) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  EXPECT_NE(nullptr, pf.get());
}

}  // namespace re2
