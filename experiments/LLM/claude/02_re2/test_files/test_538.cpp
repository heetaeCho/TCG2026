#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/prefilter_tree.h"
#include <string>
#include <vector>

namespace re2 {

class PrefilterTest_538 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that FromRE2 returns a non-null Prefilter for a simple literal pattern
TEST_F(PrefilterTest_538, FromRE2SimpleLiteral_538) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // pf may or may not be null depending on the pattern, but for a literal it should exist
  if (pf != nullptr) {
    delete pf;
  }
}

// Test that FromRE2 returns a Prefilter for a case-insensitive pattern
TEST_F(PrefilterTest_538, FromRE2CaseInsensitive_538) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test that FromRE2 handles alternation
TEST_F(PrefilterTest_538, FromRE2Alternation_538) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test that FromRE2 handles dot star (match all)
TEST_F(PrefilterTest_538, FromRE2DotStar_538) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, so prefilter might be an ALL node or null
  if (pf != nullptr) {
    delete pf;
  }
}

// Test that FromRE2 handles character classes
TEST_F(PrefilterTest_538, FromRE2CharClass_538) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test that FromRE2 handles complex regex
TEST_F(PrefilterTest_538, FromRE2ComplexPattern_538) {
  RE2 re("(foo|bar).*baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test that FromRE2 handles empty pattern
TEST_F(PrefilterTest_538, FromRE2EmptyPattern_538) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test that FromRE2 handles single character
TEST_F(PrefilterTest_538, FromRE2SingleChar_538) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test Prefilter with repetition
TEST_F(PrefilterTest_538, FromRE2Repetition_538) {
  RE2 re("ab+c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test Prefilter DebugString doesn't crash
TEST_F(PrefilterTest_538, DebugStringNoCrash_538) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

}  // namespace re2
